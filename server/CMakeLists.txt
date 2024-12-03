cmake_minimum_required(VERSION 3.10)

project(CloudDriveServer)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Debug)
find_package(fmt REQUIRED)
include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)
include_directories(
    ./ThreadPool/include
    ./QuickTool/include
)
file(GLOB_RECURSE source
    ./ThreadPool/src/*.*
    ./QuickTool/src/*.*
)
add_executable(CloudDriveServer ./main.cpp ${source})

target_link_libraries(CloudDriveServer fmt::fmt)