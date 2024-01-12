cmake_minimum_required(VERSION 3.27)
project(Hospitals)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_PREFIX_PATH "C:/Qt/5.15.16/mingw81_64")

# Dodaj wszystkie pliki źródłowe z folderu 'src'
file(GLOB SRC_FILES src/*.cpp)

# Dodaj wszystkie pliki nagłówkowe z folderu 'include'
file(GLOB HEADER_FILES include/*.hpp)

# Dodaj pliki źródłowe i nagłówkowe do projektu
add_executable(Hospitals main.cpp include/tabu.hpp scr/tabu.cpp include/structures.hpp
        scr/structures.cpp include/ui_window.h include/window.hpp scr/window.cpp
        )

# Dodaj ścieżki do folderów include
target_include_directories(Hospitals PRIVATE include)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
find_package(Qt5Widgets REQUIRED)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

target_link_libraries(Hospitals Qt5::Core Qt5::Widgets)

include_directories( C:\\Qt\\Tools\\QtCreator\\
                   C:\\Qt\\5.15.2\\mingw81_64\\
                     C:\\Qt\\Tools\\mingw810_64\\bin)


if (WIN32 AND NOT DEFINED CMAKE_TOOLCHAIN_FILE)
    set(DEBUG_SUFFIX)
    if (MSVC AND CMAKE_BUILD_TYPE MATCHES "Debug")
        set(DEBUG_SUFFIX "d")
    endif ()
    set(QT_INSTALL_PATH "${CMAKE_PREFIX_PATH}")
    if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
        set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        if (NOT EXISTS "${QT_INSTALL_PATH}/bin")
            set(QT_INSTALL_PATH "${QT_INSTALL_PATH}/..")
        endif ()
    endif ()
    if (EXISTS "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E make_directory
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/plugins/platforms/qwindows${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>/plugins/platforms/")
    endif ()
    foreach (QT_LIB Core Gui Widgets)
        add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy
                "${QT_INSTALL_PATH}/bin/Qt5${QT_LIB}${DEBUG_SUFFIX}.dll"
                "$<TARGET_FILE_DIR:${PROJECT_NAME}>")
    endforeach (QT_LIB)
endif ()
