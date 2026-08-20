#pragma once

namespace commands {
    /**
     * @brief List packages defined in the configuration file
     *
     * @throws std::runtime_error If the configuration file does not exist
     * @throws std::runtime_error If the configuration file is malformed
     */
    auto list(void) -> void;
}
