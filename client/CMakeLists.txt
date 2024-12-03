cmake_minimum_required(VERSION 3.10)

project(CloudDriveClient)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
add_executable(CloudDriveClient ./client.cpp)