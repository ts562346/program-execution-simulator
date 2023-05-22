cmake_minimum_required(VERSION 3.16)
project(prosim C)

set(CMAKE_C_STANDARD 11)

add_executable(prosim main.c stack.h linked_list.h stack.c linked_list.c)

