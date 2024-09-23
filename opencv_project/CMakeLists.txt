cmake_minimum_required(VERSION 3.10)
project(opencv_project)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_executable(opencv_project src/main.cpp)
target_link_libraries(opencv_project ${OpenCV_LIBS})