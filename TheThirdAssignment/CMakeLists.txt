cmake_minimum_required(VERSION 3.28)
project(TheThirdAssignment)

set(CMAKE_CXX_STANDARD 20)

# Додати цільову бібліотеку
add_library(caesar SHARED caesar.cpp)

# Додати цільовий виконуваний файл
add_executable(TheThirdAssignment main.cpp)

# Встановити властивості для бібліотеки
set_target_properties(caesar PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
)

# Встановити властивості для виконуваного файлу
set_target_properties(TheThirdAssignment PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}
        BUILD_RPATH ${CMAKE_BINARY_DIR}
)

# Зв'язати бібліотеку з виконуваним файлом
target_link_libraries(TheThirdAssignment PRIVATE caesar)

