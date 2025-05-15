cmake_minimum_required(VERSION 3.7...3.27)

list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/CMake)

# --------------------------------------------------------------
# Project Configuration
# --------------------------------------------------------------

project(Man 
        LANGUAGES CXX C
        VERSION 0.0.1)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set_property(GLOBAL PROPERTY PREDEFINED_TARGETS_FOLDER "CMake")

add_compile_options("$<$<C_COMPILER_ID:MSVC>:/utf-8>")
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")

# --------------------------------------------------------------
# Settings
# --------------------------------------------------------------

# options
option(MAN_BUILD_LIBRARY "Build dynamic/static library" ON)
option(MAN_BUILD_TESTS "Build the test programs" ON)
option(MAN_ENABLE_FAST_MATH "Enable fast math optimizations" OFF)
option(MAN_USE_DOUBLE_PRECISION "Use double precision" OFF)

# compiler settings

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_DISABLE_SOURCE_CHANGES ON)
set(CMAKE_DISABLE_IN_SOURCE_BUILD ON)

if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    add_compile_options(-Wno-c++98-compat)
    add_compile_options(-Wno-c++98-compat-pedantic)
endif ()

if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
    add_compile_options(-fms-extensions)
endif ()

if (MAN_ENABLE_FAST_MATH)
    if ((CMAKE_CXX_COMPILER_ID MATCHES "Clang") OR (CMAKE_CXX_COMPILER_ID MATCHES "GNU"))
        add_compile_options(-ffast-math)

    elseif (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_compile_options(/fp:fast)
    endif ()
else ()
    if (CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
        add_compile_options(/fp:precise)
    endif ()
endif ()

# --------------------------------------------------------------
# Sources
# --------------------------------------------------------------

######################################
# Project
add_subdirectory(Man)

######################################
# Tests
if (MAN_BUILD_TESTS)
    enable_testing()
    add_subdirectory(Tests)
endif ()