#include <filesystem>
#include <fstream>
#include <iostream>
#include <libjson/extra/decode.hxx>
#include <patch.hxx>

namespace fs = std::filesystem;

auto patchDeclare(void) -> void {
    const auto configFilepath {fs::current_path() / "cpppkg.json"};

    // check config file
    if (!fs::exists(configFilepath) || !fs::is_regular_file(configFilepath))
        throw std::runtime_error("Missing configuration file: 'cpppkg.json'");

    // decode config file
    std::ifstream ifs {configFilepath};
    const auto config {libjson::decode(ifs)};

    if (!config.holds_alternative<libjson::object_t>())
        throw std::runtime_error(
            "Top level value of the configuration file must be an object");

    // check install folder
    const auto installFolderpath {fs::current_path() / ".cpppkg"};

    if (!fs::exists(installFolderpath) || !fs::is_directory(installFolderpath))
        if (!fs::create_directory(installFolderpath))
            throw std::runtime_error(
                "Cannot create the install folder: '.cpppkg'");

    const auto declareFilepath {installFolderpath / "Declare.cmake"};
    std::ofstream ofs {declareFilepath};

    // check stream
    if (!ofs.is_open())
        throw std::runtime_error("Cannot create the CMake declare file: '"
                                 + declareFilepath.string() + "'");

    // iterate packages
    for (const auto& [k, _] : config.as<libjson::object_t>())
        // write the CMake include instruction
        ofs << "include(${CMAKE_CURRENT_SOURCE_DIR}/.cpppkg/packages/" << k
            << ".cmake)" << std::endl;

    std::clog << "-- CMake declare file created" << std::endl;
}

auto patchLink(void) -> void {
    const auto configFilepath {fs::current_path() / "cpppkg.json"};

    // check config file
    if (!fs::exists(configFilepath) || !fs::is_regular_file(configFilepath))
        throw std::runtime_error("Missing configuration file: 'cpppkg.json'");

    // decode config file
    std::ifstream ifs {configFilepath};
    const auto config {libjson::decode(ifs)};

    if (!config.holds_alternative<libjson::object_t>())
        throw std::runtime_error(
            "Top level value of the configuration file must be an object");

    // check install folder
    const auto installFolderpath {fs::current_path() / ".cpppkg"};

    if (!fs::exists(installFolderpath) || !fs::is_directory(installFolderpath))
        if (!fs::create_directory(installFolderpath))
            throw std::runtime_error(
                "Cannot create the install folder: '.cpppkg'");

    const auto declareFilepath {installFolderpath / "Link.cmake"};
    std::ofstream ofs {declareFilepath};

    // check stream
    if (!ofs.is_open())
        throw std::runtime_error("Cannot create the CMake link file: '"
                                 + declareFilepath.string() + "'");

    // iterate packages
    for (const auto& [k, _] : config.as<libjson::object_t>())
        // write the CMake link instruction
        ofs << "target_link_libraries(${PROJECT_NAME} PRIVATE " << k << ")"
            << std::endl;

    std::clog << "-- CMake link file created" << std::endl;
}
