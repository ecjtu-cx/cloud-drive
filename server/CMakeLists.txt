cmake_minimum_required(VERSION 3.10)

project(CloudDriveServer)

include_directories(${PROJECT_SOURCE_DIR}/ThreadPool/include)
file(GLOB SOURCES ${PROJECT_SOURCE_DIR}/ThreadPool/src/*.cpp)

add_executable(CloudDriveServer ${SOURCES})

add_library(CloudDriveServer fmt::fmt)