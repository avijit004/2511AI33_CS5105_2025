# Use official Python image
FROM python:3.10-slim

# Prevent Python from buffering stdout
ENV PYTHONUNBUFFERED=1

# Create app directory
WORKDIR /app

# Install system dependencies for ReportLab (important!)
RUN apt-get update && apt-get install -y \
    libcairo2-dev \
    libjpeg62-turbo-dev \
    libpng-dev \
    libfreetype6-dev \
    && rm -rf /var/lib/apt/lists/*

# Copy app files
COPY . /app

# Install Python dependencies
RUN pip install --no-cache-dir -r requirements.txt

# Expose Streamlit default port
EXPOSE 8501

# Streamlit config to allow external access
RUN mkdir -p ~/.streamlit
RUN bash -c 'echo -e "\
[server]\n\
headless = true\n\
enableCORS = false\n\
port = 8501\n\
" > ~/.streamlit/config.toml'

# Run Streamlit app

CMD ["streamlit", "run", "app.py"]
