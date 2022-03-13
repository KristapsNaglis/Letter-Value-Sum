cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME letter_value_sum)
project(${PROJECT_NAME})

set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES main.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
