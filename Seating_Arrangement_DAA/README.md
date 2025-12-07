🎓 Seating Arrangement – Automated Exam Seating System

📹 Full Demo Video
👉 https://youtu.be/1xxJfsajEug

📖 Project Overview
Seating Arrangement is an automated exam seating allocation system built using Python, with an optional Streamlit web interface and Docker deployment.
It aims to:
✔ Automatically place students in rooms
✔ Respect room capacities
✔ Separate students from same batches/courses
✔ Provide transparent logs for debugging
✔ Offer a user-friendly web UI for faculty


🧩 Features
🔹 1. Intelligent Seating Allocation:
Reads Excel/CSV student + room data
Distributes students optimally
Avoids clustering of same-class students

🔹 2. Streamlit Web UI:
Upload input data
Generate seating plan
Visual layout & table view
No coding required

🔹 3. Full Logging System:
app.log → Application events
seating_alloc.log → Allocation logic
errors.txt → Debugging trace

🔹 4. Docker Support (One-Click Deploy):
Works on any system
No Python installation needed

📁 Project Structure
Seating-Arrangement/
│── app.py                 # Core algorithm
│── streamlit.py           # Streamlit UI
│── input_data.xlsx        # Sample student/room data
│── requirements.txt       # Dependencies
│── Dockerfile             # Docker image build
│── docker-compose.yml     # Compose setup
│── app.log                # Application logs
│── seating_alloc.log      # Allocation logs
│── errors.txt             # Error logs (if any)
│── no_image_available.png # UI placeholder
└── README.md


🛠️ Installation & Setup
1️⃣ Clone the Repository
git clone https://github.com/avijit004/DAA_ASSINGMENT_SEATING_ARRANGEMENT.git
cd DAA_ASSINGMENT_SEATING_ARRANGEMENT


2️⃣ Create a Virtual Environment
macOS / Linux
python3 -m venv .venv
source .venv/bin/activate

Windows
python -m venv .venv
.venv\Scripts\activate

3️⃣ Install Dependencies
pip install --upgrade pip
pip install -r requirements.txt

▶️ Running the Application
A. Run Core Python Script
python app.py


This loads student data, generates seating, and writes logs.

B. Run Streamlit Web App
streamlit run streamlit.py

Then open:

👉 http://localhost:8501

💡 Web UI Features:
Upload input_data.xlsx
Modify settings
Generate seating
View results as tables


🐳 Docker Support
Build Docker Image:
docker build -t seating-app .

Run Container:
docker run -p 8501:8501 seating-app

Or Use Docker Compose:
docker-compose up --build


Now visit:
👉 http://localhost:8501


🧪 Input Format (Excel Template)
Sheet must contain:
Student Name
Roll Number
Course / Batch
Room Allocation Priority (optional)
Room Capacity sheet


🧯 Troubleshooting
❌ Errors when running app?

Check:
errors.txt
seating_alloc.log
Excel column formatting

❌ Streamlit not starting?
Run:
pip install streamlit

❌ Docker failure?
Rebuild:
docker-compose up --build


🧠 Future Enhancements
✨ Add visual seat map
✨ Generate printable PDF seating charts
✨ Support multiple exams / sessions
✨ Auto-email seat allotments to students
✨ Admin dashboard for bulk uploads


