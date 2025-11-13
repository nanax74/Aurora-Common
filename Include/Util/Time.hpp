#pragma once

#include <chrono>

namespace Util
{
    class Time
    {
    public:
        static uint64_t getNow()
        {
            using namespace std::chrono;
            uint64_t now = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();
            return now;
        }
    };
}