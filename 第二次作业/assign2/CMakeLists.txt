cmake_minimum_required(VERSION 2.8)
project(problem_2)
set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV 4 REQUIRED)

include_directories(${OPENCV_INCLUDE_DIRS})
set(SOURCE_FILES assign2.cpp )


add_executable(problem_2 ${SOURCE_FILES})
target_link_libraries(problem_2 ${OpenCV_LIBS})
