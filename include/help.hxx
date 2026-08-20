#pragma once

inline constexpr auto HELP_MESSAGE {R"(NAME
    cppkg - CMake package manager

SYNOPSIS
    cpppkg [options...] <command> [args...]

DESCRIPTION
    cpppkg is a CMake package manager which generate CMake files to import git
    repositories via 'FetchContent'. Each package must be defined inside
    'cpppkg.json' configuration file.

    After running 'cpppkg i' the files 'cpppkg/Declare.cmake' and 'cpppkg/Link.cmake'
    will be generated to be included in your CMakeLists.

OPTIONS
    -v, --version
        Print the program version message and exit.

    -h, --help
        Print the program help message and exit.

    --force
        Force the command execution.

COMMANDS
    i, install
        Generate the CMake files for the packages defined in the configuration file;
        package/s with already generated files will be skipped unless the '--force'
        option is provided.

    l, list
        Print the list of installed packages.)"};

inline constexpr auto TIP_MESSAGE {"Tip: run 'cpppkg -h' for usage info"};
