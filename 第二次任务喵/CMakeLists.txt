cmake_minimum_required(VERSION 3.0.0)
project(task)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
find_package(OpenCV REQUIRED)
find_package(Ceres REQUIRED)

aux_source_directory(./src ALL_SRCS)
include_directories(include
${OpenCV_INCLUDE_DIRS}${CERES_INCLUDE_DIRS})

set(SRC ./cc)

add_executable(task main.cpp ${ALL_SRCS})
target_link_libraries(task ${OpenCV_LIBS} ${CERES_LIBRARIES})