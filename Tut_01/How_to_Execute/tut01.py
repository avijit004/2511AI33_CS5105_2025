import math
import argparse
from collections import deque, defaultdict
from dataclasses import dataclass
from pathlib import Path
import pandas as pd
import sys
import json
from datetime import datetime
from typing import List, Optional, Union
import shutil
import io

@dataclass
class RunConfig:
    input_path: Path
    sheet_name: str
    output_dir: Path
    mix_groups_count: int
    uniform_groups_count: int

def parse_cli() -> argparse.Namespace:
    parser = argparse.ArgumentParser(description="Create Branchwise Mix (iterator-based) and Uniform Mix groups from roster.")
    parser.add_argument("--input", "-i", type=str, default="input_Make-Groups.xlsx",
                        help="Path to the roster file (.xlsx or .csv). Default: input_Make-Groups.xlsx")
    parser.add_argument("--sheet", "-s", type=str, default="Sheet1",
                        help="Excel sheet name (for .xlsx). Default: Sheet1")
    parser.add_argument("--output", "-o", type=str, default="output",
                        help="Output directory (will be cleared each run). Default: output")
    parser.add_argument("--groups-mix", type=int,
                        help="Number of groups for the Branchwise Mix permutation. If omitted, will prompt.")
    parser.add_argument("--groups-uniform", type=int,
                        help="Number of groups for the Uniform Mix permutation. If omitted, will prompt.")
    return parser.parse_args()

def ask_positive_int(prompt: str, provided: Optional[int]) -> int:
    if provided is not None:
        n = provided
    else:
        try:
            n = int(input(prompt).strip())
        except Exception:
            print("Invalid input. Please provide a positive integer.")
            sys.exit(1)
    if n <= 0:
        print("Value must be a positive integer.")
        sys.exit(1)
    return n

def parse_branch_code(roll: str) -> Optional[str]:
    if not isinstance(roll, str):
        return None
    s = roll.strip()
    return s[4:6] if len(s) >= 6 else None

def mkdir_p(path: Path) -> None:
    path.mkdir(parents=True, exist_ok=True)

def export_groups_csv(groups: List[List[dict]], out_dir: Path) -> None:
    mkdir_p(out_dir)
    for idx, members in enumerate(groups, start=1):
        frame = pd.DataFrame(members)
        if not frame.empty:
            for col in ["Name", "Roll", "Email"]:
                if col not in frame.columns:
                    frame[col] = ""
            frame = frame[["Name", "Roll", "Email"]]
        else:
            frame = pd.DataFrame(columns=["Name", "Roll", "Email"])
        frame.to_csv(out_dir / f"G{idx}.csv", index=False)

def summarize_group_composition(groups: List[List[dict]], branch_codes: List[str]) -> pd.DataFrame:
    rows = []
    for i, members in enumerate(groups, start=1):
        row = {"Group": f"G{i}"}
        counts = defaultdict(int)
        for m in members:
            br = m.get("Branch", None)
            if br is not None:
                counts[br] += 1
        total = 0
        for b in branch_codes:
            c = counts.get(b, 0)
            row[b] = c
            total += c
        row["Total"] = total
        rows.append(row)
    return pd.DataFrame(rows, columns=["Group"] + branch_codes + ["Total"])

def _normalize_headers(df: pd.DataFrame) -> pd.DataFrame:
    df = df.copy()
    lower = {c: c.strip().lower() for c in df.columns}
    df.columns = [lower[c] for c in df.columns]
    ren = {}
    for c in list(df.columns):
        if c in {"roll", "roll no", "roll no.", "roll_no", "rollnumber", "rollnumber."}:
            ren[c] = "roll"
        elif c == "name ":
            ren[c] = "name"
    if ren:
        df = df.rename(columns=ren)
    return df

def normalize_dataframe_columns(df_in: pd.DataFrame) -> pd.DataFrame:
    df = _normalize_headers(df_in)
    required = ["roll", "name", "email"]
    missing = [c for c in required if c not in df.columns]
    if missing:
        raise RuntimeError(f"Missing required columns: {missing}. Need Roll, Name, Email.")
    df = df[required].copy()
    for c in df.columns:
        df[c] = df[c].astype(str).str.strip()
    df = df.replace({"": pd.NA}).dropna(subset=required).reset_index(drop=True)
    df["Branch"] = df["roll"].apply(parse_branch_code)
    bad = df["Branch"].isna()
    if bad.any():
        df = df.loc[~bad].reset_index(drop=True)
    df = df.rename(columns={"roll": "Roll", "name": "Name", "email": "Email"})
    df = df.sort_values(by=["Name", "Roll"], kind="stable").reset_index(drop=True)
    return df

