cmake_minimum_required(VERSION 3.15)
project(lab1_es07 C)

set(CMAKE_C_STANDARD 99)

add_executable(lab1_es07 main.c)

target_link_libraries(${PROJECT_NAME} pthread)
