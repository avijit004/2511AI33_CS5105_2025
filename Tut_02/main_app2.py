import streamlit as st
import pandas as pd
import logging

# Configure logger
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def process_allocation(df):
    try:
        # 1. Identify all faculty columns after 'CGPA'
        try:
            faculty_columns = df.columns[df.columns.get_loc('CGPA') + 1:]
        except KeyError:
            st.error("Error: Input CSV must contain a 'CGPA' column.")
            return None, None

        num_faculty = len(faculty_columns)
        logging.info(f"Detected {num_faculty} faculty columns dynamically.")

        # 2. Sort by CGPA descending for fair allocation
        df_sorted = df.sort_values(by='CGPA', ascending=False, kind='mergesort').reset_index(drop=True)

        total_students = len(df_sorted)
        base = total_students // num_faculty
        remainder = total_students % num_faculty

        # Build per-faculty capacity
        faculty_capacity = {faculty_columns[i]: base + (1 if i < remainder else 0) for i in range(num_faculty)}
        faculty_current = {f: 0 for f in faculty_columns}
        allocations = {}

        logging.info(f"Faculty target distributions: {faculty_capacity}")

        # 3. Strict mod-n round robin allocation by preferences
        fac_index = 0
        for idx, student in df_sorted.iterrows():
            assigned = False

            for pref_level in range(1, num_faculty + 1):
                # Priority sequence begins from fac_index to distribute load uniformly
                ordered_fac_list = list(faculty_columns[fac_index:]) + list(faculty_columns[:fac_index])

                for fac in ordered_fac_list:
                    try:
                        if int(student[fac]) == pref_level and faculty_current[fac] < faculty_capacity[fac]:
                            allocations[student['Roll']] = fac
                            faculty_current[fac] += 1
                            assigned = True
                            fac_index = (fac_index + 1) % num_faculty
                            break
                    except (ValueError, TypeError):
                        continue
                if assigned:
                    break

            if not assigned:
                # Assign to least loaded faculty if no preference available
                available_fac = min(faculty_current, key=lambda f: faculty_current[f])
                allocations[student['Roll']] = available_fac
                faculty_current[available_fac] += 1

        # 4. Create Output Allocation DataFrame
        output_df = df_sorted[['Roll', 'Name', 'Email', 'CGPA']].copy()
        output_df['Allocated Faculty'] = output_df['Roll'].map(allocations)
        output_df['Faculty Load'] = output_df['Allocated Faculty'].map(lambda x: faculty_current.get(x, 0))

        # 5. Create Faculty Preference Stats
        pref_stats = {f'Count Pref {i}': {fac: 0 for fac in faculty_columns} for i in range(1, num_faculty + 1)}
        for _, row in df.iterrows():
            for fac in faculty_columns:
                try:
                    pref = int(row[fac])
                    if 1 <= pref <= num_faculty:
                        pref_stats[f'Count Pref {pref}'][fac] += 1
                except (ValueError, TypeError):
                    continue

        fac_pref_df = pd.DataFrame(pref_stats)
        fac_pref_df['Total Assigned'] = fac_pref_df.index.map(lambda fac: faculty_current.get(fac, 0))
        fac_pref_df.index.name = 'Faculty'

        return output_df, fac_pref_df

    except Exception as e:
        logging.error(f"Error in allocation: {e}")
        st.error(f"Error in allocation: {e}")
        return None, None

def main():
    st.set_page_config(page_title="BTP/MTP Allocation System", layout="wide")
    st.title("🎓 Dynamic BTP/MTP Allocation System - Round Robin")

    st.sidebar.header("Instructions")
    st.sidebar.info(
        "1. Upload a CSV containing Roll, Name, Email, CGPA, then faculty columns.\n"
        "2. Students are allocated using fair mod-n round robin logic.\n"
        "3. Download both output CSVs after successful processing."
    )

    uploaded_file = st.file_uploader("📂 Upload Input CSV File", type=['csv'])

    if uploaded_file is not None:
        try:
            input_df = pd.read_csv(uploaded_file)
            st.success("File uploaded successfully!")
            st.dataframe(input_df.head())

            if st.button("🚀 Run Allocation"):
                with st.spinner('Processing allocation...'):
                    allocation_df, stats_df = process_allocation(input_df)

                if allocation_df is not None:
                    st.success("✅ Allocation Completed Successfully!")
                    st.info(f"Allocated {len(allocation_df)} / {len(input_df)} students.")

                    st.subheader("📊 Allocation Results")
                    st.dataframe(allocation_df)

                    st.subheader("📈 Faculty Preference Statistics")
                    st.dataframe(stats_df)

                    c1, c2 = st.columns(2)
                    with c1:
                        st.download_button(
                            label="📥 Download Allocation CSV",
                            data=allocation_df.to_csv(index=False).encode('utf-8'),
                            file_name='output_btp_mtp_allocation.csv',
                            mime='text/csv'
                        )
                    with c2:
                        st.download_button(
                            label="📥 Download Faculty Stats CSV",
                            data=stats_df.to_csv().encode('utf-8'),
                            file_name='fac_preference_count.csv',
                            mime='text/csv'
                        )
        except Exception as e:
            logging.error(f"Critical error while reading file: {e}")
            st.error(f"Critical error while reading file: {e}")

if __name__ == '__main__':
    main()