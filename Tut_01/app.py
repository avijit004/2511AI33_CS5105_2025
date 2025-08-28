import io
from pathlib import Path
import shutil
import streamlit as st
import pandas as pd
import tut01 

st.set_page_config(page_title="Tutorial 1-DAA", page_icon="🧑🏼‍🎓", layout="centered")

st.title("Tutorial 01 Assignment: Student Grouping and Statistics 🧑🏼‍🎓")
st.caption("Branchwise Mix (iterator-based) and Uniform Mix with per-branch statistics and reproducible outputs")
st.divider()

st.subheader("Upload Student Data (CSV/Excel)")
uploaded = st.file_uploader("Drag and drop file here", type=["csv","xlsx"])
sheet_name = st.text_input("Excel sheet name (for .xlsx only)", value="Sheet1")

if uploaded is not None:
    try:
        ext = Path(uploaded.name).suffix.lower()
        if ext == ".csv":
            uploaded.seek(0)
            df_raw = pd.read_csv(uploaded)
            df_preview = tut01.normalize_dataframe_columns(df_raw)
            st.markdown("#### Preview (first 10 rows)")
            st.dataframe(df_preview.head(10), use_container_width=True)
            st.caption(f"{df_preview.shape} rows × {df_preview.shape[1]} columns after normalization")
        elif ext == ".xlsx":
            uploaded.seek(0)
            df_x = pd.read_excel(uploaded, sheet_name=sheet_name, dtype=str)
            st.markdown("#### Preview (first 10 rows)")
            st.dataframe(df_x.head(10), use_container_width=True)
            st.caption(f"{df_x.shape} rows × {df_x.shape[1]} columns (raw Excel sheet)")
        else:
            st.warning("Unsupported file type. Please upload a .csv or .xlsx file.")
    except Exception as e:
        st.warning(f"Could not preview file: {e}")
col1, col2 = st.columns(2)
with col1:
    mix_k = st.number_input("Branchwise Mix: number of groups", min_value=1, step=1, value=3)
with col2:
    uniform_k = st.number_input("Uniform Mix: number of groups", min_value=1, step=1, value=3)

default_out = str((Path.cwd() / "output").resolve())
out_dir_str = st.text_input("Output directory (cleared each run)", value=default_out)

colA, colB = st.columns([1,1])
generate_btn = colA.button("Generate")
clear_btn = colB.button("Clear Output Only")

st.divider()

def clear_output_dir(path_str: str):
    p = Path(path_str)
    if p.exists():
        shutil.rmtree(p)
    p.mkdir(parents=True, exist_ok=True)

if clear_btn:
    try:
        clear_output_dir(out_dir_str)
        st.success(f"Cleared: {out_dir_str}")
    except Exception as e:
        st.error(f"Failed to clear output: {e}")



if generate_btn:
    if uploaded is None:
        st.error("Please upload a .csv or .xlsx file.")
    else:
        try:
            output_dir = Path(out_dir_str)
            ext = Path(uploaded.name).suffix.lower()

            if ext == ".csv":
                uploaded.seek(0)
                df_raw = pd.read_csv(uploaded)
                summary = tut01.generate_outputs(
                    input_source=tut01.normalize_dataframe_columns(df_raw),
                    sheet_name=sheet_name, 
                    output_dir=output_dir,
                    mix_k=int(mix_k),
                    uniform_k=int(uniform_k),
                )
            elif ext == ".xlsx":
                uploaded.seek(0)
                xls_bytes = uploaded.read()
                buf = io.BytesIO(xls_bytes)
                summary = tut01.generate_outputs(
                    input_source=buf,
                    sheet_name=sheet_name,
                    output_dir=output_dir,
                    mix_k=int(mix_k),
                    uniform_k=int(uniform_k),
                )
            else:
                st.error("Unsupported file type. Please upload a .csv or .xlsx file.")
                st.stop()

            st.success("Generation complete!")
            st.write(f"Total students: {summary['total_students']}")

            with st.expander("📁 Full Branchwise Division", expanded=False):
                st.write("CSV files saved under: branches/")
                st.code(str(Path(summary["output_dir"]) / "branches"))
                try:
                    from itertools import islice
                    files = sorted((Path(summary["output_dir"]) / "branches").glob("*.csv"))
                    show = list(islice(files, 20))
                    for p in show:
                        st.write(p.name)
                    if len(files) > 20:
                        st.caption(f"...and {len(files)-20} more")
                except Exception:
                    pass

            with st.expander("⚡ Branchwise Mix Groups", expanded=False):
                st.write("CSV files saved under: branch_wise_mix/")
                st.code(str(Path(summary["output_dir"]) / "branch_wise_mix"))
                try:
                    files = sorted((Path(summary["output_dir"]) / "branch_wise_mix").glob("G*.csv"))
                    st.caption(f"{len(files)} group files")
                except Exception:
                    pass

            with st.expander("⚡ Uniform Mix Groups", expanded=False):
                st.write("CSV files saved under: uniform_mix/")
                st.code(str(Path(summary["output_dir"]) / "uniform_mix"))
                try:
                    files = sorted((Path(summary["output_dir"]) / "uniform_mix").glob("G*.csv"))
                    st.caption(f"{len(files)} group files")
                except Exception:
                    pass

            with st.expander("📊 Statistics", expanded=False):
                stats_path = Path(summary["output_dir"]) / "stats" / "stats.csv"
                st.code(str(stats_path))
                try:
                    df_stats = pd.read_csv(stats_path)
                    st.dataframe(df_stats, use_container_width=True)
                except Exception as e:
                    st.warning(f"Could not load stats.csv: {e}")

            with st.expander("📦 Download All Outputs", expanded=False):
                try:
                    archive_base = str(Path(summary["output_dir"]))
                    zip_path = shutil.make_archive(archive_base, "zip", root_dir=summary["output_dir"])
                    with open(zip_path, "rb") as f:
                        st.download_button(
                            label="Download outputs (ZIP)",
                            data=f,
                            file_name=Path(zip_path).name,
                            mime="application/zip",
                        )
                except Exception as e:
                    st.warning(f"ZIP creation failed: {e}")

        except Exception as e:
            st.error(f"Error: {e}")
