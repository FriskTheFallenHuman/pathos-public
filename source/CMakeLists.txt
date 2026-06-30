cmake_minimum_required(VERSION 3.16)

# Prevent in-source builds
if("${CMAKE_BINARY_DIR}" STREQUAL "${CMAKE_SOURCE_DIR}")
    message(FATAL_ERROR "In-source builds are not permitted! Make sure to use a separate build directory")
endif ()

project(PathosEngine VERSION 1.0.0 LANGUAGES CXX C)

option(USE_SYSTEM_LIBS "Prefer system-installed libraries over FetchContent" OFF)

if(USE_SYSTEM_LIBS)
	set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
endif()

include(CompilationSettings.cmake)

macro(SET_FORCED_OPTION option value)
    set(${option} ${value} CACHE INTERNAL "" FORCE)
endmacro()

include(FetchContent)
macro(find_or_fetch PACKAGE_NAME)
    if(USE_SYSTEM_LIBS)
        find_package(${PACKAGE_NAME} REQUIRED)
        include_directories(${${PACKAGE_NAME}_INCLUDE_DIRS})
    else()
        find_package(${PACKAGE_NAME} QUIET)
        if(NOT ${PACKAGE_NAME}_FOUND)
            message(STATUS "Fetching ${PACKAGE_NAME}")
            FetchContent_Declare(
                ${PACKAGE_NAME}
                ${ARGN}
            )
            FetchContent_MakeAvailable(${PACKAGE_NAME})
            FetchContent_GetProperties(${PACKAGE_NAME})

            include_directories(${${PACKAGE_NAME}_SOURCE_DIR}/include ${${PACKAGE_NAME}_BINARY_DIR}/include)
        endif()
    endif()
endmacro()

# SDL2
SET_FORCED_OPTION(SDL_STATIC OFF)
SET_FORCED_OPTION(SDL_TEST OFF)
if(MSVC)
    SET_FORCED_OPTION(SDL_JOYSTICK_XINPUT ON)
endif()

find_or_fetch(SDL2
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG release-2.30.10)

# OpenAL
SET_FORCED_OPTION(ALSOFT_NO_CONFIG_UTIL OFF)
SET_FORCED_OPTION(ALSOFT_UTILS OFF)
SET_FORCED_OPTION(ALSOFT_EXAMPLES OFF)
SET_FORCED_OPTION(ALSOFT_TESTS OFF)
SET_FORCED_OPTION(ALSOFT_INSTALL_UTILS OFF)
SET_FORCED_OPTION(ALSOFT_INSTALL_EXAMPLES OFF)
SET_FORCED_OPTION(ALSOFT_INSTALL_AMBDEC_PRESETS OFF)
SET_FORCED_OPTION(ALSOFT_INSTALL_HRTF_DATA OFF)
SET_FORCED_OPTION(ALSOFT_INSTALL_CONFIG OFF)
SET_FORCED_OPTION(ALSOFT_INSTALL OFF)

find_or_fetch(OpenAL
    GIT_REPOSITORY https://github.com/kcat/openal-soft.git
    GIT_TAG 1.25.2)

# Freetype
find_or_fetch(Freetype
    GIT_REPOSITORY https://github.com/freetype/freetype.git
    GIT_TAG VER-2-14-3)

if(NOT TARGET Freetype::Freetype)
    add_library(Freetype::Freetype ALIAS freetype)
endif()

include_directories(${freetype_SOURCE_DIR}/include/freetype ${freetype_BINARY_DIR}/include)

# Ogg
SET_FORCED_OPTION(INSTALL_DOCS OFF)
SET_FORCED_OPTION(BUILD_TESTING OFF)
if(CYGWIN)
    set(OGG_INCLUDE_DIR "/usr/include" CACHE PATH "" FORCE)
endif()

find_or_fetch(Ogg
    GIT_REPOSITORY https://github.com/xiph/ogg.git
    GIT_TAG v1.3.5)

if(NOT TARGET Ogg::ogg)
    add_library(Ogg::ogg ALIAS ogg)
endif()


# Vorbis
if(MSVC)
    set(OGG_INCLUDE_DIR "${Ogg_SOURCE_DIR}/include;${Ogg_BINARY_DIR}/include" CACHE PATH "" FORCE)
    set(OGG_LIBRARY ogg CACHE STRING "" FORCE)
endif()

find_or_fetch(Vorbis
    GIT_REPOSITORY https://github.com/xiph/vorbis.git
    GIT_TAG v1.3.7)

if(NOT TARGET Vorbis::vorbis)
    add_library(Vorbis::vorbis ALIAS vorbis)
    add_library(Vorbis::vorbisenc ALIAS vorbisenc)
    add_library(Vorbis::vorbisfile ALIAS vorbisfile)
endif()

# Enet
message(STATUS "Fetching ENet")
FetchContent_Declare(ENet
    GIT_REPOSITORY https://github.com/lsalzman/enet.git
    GIT_TAG v1.3.18)

FetchContent_MakeAvailable(ENet)
FetchContent_GetProperties(ENet)

if(NOT TARGET ENet::enet)
    add_library(ENet::enet ALIAS enet)
endif()

include_directories(${enet_SOURCE_DIR}/include)

# Detours (Windows only)
if(WIN32)
    FetchContent_Declare(detours
        GIT_REPOSITORY https://github.com/microsoft/Detours.git
        GIT_TAG v4.0.1)

    FetchContent_GetProperties(detours)
    if(NOT detours_POPULATED)
        FetchContent_Populate(detours)
    endif()

    add_library(detours STATIC
        ${detours_SOURCE_DIR}/src/detours.cpp
        ${detours_SOURCE_DIR}/src/modules.cpp
        ${detours_SOURCE_DIR}/src/disasm.cpp
        ${detours_SOURCE_DIR}/src/image.cpp
        ${detours_SOURCE_DIR}/src/creatwth.cpp
    )
    target_include_directories(detours PUBLIC ${detours_SOURCE_DIR}/src)
    target_compile_definitions(detours PRIVATE WIN32_LEAN_AND_MEAN)
    add_library(Detours::detours ALIAS detours)
endif()

find_package(OpenGL REQUIRED)

add_subdirectory(engine)
add_subdirectory(clientdll)
add_subdirectory(gamedll)
