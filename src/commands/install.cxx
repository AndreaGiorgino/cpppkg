#include <commands/install.hxx>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <libjson/extra/decode.hxx>

namespace fs = std::filesystem;

namespace commands {
auto install(bool force) -> void {
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
    auto installFolderpath {fs::current_path() / ".cpppkg"};

    if (!fs::exists(installFolderpath) || !fs::is_directory(installFolderpath))
        if (!fs::create_directory(installFolderpath))
            throw std::runtime_error(
                "Cannot create the install folder: '.cpppkg'");

    installFolderpath /= "packages";

    if (!fs::exists(installFolderpath) || !fs::is_directory(installFolderpath))
        if (!fs::create_directory(installFolderpath))
            throw std::runtime_error(
                "Cannot create the install folder: '.cpppkg/packages'");

    // iterate packages
    for (const auto& [k, v] : config.as<libjson::object_t>()) {
        const auto filepath {installFolderpath / (k + ".cmake")};

        // skip installed packages if 'force' flag is not set
        if (fs::exists(filepath) && fs::is_regular_file(filepath) && !force) {
            std::clog << "-- Package '" << k << "' skipped" << std::endl;
            continue;
        }

        std::ofstream ofs {filepath};

        // check stream
        if (!ofs.is_open())
            throw std::runtime_error("Cannot create the CMake declare file: '"
                                     + filepath.string() + "'");

        // write the CMake declare instructions
        ofs << "cmake_minimum_required(VERSION 3.11)\n\n"
            << "include(FetchContent)\n\n"
            << "FetchContent_Declare(\n"
            << k << "\n"
            << "    GIT_REPOSITORY \"git@github.com:"
            << v.at("user").as<std::string>() << "/"
            << v.at("repository").as<std::string>() << "\"\n"
            << "    GIT_TAG " << v.at("tag") << "\n"
            << "    GIT_SHALLOW TRUE\n)\n\n"
            << "FetchContent_MakeAvailable(" << k << ")" << std::endl;

        std::clog << "-- Package '" << k << "' installed" << std::endl;
    }
}
} // namespace commands
