cmake_minimum_required(VERSION 3.10)

project(RLE-algorithm)

set(CMAKE_C_STANDARD 23)



file(GLOB SOURCES "src/*.c")
file(GLOB HEADERS "includes/*.h")

add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})
target_include_directories(${PROJECT_NAME} PRIVATE includes)
