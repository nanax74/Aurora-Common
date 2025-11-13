#pragma once

#include <string>
#include <cstdint>

namespace Util
{
    class IP
    {
    public:
        static std::string ipToString(const uint32_t ip);
        static uint32_t stringToIp(const std::string& ipStr);
    };
}