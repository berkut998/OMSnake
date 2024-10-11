cmake_minimum_required(VERSION 3.5.0)
project(Snake VERSION 0.1.0 LANGUAGES C CXX)

#build type
# default release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Debug-specific options
set(DEBUG_OPTIONS "-g3")

# Release-specific options
set(RELEASE_OPTIONS "-O3")



set(SFML_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/include/SFML/")
include_directories(${SFML_INCLUDE})
set (SFML_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/lib/")

#release dll
IF (CMAKE_BUILD_TYPE STREQUAL "Release")
    set (SFML_ALL_LIB "${SFML_LIB_PATH}/libsfml-window.so" 
    "${SFML_LIB_PATH}/libsfml-system.so"
    "${SFML_LIB_PATH}/libsfml-graphics.so"
    "${SFML_LIB_PATH}/libsfml-audio.so")
ENDIF()
#debug dll
IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set (SFML_ALL_LIB "${SFML_LIB_PATH}/libsfml-window-d.so" 
    "${SFML_LIB_PATH}/libsfml-system-d.so"
    "${SFML_LIB_PATH}/libsfml-graphics-d.so"
    "${SFML_LIB_PATH}/libsfml-audio-d.so")
ENDIF()

#debug lib .a not working?
# IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
#     set (SFML_ALL_LIB "${SFML_LIB_PATH}/libsfml-window-s-d.a" 
#     "${SFML_LIB_PATH}/libsfml-system-s-d.a"
#     "${SFML_LIB_PATH}/libsfml-graphics-s-d.a"
#     "${SFML_LIB_PATH}/libsfml-audio-s-d.a")
# ENDIF()
add_executable(Snake main.cpp)

# compiler flags based on the build type
IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Snake PRIVATE ${DEBUG_OPTIONS})
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Snake PRIVATE ${RELEASE_OPTIONS})
ENDIF()

target_link_libraries(Snake PRIVATE ${SFML_ALL_LIB})
target_compile_features(Snake PRIVATE cxx_std_17)


file(GLOB SFML_dll myDir/*.so)
foreach(CurrentHeaderFile IN LISTS MY_HEADERS)
    add_custom_command(
                TARGET MyTarget PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy_if_different ${CurrentHeaderFile} ${myDestination}
                COMMENT "Copying header: ${CurrentHeaderFile}")
endforeach()


#Font copy
set(FontPath "Font/ArialCE.ttf" )
message(FontPath=="${CMAKE_CURRENT_SOURCE_DIR}/${FontPath}")
message(FontPath=="${CMAKE_CURRENT_BINARY_DIR}/${FontPath}")
add_custom_command(
    TARGET Snake POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${FontPath}"
    "${CMAKE_CURRENT_BINARY_DIR}/${FontPath}"
    COMMENT "copy font")