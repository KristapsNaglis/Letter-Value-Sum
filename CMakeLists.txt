cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

set(PROJECT_NAME letter_value_sum)
project(${PROJECT_NAME})

set(SRC_DIR src)
set(STRUCT_DIR structures)
set(CMAKE_CXX_STANDARD 20)
set(SOURCE_FILES ${SRC_DIR}/main.cpp ${SRC_DIR}/wordlist.cpp ${SRC_DIR}/letterCalc.cpp ${SRC_DIR}/${STRUCT_DIR}/helperStructures.h ${SRC_DIR}/userInteractions.cpp ${SRC_DIR}/userInteractions.h ${SRC_DIR}/chronoTimer.cpp ${SRC_DIR}/chronoTimer.h)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})