def load_student_sheet(xlsx_source: Union[str, Path, io.BytesIO], sheet_name: str) -> pd.DataFrame:
    try:
        df = pd.read_excel(xlsx_source, sheet_name=sheet_name, dtype=str)
    except Exception as e:
        raise RuntimeError(f"Failed to read Excel: {e}")
    df = _normalize_headers(df)
    required = ["roll", "name", "email"]
    missing = [c for c in required if c not in df.columns]
    if missing:
        raise RuntimeError(f"Missing required columns in Excel: {missing}. Expected: Roll, Name, Email.")
    df = df[required].copy()
    for c in df.columns:
        df[c] = df[c].astype(str).str.strip()
    df = df.replace({"": pd.NA}).dropna(subset=required).reset_index(drop=True)
    df["Branch"] = df["roll"].apply(parse_branch_code)
    bad = df["Branch"].isna()
    if bad.any():
        df = df.loc[~bad].reset_index(drop=True)
    df = df.rename(columns={"roll": "Roll", "name": "Name", "email": "Email"})
    df = df.sort_values(by=["Name", "Roll"], kind="stable").reset_index(drop=True)
    return df

def export_branch_rosters(df: pd.DataFrame, out_dir: Path) -> List[str]:
    branch_codes = sorted(df["Branch"].unique().tolist())
    branches_dir = out_dir / "branches"
    mkdir_p(branches_dir)
    for b in branch_codes:
        sub = df.loc[df["Branch"] == b, ["Name", "Roll", "Email"]]
        sub.to_csv(branches_dir / f"{b}.csv", index=False)
    return branch_codes

def create_branchwise_mixed_groups(df: pd.DataFrame, num_groups: int) -> List[List[dict]]:
    if num_groups <= 0:
        raise ValueError("num_groups must be positive")
    total_students = len(df)
    target_size = math.ceil(total_students / num_groups)

    branch_iters = {b: iter(rows.to_dict("records")) for b, rows in df.groupby("Branch")}
    branchwise_mixed: List[List[dict]] = [[] for _ in range(num_groups)]
    group_index = 0

    while True:
        added = False
        for _, it in branch_iters.items():
            try:
                student = next(it)
                branchwise_mixed[group_index].append(student)
                added = True
                if len(branchwise_mixed[group_index]) >= target_size:
                    group_index = (group_index + 1) % num_groups
            except StopIteration:
                continue
        if not added:
            break
    return branchwise_mixed

def make_groups_pack_by_branch(df: pd.DataFrame, branch_codes: List[str], k_groups: int) -> List[List[dict]]:
    total = len(df)
    if k_groups <= 0:
        raise ValueError("k_groups must be positive")
    cap = math.ceil(total / k_groups)

    per_branch_q = {b: deque(df[df["Branch"] == b].to_dict(orient="records")) for b in branch_codes}
    groups = [[] for _ in range(k_groups)]

    for i in range(k_groups):
        while len(groups[i]) < cap:
            candidates = [(b, len(q)) for b, q in per_branch_q.items() if q]
            if not candidates:
                break
            candidates.sort(key=lambda x: (-x[1], x[0]))
            b_pick = candidates[0][0]
            while len(groups[i]) < cap and per_branch_q[b_pick]:
                groups[i].append(per_branch_q[b_pick].popleft())
    return groups

def save_run_metadata(cfg: RunConfig) -> None:
    meta = {
        "input": str(cfg.input_path),
        "sheet": cfg.sheet_name,
        "output": str(cfg.output_dir),
        "mix_groups_count": cfg.mix_groups_count,
        "uniform_groups_count": cfg.uniform_groups_count,
        "timestamp": datetime.now().isoformat(timespec="seconds"),
    }
    mkdir_p(cfg.output_dir)
    (cfg.output_dir / "params.json").write_text(json.dumps(meta, indent=2), encoding="utf-8")

