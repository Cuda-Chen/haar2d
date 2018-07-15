cmake_minimum_required(VERSION 2.8)

project(haar2d)

set(EXECUTABLE_OUTPUT_PATH "..")
set(CMAKE_BUILD_TYPE Debug)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

find_package(OpenCV REQUIRED)

add_executable(haar2d main.cpp)

target_link_libraries(haar2d ${OpenCV_LIBS})

