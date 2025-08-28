Tutorial 01 — Student Grouping and Statistics
Generates Branchwise Mix (iterator-based) and Uniform Mix groups, plus per-branch stats.

Contents:
1.tut01.py-Core script
2.requirements.txt-Dependencies (pandas, openpyxl, streamlit)
3.input_Make-Groups.xlsx-Sample input
4.Readme.txt-This guide

Setup:
1.Install Python 3.9+.
2.From this folder:
  2.1pip install -r requirements.txt

Input:
1. .xlsx (Excel): sheet with columns Roll, Name, Email (case-insensitive; “Roll No.” variants OK).
2. .csv (CSV): columns Roll, Name, Email (variants OK).
3. Branch is auto-derived from Roll characters 5–6 (e.g., 1401AI23 → AI).

    A) Run from Command Line
    1.Open terminal and cd to this folder.
    2.Example (Excel):
        python tut01.py --input input_Make-Groups.xlsx --sheet Sheet1 --output output
    3.When prompted, enter group counts (e.g., 3 and 3).
    4.Output directory is cleared each run.
    
    Outputs (in output/):
    input_copy.csv
    branches/ one CSV per branch
    branch_wise_mix/ G1..Gk.csv (Branchwise Mix)
    uniform_mix/ G1..Gk.csv (Uniform Mix)
    stats/stats.csv sections “Branchwise Mix” and “Uniform Mix”
    params.json run metadata


    B) Run with Streamlit (UI)
    1.Ensure deps installed:
        pip install -r requirements.txt
    2.From project root (where app.py can import tut01):
        streamlit run app.py
    3.In the browser:
        Upload CSV/XLSX (for XLSX, set sheet name).
        Set groups (default 3 each).
        Choose output directory (cleared each run) and Generate.
        Use sections to view branch files, group files, stats, and download ZIP.

Reproducibility:
params.json logs input, sheet, output path, group counts, and timestamp.


