# Use an official Ubuntu image as a base
FROM ubuntu:latest

# Install necessary packages
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    cmake \
    libwhatever-dev  # Replace with any additional libraries your project needs

# Set the working directory inside the container
WORKDIR /app

# Copy your project files into the container
COPY . /app

# Build the C++ application
RUN g++ -o library_management code_LMS.cpp -lwhatever  # Replace with the correct linking flags if needed

# Specify the command to run your app
CMD ["./library_management"]
