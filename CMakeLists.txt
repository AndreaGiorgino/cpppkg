cmake_minimum_required(VERSION 3.24)

project(
    cpppkg
    VERSION 1.0.0
    LANGUAGES CXX
)

set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

#
# Dependencies
#

include(${CMAKE_CURRENT_SOURCE_DIR}/CMake/Options.cmake)

#
# CMake generated files
#

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/include/version.hxx.in
    ${CMAKE_CURRENT_BINARY_DIR}/generated/version.hxx
    @ONLY)

#
# Target
#

file(
    GLOB_RECURSE SOURCE_FILES
    CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cxx
)

add_executable(
    ${PROJECT_NAME}
    ${SOURCE_FILES}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 23
        CXX_STANDARD_REQUIRED ON
        CXX_EXTENSIONS OFF
)

target_compile_options(
    ${PROJECT_NAME}
    PRIVATE -Wall -Wextra -pedantic
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/generated>
        $<INSTALL_INTERFACE:include>
)
