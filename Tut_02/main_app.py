import pandas as pd
import streamlit as st
import logging
import io

# ------------------ STEP 1: Configure Logging ------------------
logging.basicConfig(
    filename='app.log',
    level=logging.INFO,
    format='%(asctime)s - %(levelname)s - %(message)s'
)

# Set Streamlit page config for better look
st.set_page_config(
    page_title="BTP/MTP Allocation System",
    layout="wide",
    initial_sidebar_state="collapsed"
)

# Nice HTML heading
st.markdown(
    """
    <h1 style='text-align: center; color: #00B4D8;'>🚀 BTP/MTP Allocation System <br>
    <span style="font-size:22px; color:#48CAE4;">Assignment 2</span></h1>
    """,
    unsafe_allow_html=True,
)

st.markdown(
    "<hr style='border:2px solid #00B4D8;'>",
    unsafe_allow_html=True
)

with st.container():
    col1, col2 = st.columns([1, 2])
    with col1:
        st.markdown(
            """
            <h3 style="color:#48CAE4;">Instructions</h3>
            <ul style="color:#adb5bd; font-size:16px;">
                <li>Upload your CSV file containing allocation data.</li>
                <li>Download processed results instantly.</li>
                <li>All computation is secure and local.</li>
            </ul>
            """, unsafe_allow_html=True
        )
    with col2:
        uploaded_file = st.file_uploader("⬆️ <b>Upload Input File</b>", type=["csv"], key="fileUploader", label_visibility="hidden")

def process_file(uploaded_file):
    try:
        df = pd.read_csv(uploaded_file)
        logging.info("CSV file loaded successfully.")

        # Identify faculty columns dynamically
        cgpa_index = df.columns.get_loc("CGPA")
        faculty_cols = df.columns[cgpa_index + 1:]
        n = len(faculty_cols)
        logging.info(f"Detected {n} faculty columns: {list(faculty_cols)}")

        # Sort by CGPA
        df_sorted = df.sort_values(by="CGPA", ascending=False).reset_index(drop=True)
        total_students = len(df_sorted)

        # Allocate Students
        allocations = [faculty_cols[i % n] for i in range(total_students)]
        df_sorted["Allocated"] = allocations

        # Allocation output
        allocation_output = df_sorted[["Roll", "Name", "Email", "CGPA", "Allocated"]]
        allocation_csv = allocation_output.to_csv(index=False)

        # Faculty Preference Count
        pref_data = []
        for fac in faculty_cols:
            pref_counts = [(df[fac] == pref_no).sum() for pref_no in range(1, len(faculty_cols) + 1)]
            pref_data.append(pref_counts)

        pref_df = pd.DataFrame(pref_data, columns=[f"Pref {i+1} Count" for i in range(len(faculty_cols))])
        pref_df.insert(0, "Faculty", faculty_cols)
        pref_csv = pref_df.to_csv(index=False)
        logging.info("Created faculty preference count successfully")

        return allocation_csv, pref_csv, allocation_output, pref_df

    except Exception as e:
        logging.error(f"File Processing Error: {str(e)}")
        st.error(f"Error: {e}")
        return None, None, None, None

if uploaded_file is not None:
    with st.spinner("🔄 Processing... Please wait."):
        allocation_csv, pref_csv, allocation_output, pref_df = process_file(uploaded_file)

    if allocation_csv and pref_csv:
        st.success("✅ Processing completed successfully!")
        st.balloons()

        with st.expander("📋 View Sample Allocation Output"):
            st.dataframe(allocation_output.head(8), hide_index=True, use_container_width=True)
            st.download_button(
                label="⬇️ Download Allocation File",
                data=allocation_csv,
                file_name="btp_mtp_allocation.csv",
                mime="text/csv"
            )

        with st.expander("📊 Faculty Preference Count Table"):
            st.dataframe(pref_df.head(8), hide_index=True, use_container_width=True)
            st.download_button(
                label="⬇️ Download Faculty Preference File",
                data=pref_csv,
                file_name="fac_preference_count.csv",
                mime="text/csv"
            )
else:
    st.markdown(
        "<p style='color: #adb5bd; font-size:18px;'>Please upload the input CSV file to begin processing.</p>",
        unsafe_allow_html=True
    )