def generate_outputs(input_source: Union[str, Path, io.BytesIO, pd.DataFrame],
                     sheet_name: str,
                     output_dir: Path,
                     mix_k: int,
                     uniform_k: int) -> dict:

    if output_dir.exists():
        shutil.rmtree(output_dir)
    output_dir.mkdir(parents=True, exist_ok=True)
    if isinstance(input_source, pd.DataFrame):
        df = normalize_dataframe_columns(input_source)
    else:
        if isinstance(input_source, (str, Path)) and str(input_source).lower().endswith(".csv"):
            df_raw = pd.read_csv(input_source, dtype=str)
            df = normalize_dataframe_columns(df_raw)
        else:
            df = load_student_sheet(input_source, sheet_name)

    df[["Roll", "Name", "Email"]].to_csv(output_dir / "input_copy.csv", index=False)

    branch_codes = export_branch_rosters(df, output_dir)

    groups_mix = create_branchwise_mixed_groups(df, mix_k)
    export_groups_csv(groups_mix, output_dir / "branch_wise_mix")

    groups_uniform = make_groups_pack_by_branch(df, branch_codes, uniform_k)
    export_groups_csv(groups_uniform, output_dir / "uniform_mix")

    stats_dir = output_dir / "stats"
    mkdir_p(stats_dir)
    stats_mix = summarize_group_composition(groups_mix, branch_codes)
    stats_uniform = summarize_group_composition(groups_uniform, branch_codes)
    with open(stats_dir / "stats.csv", "w", encoding="utf-8") as f:
        f.write("Branchwise Mix," + ",".join(branch_codes) + ",Total\n")
        for _, row in stats_mix.iterrows():
            f.write(f"{row['Group']}," + ",".join(str(int(row[b])) for b in branch_codes) + f",{int(row['Total'])}\n")
        f.write("\n")
        f.write("Uniform Mix," + ",".join(branch_codes) + ",Total\n")
        for _, row in stats_uniform.iterrows():
            f.write(f"{row['Group']}," + ",".join(str(int(row[b])) for b in branch_codes) + f",{int(row['Total'])}\n")

    meta = RunConfig(
        input_path=Path(str(output_dir / "input_copy.csv")),
        sheet_name=sheet_name,
        output_dir=output_dir,
        mix_groups_count=mix_k,
        uniform_groups_count=uniform_k,
    )
    save_run_metadata(meta)

    return {
        "total_students": int(len(df)),
        "branch_counts": df["Branch"].value_counts().sort_index().to_dict(),
        "output_dir": str(output_dir.resolve()),
        "mix_groups": int(mix_k),
        "uniform_groups": int(uniform_k),
    }

def run() -> None:
    cli = parse_cli()

    in_path = Path(cli.input)
    if not in_path.is_absolute():
        in_path = Path.cwd() / in_path
    in_path = in_path.resolve()

    out_dir = Path(cli.output)
    if not out_dir.is_absolute():
        out_dir = Path.cwd() / out_dir
    out_dir = out_dir.resolve()

    if not in_path.exists():
        print(f"Input not found at: {in_path}")
        print("Tips:")
        print("- Ensure filename is correct and path exists")
        print("- For Excel, pass --sheet SHEETNAME if not Sheet1")
        sys.exit(1)

    mix_k = ask_positive_int("Enter number of groups for Branchwise Mix (positive integer): ", cli.groups_mix)
    uniform_k = ask_positive_int("Enter number of groups for Uniform Mix (positive integer): ", cli.groups_uniform)

    if str(in_path).lower().endswith(".csv"):
        input_source = in_path 
    else:
        input_source = in_path 

    summary = generate_outputs(input_source, cli.sheet, out_dir, mix_k, uniform_k)

    print(f"Input: {in_path}")
    print(f"Total students: {summary['total_students']}")
    print("Counts per branch:")
    for b, c in summary["branch_counts"].items():
        print(f"  {b}: {c}")
    print(f"[Branchwise Mix] Groups: {summary['mix_groups']}, group_size: {math.ceil(summary['total_students'] / summary['mix_groups'])}")
    print(f"[Uniform Mix] Groups: {summary['uniform_groups']}, group_size: {math.ceil(summary['total_students'] / summary['uniform_groups'])}")
    print(f"Done. Outputs at: {summary['output_dir']}")

if __name__ == "__main__":
    run()