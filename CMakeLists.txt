cmake_minimum_required(VERSION 3.23)
project(rbt C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_FLAGS "-fsanitize=address,undefined -static-libsan")

add_executable(rbt main.c)
