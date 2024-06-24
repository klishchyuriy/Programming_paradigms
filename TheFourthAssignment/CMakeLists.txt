cmake_minimum_required(VERSION 3.28)
project(TheFourthAssignment)

set(CMAKE_CXX_STANDARD 20)

# Ensure paths to source files are correct
add_library(caesar SHARED caesar.cpp)

add_executable(TheFourthAssignment main.cpp text_editor.cpp caesar_cipher.cpp
        text_editor.cpp
        text_editor.h)

set_target_properties(caesar PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        OUTPUT_NAME "caesar"
)

set_target_properties(TheFourthAssignment PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        BUILD_RPATH ${CMAKE_BINARY_DIR}
)

target_link_libraries(TheFourthAssignment PRIVATE caesar)
