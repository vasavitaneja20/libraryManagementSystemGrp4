# Use an official Ubuntu image as a base
FROM ubuntu:latest

# Install necessary packages (basic tools for C++ projects)
RUN apt-get update && apt-get install -y \
    g++ \
    make \
    cmake

# Set the working directory inside the container
WORKDIR /app

# Copy your project files into the container
COPY . /app

# Build the C++ application
RUN g++ -o library_management code_LMS.cpp

# Specify the command to run your app
CMD ["./library_management"]
