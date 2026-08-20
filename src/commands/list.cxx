#include <commands/list.hxx>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <libjson/extra/decode.hxx>

namespace fs = std::filesystem;

namespace commands {
auto list(void) -> void {
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

    // iterate packages
    for (const auto& [k, v] : config.as<libjson::object_t>())
        std::cout << k << ": " << v.at("user").as<std::string>() << "/"
                  << v.at("repository").as<std::string>() << " "
                  << v.at("tag").as<std::string>() << std::endl;
}
} // namespace commands
