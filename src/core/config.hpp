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
        class path;
    }
}

#define xstr(a) ver_str (a)
#define ver_str(a) #a

char const * const NANO_VERSION_STRING = xstr (TAG_VERSION_STRING);
char const * const NANO_MAJOR_VERSION_STRING = xstr (MAJOR_VERSION_STRING);
char const * const NANO_MINOR_VERSION_STRING = xstr (MINOR_VERSION_STRING);
char const * const NANO_PATCH_VERSION_STRING = xstr (PATCH_VERSION_STRING);
char const * const NANO_PRE_RELEASE_VERSION_STRING = xstr (PRE_RELEASE_VERSION_STRING);
char const * const BUILD_INFO = xstr (GIT_COMMIT_HASH BOOST_COMPILER) " \"BOOST " xstr (BOOST_VERSION) "\" BUILT " xstr (__DATE__);

#if defined(__has_feature)
#if __has_feature(address_sanitizer)
inline bool is_asan_build () {
	return true;
}
#else
inline bool is_asan_build () {
	return false;
}
#endif
#elif defined(__SANITIZE_ADDRESS__)
inline bool is_asan_build () {
	return true;
}
#else
inline bool is_asan_build () {
	return false;
}
#endif

#if defined(__has_feature)
#if __has_feature(thread_sanitizer)
inline bool is_tsan_build () {
	return true;
}
#else
inline bool is_tsan_build () {
	return false;
}
#endif
#elif defined(__SANITIZE_THREAD__)
inline bool is_tsan_build () {
	return true;
}
#else
inline bool is_tsan_build () {
	return false;
}
#endif

namespace Nano {
    uint8_t get_major_node_version();
    uint8_t get_minor_node_version();
    uint8_t get_patch_node_version();
    uint8_t get_pre_release_node_version();

    std::optional<std::string> get_env(char const * variable_name);
    std::string get_env_or_default(char const * variable_name, std::string const default_value);
    int get_env_int_or_default(char const * variable_name, int const default_value);
    uint64_t get_env_threshold_or_default (char const * variable_name, uint64_t const default_value);

    uint16_t test_node_port();
    uint16_t test_rpc_port();
    uint16_t test_ipc_port();
    uint16_t test_websocket_port();
    std::array<uint8_t, 2> test_magic_number ();
    uint32_t test_scan_wallet_reps_delay ();

    enum class Networks : uint16_t {
        Invalid = 0x0,
        NanoDevNetwork = 0x5241, 
        NanoBetaNetwork = 0x5242,
        NanoLiveNetwork = 0x5243,
        NanoTestNetwork = 0x5258,
    };

    enum class WorkVersion {
        unspecified,
        work_1
    };

    enum class BlockType : uint8_t;

    class Root;
    class Block;
    class BlockDetails;

    class WorkThresholds {
    public:
        uint64_t const epoch_1;
        uint64_t const epoch_2;
        uint64_t const epoch_2_receive;
        uint64_t const base;
        uint64_t const entry;

        /**
         * @brief WorkThresholds
         * 
         */
        constexpr WorkThresholds (uint64_t epoch_1_a, uint64_t epoch_2_a, uint64_t epoch_2_receive_a) :
            epoch_1 (epoch_1_a), epoch_2 (epoch_2_a), epoch_2_receive (epoch_2_receive_a),
            base (std::max ({ epoch_1, epoch_2, epoch_2_receive })),
            entry (std::min ({ epoch_1, epoch_2, epoch_2_receive }))
        {
        }

        WorkThresholds () = delete;
        WorkThresholds operator= (Nano::WorkThresholds const & other_a) {
            return other_a;
        }

        uint64_t threshold_entry(Nano::WorkVersion const, Nano::BlockType const) const;
        uint64_t threshold(Nano::BlockDetails const &) const;
        uint64_t threshold(Nano::WorkVersion const, Nano::BlockDetails const) const;
        uint64_t threshold_base(Nano::WorkVersion const) const;
        uint64_t value(Nano::Root const & root_a, uint64_t work_a) const;
        double normalized_multiplier(double const, uint64_t const) const;
        double denormalized_multiplier(double const, uint64_t const) const;
        uint64_t difficulty(Nano::WorkVersion const, Nano::Root const &, uint64_t const) const;
        uint64_t difficulty(Nano::Block const & block_a) const;
        bool validate_entry(Nano::WorkVersion const, Nano::Root const &, uint64_t const) const;
        bool validate_entry(Nano::Block const &) const;

        static Nano::WorkThresholds const PublishFull;
        static Nano::WorkThresholds const PublishBeta;
        static Nano::WorkThresholds const PublishDev;
        static Nano::WorkThresholds const PublishTest;
    };

    class NetworkConstants {
        static constexpr std::chrono::seconds default_cleanup_period = std::chrono::seconds (60);
        static constexpr size_t default_max_peers_per_ip = 10;

