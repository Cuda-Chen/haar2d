cmake_minimum_required(VERSION 2.8)

project(haar2d)

set(EXECUTABLE_OUTPUT_PATH "..")
set(DEBUG_BUILD_TYPE Debug)

find_package(OpenCV REQUIRED)

add_executable(haar2d main.cpp)

target_link_libraries(haar2d ${OpenCV_LIBS})

