Project Title: Streamlit Application with Docker Deployment

Description:
This project contains two versions of a Streamlit application (main_app.py and main_app2.py) along with configuration files for Docker containerization and deployment.

Files:
1. main_app.py - Primary Streamlit application script.
2. main_app2.py - Alternative or extended version of the Streamlit app.
3. docker-compose.yml - Docker Compose configuration file to build and run the app container.
4. requirements.txt - Python dependencies required to run the Streamlit app.
5. app.log - Log file containing runtime logs for troubleshooting.

Setup and Installation:
1. Ensure Docker and Docker Compose are installed on your system.
2. Clone or download the project files.
3. (Optional) For manual setup without Docker, create a Python virtual environment and install dependencies:
python -m venv venv
source venv/bin/activate # On Windows use venv\Scripts\activate
pip install -r requirements.txt
4. To run the application manually, execute: streamlit run main_app2.py

Running with Docker:
1. Build and start the container using Docker Compose: docker-compose up --build
2. Access the Streamlit app at: http://localhost:8501

Logs:
- The app generates logs in app.log for debugging and monitoring.

Notes:
- The entrypoint script or command used in Docker Compose launches the appropriate Streamlit app.
- Modify the docker-compose.yml file to switch between main_app.py and main_app2.py if needed.

For any issues, consult the app.log or Docker container logs.

---

End of README
