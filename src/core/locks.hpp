/**
 * @file locks.hpp
 * @author Krisna Pranav
 * @brief Locks
 * @version 1.0
 * @date 2023-06-24
 * 
 * @copyright Copyright (c) 2023 Krisna Pranav, NanoBlocksDevelopers
 * 
 */

#pragma once

namespace Nano {
    class Mutex;

    extern Nano::Mutex* mutexToFilter;
    extern Nano::Mutex* mutexToFilterMutex;
    bool shouldBeFiltered(char const* name);
    bool any_filters_registerd();

    enum class Mutexes {
        ACTIVE,
        BLOCKARRIVAL,
    };

    char const* mutex_identifier(Mutexes mutex);

    class Mutex {
    public:
        Mutex() = default;
        Mutex(const char* name_a);
        #if USING_NANO_TIMED_LOCKS
            :
            name(name_a)
        #endif

    };

    #if USING_NANO_TIMED_LOCKS
    template <typename Mutex>
    void output(char const* str, std::chrono::millseconds time, Mutex& mutex);

    #endif 
}