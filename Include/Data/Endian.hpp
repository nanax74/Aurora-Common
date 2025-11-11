#pragma once

#include <algorithm>
#include <cstdint>

namespace Data
{
    enum class Endian
    {
        Little,
        Big
    };

    template <typename T>
    static T swapEndian(T val)
    {
        T result = val;
        std::reverse(reinterpret_cast<char*>(&result), reinterpret_cast<char*>(&result) + sizeof(T));
        return result;
    }

    inline Endian getSystemEndian()
    {
        uint16_t test = 0x1;
        return (*reinterpret_cast<uint8_t*>(&test) == 0x1)
            ? Endian::Little
            : Endian::Big;
    }
}