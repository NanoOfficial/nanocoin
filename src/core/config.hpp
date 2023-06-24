/**
 * @file config.hpp
 * @author Krisna Pranav
 * @brief Config
 * @version 1.0
 *
 * @copyright Copyright (c) 2023 Krisna Pranav, NanoBlocksDevelopers
 *
 */

#pragma once

#include <boost/config.hpp>
#include <boost/version.hpp>

#include <algorithm>
#include <array>
#include <chrono>
#include <optional>
#include <string>

using namespace std::chrono_literals;

namespace boost {
    namespace filesystem {
        class Path;
    }
}

#define xstr(a) ver_str (a)
#define ver_str(a) #a

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
inline bool is_asan_build() {
    return true;
}
#else
inline bool is_asan_build() {
    return false;
}
#endif
#elif defined(__SANITIZER_ADDRESS__)
inline bool is_asan_build() {
    return true;
}
#else
inline bool is_asan_build() {
    return false;
}
#endif

namespace nano {
    uint8_t get_major_node_version();
    uint8_t get_minor_node_version();
    uint8_t get_patch_node_version();
    uint8_t get_pre_release_node_version();

    std::optional<std::string> get_env(char const* variable_name);
    std::string get_env_or_default(char const * variable_name, std::string const default_value);

    enum class networks: uint16_t {
        invalid = 0x0,
        nano_dev_network = 0x5241,
        nano_beta_network = 0x5242,
        nano_live_network = 0x5243
    };
}

enum class WorkVersion {
    unspecified,
    work_1
};

enum class BlockType: uint8_t;

class Root;
class Block;
class BlockDetails;
