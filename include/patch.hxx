#pragma once

/**
 * @brief Regenerate the CMake declare file
 *
 * @throw std::runtime_error If the configuration file is missing
 * @throw std::runtime_error If the configuration file is malformed
 * @throw std::runtime_error If cannot create the install folder
 * @throw std::runtime_error If cannot create the CMake declare file
 */
auto patchDeclare(void) -> void;

/**
 * @brief Regenerate the CMake link file
 *
 * @throw std::runtime_error If the configuration file is missing
 * @throw std::runtime_error If the configuration file is malformed
 * @throw std::runtime_error If cannot create the install folder
 * @throw std::runtime_error If cannot create the CMake link file
 */
auto patchLink(void) -> void;
