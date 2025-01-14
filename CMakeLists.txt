cmake_minimum_required(VERSION 3.20.0)
project(Snake VERSION 0.1.0 LANGUAGES C CXX)

#build type
# default release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

# Debug-specific options
#set(DEBUG_OPTIONS "-g2")

# Release-specific options
#set(RELEASE_OPTIONS "-O3")

IF(UNIX AND NOT APPLE)
    set(LINUX TRUE)
ENDIF()

#include SFML
set(SFML_INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/include/SFML/")
include_directories(${SFML_INCLUDE})

IF (LINUX)
#   lib SFML LINUX
    set (SFML_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/Linux/lib")   
    #release lib
    IF (CMAKE_BUILD_TYPE STREQUAL "Release")
        set (SFML_ALL_LIB "${SFML_LIB_PATH}/libsfml-window.so.2.6.1" 
        "${SFML_LIB_PATH}/libsfml-system.so.2.6.1"
        "${SFML_LIB_PATH}/libsfml-graphics.so.2.6.1"
        "${SFML_LIB_PATH}/libsfml-audio.so.2.6.1"

        "${SFML_LIB_PATH}/libsfml-window.so.2.6" 
        "${SFML_LIB_PATH}/libsfml-system.so.2.6"
        "${SFML_LIB_PATH}/libsfml-graphics.so.2.6"
        "${SFML_LIB_PATH}/libsfml-audio.so.2.6")
        set(SFML_DEPENDENCY ${SFML_ALL_LIB})
    ENDIF()
    #debug lib
    IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
        set (SFML_ALL_LIB "${SFML_LIB_PATH}/libsfml-window-d.so.2.6.1"
        "${SFML_LIB_PATH}/libsfml-system-d.so.2.6.1"
        "${SFML_LIB_PATH}/libsfml-graphics-d.so.2.6.1"
        "${SFML_LIB_PATH}/libsfml-audio-d.so.2.6.1"
        
        "${SFML_LIB_PATH}/libsfml-window-d.so.2.6"
        "${SFML_LIB_PATH}/libsfml-system-d.so.2.6"
        "${SFML_LIB_PATH}/libsfml-graphics-d.so.2.6"
        "${SFML_LIB_PATH}/libsfml-audio-d.so.2.6")
        set(SFML_DEPENDENCY ${SFML_ALL_LIB})
    ENDIF()

    set(CMAKE_INSTALL_RPATH ".")
    set(CMAKE_BUILD_WITH_INSTALL_RPATH true)
ENDIF()

#windows lib
IF (WIN32)
    IF (CMAKE_BUILD_TYPE STREQUAL "Debug")
        # static lib(lib) SFML Windows
        set(SFML_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/Windows/lib")
        set(SFML_ALL_LIB "${SFML_LIB_PATH}/sfml-window-d.lib"
        "${SFML_LIB_PATH}/sfml-system-d.lib"
        "${SFML_LIB_PATH}/sfml-network-d.lib"
        "${SFML_LIB_PATH}/sfml-main-d.lib"
        "${SFML_LIB_PATH}/sfml-graphics-d.lib"
        "${SFML_LIB_PATH}/sfml-audio-d.lib"
        "${SFML_LIB_PATH}/vorbis.lib"
        "${SFML_LIB_PATH}/openal32.lib"
        "${SFML_LIB_PATH}/ogg.lib" 
        "${SFML_LIB_PATH}/freetype.lib"
        "${SFML_LIB_PATH}/flac.lib"
        "${SFML_LIB_PATH}/vorbisenc.lib"
        "${SFML_LIB_PATH}/vorbisfile.lib")

        #dynamic lib(dll) Windows
        set(SFML_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/Windows/bin")
        set(SFML_ALL_DLL "/sfml-window-d-2.dll"
        "/sfml-system-d-2.dll"
        "/sfml-network-d-2.dll"
        "/sfml-graphics-d-2.dll"
        "/sfml-audio-d-2.dll"
        "/openal32.dll")
    ENDIF()

    IF (CMAKE_BUILD_TYPE STREQUAL "Release")
        # static lib(lib) SFML Windows
        set(SFML_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/Windows/lib")
        set(SFML_ALL_LIB "${SFML_LIB_PATH}/sfml-window.lib"
        "${SFML_LIB_PATH}/sfml-system.lib"
        "${SFML_LIB_PATH}/sfml-network.lib"
        "${SFML_LIB_PATH}/sfml-main.lib"
        "${SFML_LIB_PATH}/sfml-graphics.lib"
        "${SFML_LIB_PATH}/sfml-audio.lib"
        "${SFML_LIB_PATH}/vorbis.lib"
        "${SFML_LIB_PATH}/openal32.lib"
        "${SFML_LIB_PATH}/ogg.lib"
        "${SFML_LIB_PATH}/freetype.lib"
        "${SFML_LIB_PATH}/flac.lib"
        "${SFML_LIB_PATH}/vorbisenc.lib"
        "${SFML_LIB_PATH}/vorbisfile.lib")

        #dynamic lib(dll) Windows
        set(SFML_LIB_PATH "${CMAKE_CURRENT_SOURCE_DIR}/Dependency/SFML-2.6.1/Windows/bin")
        set(SFML_ALL_DLL "/sfml-window-2.dll"
        "/sfml-system-2.dll"
        "/sfml-network-2.dll"
        "/sfml-graphics-2.dll"
        "/sfml-audio-2.dll"
        "/openal32.dll")
    ENDIF()

    #stupid fix
    set(SFML_DEPENDENCY "${SFML_LIB_PATH}/sfml-window-2.dll"
    "${SFML_LIB_PATH}/sfml-window-2.dll"
    "${SFML_LIB_PATH}/sfml-system-2.dll"
    "${SFML_LIB_PATH}/sfml-graphics-2.dll")


ENDIF()

add_executable(Snake main.cpp)

# compiler flags based on the build type
IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(Snake PRIVATE ${DEBUG_OPTIONS})
ELSEIF(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_compile_options(Snake PRIVATE ${RELEASE_OPTIONS})
ENDIF()

#link and compile
target_link_libraries(Snake PRIVATE ${SFML_ALL_LIB})
target_compile_features(Snake PRIVATE cxx_std_20)

#dll copy
FOREACH( DLL  ${SFML_ALL_DLL})
     add_custom_command(
        TARGET Snake PRE_BUILD
         COMMAND ${CMAKE_COMMAND} -E copy 
         "${SFML_LIB_PATH}${DLL}" 
         "$<TARGET_FILE_DIR:Snake>${DLL}"
   )

ENDFOREACH()

#Font copy
set(FontPath "Font/ArialCE.ttf" )
add_custom_command(
    TARGET Snake PRE_BUILD
     COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/${FontPath}" 
     "$<TARGET_FILE_DIR:Snake>/${FontPath}"
)

#install
set(CMAKE_INSTALL_PREFIX "${CMAKE_BINARY_DIR}/install" CACHE PATH "Installation Directory" FORCE)
install(FILES ${SFML_DEPENDENCY}   DESTINATION bin)
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/${FontPath}"  DESTINATION bin/Font)
install(TARGETS Snake RUNTIME DESTINATION bin)
install(FILES "$<TARGET_RUNTIME_DLLS:Snake>" DESTINATION bin)
 

#CPack zip
set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_NAME "OMSnake")
set(CPACK_PACKAGE_VENDOR "Lol.org")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "OMSNake - game snake")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "CPack Component Example")
SET(CPACK_NSIS_MODIFY_PATH ON)
INCLUDE(CPack)