    public:
        NetworkConstants (Nano::WorkThresholds & work_, Nano::Networks network_a) :
            current_network(network_a),
            work(work_),
            principal_weight_factor(1000),
            default_node_port(44000),
            default_rpc_port(45000),
            default_ipc_port(46000),
            default_websocket_port(47000),
            aec_loop_interval_ms(300),
            cleanup_period(default_cleanup_period),
            keepalive_period(std::chrono::seconds (15)),
            idle_timeout(default_cleanup_period * 2),
            silent_connection_tolerance_time(std::chrono::seconds (120)),
            syn_cookie_cutoff(std::chrono::seconds (5)),
            bootstrap_interval(std::chrono::seconds (15 * 60)),
            max_peers_per_ip(default_max_peers_per_ip),
            max_peers_per_subnetwork(default_max_peers_per_ip * 4),
            ipv6_subnetwork_prefix_for_limiting(64), 
            peer_dump_interval(std::chrono::seconds (5 * 60)),
            vote_broadcast_interval(15 * 1000) {
            if (is_live_network()) {
                default_node_port = 7075;
                default_rpc_port = 7076;
                default_ipc_port = 7077;
                default_websocket_port = 7078;
            }
            else if (is_beta_network()) {
                default_node_port = 54000;
                default_rpc_port = 55000;
                default_ipc_port = 56000;
                default_websocket_port = 57000;
            }
            else if (is_test_network()) {
                default_node_port = test_node_port();
                default_rpc_port = test_rpc_port();
                default_ipc_port = test_ipc_port();
                default_websocket_port = test_websocket_port();
            }
            else if (is_dev_network()) {
                aec_loop_interval_ms = 20;
                cleanup_period = std::chrono::seconds(1);
                keepalive_period = std::chrono::seconds(1);
                idle_timeout = cleanup_period * 15;
                max_peers_per_ip = 20;
                max_peers_per_subnetwork = max_peers_per_ip * 4;
                peer_dump_interval = std::chrono::seconds(1);
                vote_broadcast_interval = 500;
                telemetry_request_cooldown = 500ms;
                telemetry_cache_cutoff = 2000ms;
                telemetry_request_interval = 500ms;
                telemetry_broadcast_interval = 500ms;
                optimistic_activation_delay = 2s;
            }
        }

        static char const * active_network_err_msg;

        Nano::Network current_network { Nano::NetworkConstants::active_network };
        Nano::WorkThresholds & work;

        unsigned principal_weight_factor;
        uint16_t default_node_port;
        uint16_t default_rpc_port;
        uint16_t default_ipc_port;
        uint16_t default_websocket_port;
        unsigned aec_loop_interval_ms;

        std::chrono::seconds cleanup_period;

        std::chrono::milliseconds cleanup_period_half() const {
            return std::chrono::duration_cast<std::chrono::milliseconds> (cleanup_period) / 2;
        }

        std::chrono::seconds cleanup_cutoff() const {
            return cleanup_period * 5;
        }

        std::chrono::seconds keepalive_period;
        std::chrono::seconds idle_timeout;
        std::chrono::seconds silent_connection_tolerance_time;
        std::chrono::seconds syn_cookie_cutoff;
        std::chrono::seconds bootstrap_interval;
        size_t max_peers_per_ip;
        size_t max_peers_per_subnetwork;
        size_t ipv6_subnetwork_prefix_for_limiting;
        std::chrono::seconds peer_dump_interval;
        uint64_t vote_broadcast_interval;

        std::chrono::milliseconds telemetry_request_cooldown{ 1000 * 15 };
        std::chrono::milliseconds telemetry_request_interval{ 1000 * 60 };
        std::chrono::milliseconds telemetry_broadcast_interval{ 1000 * 60 };
        std::chrono::milliseconds telemetry_cache_cutoff{ 1000 * 130 }; 

        std::chrono::seconds optimistic_activation_delay{ 30 };

        Nano::Networks network() const {
            return current_network;
        }

        /**
         * @brief Set the active network object
         * 
         * @param network_a 
         */
        static void set_active_network (Nano::Networks network_a) {
            active_network = network_a;
        }

        /**
         * @brief Set the active network object
         * 
         * @param network_a 
         * @return true 
         * @return false 
         */
        static bool set_active_network(std::string network_a) {
            auto error{ false };
            if (network_a == "live") {
                active_network = Nano::Networks::NanoLiveNetwork;
            }
            else if (network_a == "beta") {
                active_network = Nano::Networks::NanoBetaNetwork;
            }
            else if (network_a == "dev") {
                active_network = Nano::Networks::NanoDevNetwork;
            }
            else if (network_a == "test") {
                active_network = Nano::Networks::NanoTestNetwork;
            }
            else {
                error = true;
            }
            return error;
        }

        char const * get_current_network_as_string() {
            return is_live_network() ? "live" : is_beta_network() ? "beta"
            : is_test_network()                                    ? "test"
                                                                    : "dev";
        }

        bool is_live_network() const {
            return current_network == Nano::Networks::NanoLiveNetwork;
        }
        bool is_beta_network() const {
            return current_network == Nano::Networks::NanoBetaNetwork;
        }
        bool is_dev_network() const {
            return current_network == Nano::Networks::NanoDevNetwork;
        }
        bool is_test_network() const {
            return current_network == Nano::Networks::NanoTestNetwork;
        }

        static Nano::Networks active_network;
        uint8_t const protocol_version = 0x13;
        uint8_t const protocol_version_min = 0x12;
        uint8_t const bootstrap_protocol_version_min = 0x13;
    };

    std::string get_node_toml_config_path(boost::filesystem::path const & data_path);
    std::string get_rpc_toml_config_path(boost::filesystem::path const & data_path);
    std::string get_access_toml_config_path(boost::filesystem::path const & data_path);
    std::string get_qtwallet_toml_config_path(boost::filesystem::path const & data_path);
    std::string get_tls_toml_config_path(boost::filesystem::path const & data_path);

    bool running_within_valgrind ();
    bool memory_intensive_instrumentation ();

    bool slow_instrumentation ();

    bool is_sanitizer_build ();

    void force_nano_dev_network();
}
