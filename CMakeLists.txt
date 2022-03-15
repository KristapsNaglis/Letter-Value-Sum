cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME letter_value_sum)
project(${PROJECT_NAME})

set(SRC_DIR src)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES ${SRC_DIR}/main.cpp ${SRC_DIR}/Wordlist.cpp)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
