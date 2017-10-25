cmake_minimum_required(VERSION 3.8)
project(MLFQS)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES prioque.c prioque.h  input mlfqs.c mlfqs.c mlfqs.c)
add_executable(MLFQS ${SOURCE_FILES})