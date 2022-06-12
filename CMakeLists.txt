cmake_minimum_required(VERSION 3.22)
project(hamming_code_generator C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(hamming_code_generator
        binary_code.h
        main.c)
