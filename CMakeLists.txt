cmake_minimum_required(VERSION 3.21)
project(Hospitals)

set(CMAKE_CXX_STANDARD 14)

# Dodaj wszystkie pliki źródłowe z folderu 'src'
file(GLOB SRC_FILES src/*.cpp)

# Dodaj wszystkie pliki nagłówkowe z folderu 'include'
file(GLOB HEADER_FILES include/*.hpp)

# Dodaj pliki źródłowe i nagłówkowe do projektu
add_executable(Hospitals main.cpp include/tabu.hpp scr/tabu.cpp scr/window.cpp include/window.hpp include/structures.hpp scr/structures.cpp)

# Dodaj ścieżki do folderów include
target_include_directories(Hospitals PRIVATE include)
