#pragma once

namespace commands {
    /**
     * @brief Install packages defined in the configuration file; if the 'force'
     * flag is set, regenerate CMake files for each package
     *
     * @throws std::runtime_error If the configuration file does not exist
     * @throws std::runtime_error If the configuration file is malformed
     * @throws std::runtime_error If cannot create the install folder
     * @throws std::runtime_error If cannot create the CMake declare file
     */
    auto install(bool force = false) -> void;
}
