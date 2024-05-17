cmake_minimum_required(VERSION 3.28)
project(TheFirstAssignment C)

set(CMAKE_C_STANDARD 23)

add_executable(TheFirstAssignment main.c
        text_editor.cpp
        text_editor.h)
