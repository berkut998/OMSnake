cmake_minimum_required(VERSION 3.5.0)
project(Snake VERSION 0.1.0 LANGUAGES C CXX)

set(SFML_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/include/SFML/")
include_directories(${SFML_INCLUDE})
set (SFML_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/lib/")
set (SFML_ALL_LIB "${SFML_LIB_PATH}/libsfml-window.so" 
"${SFML_LIB_PATH}/libsfml-system.so"
"${SFML_LIB_PATH}/libsfml-graphics.so"
"${SFML_LIB_PATH}/libsfml-audio.so")

add_executable(Snake main.cpp)
target_link_libraries(Snake PRIVATE ${SFML_ALL_LIB})
target_compile_features(Snake PRIVATE cxx_std_17)

