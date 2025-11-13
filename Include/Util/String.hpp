#pragma once

#include <string>
#include <vector>

namespace Util
{
    class String
    {
    public:
        static std::string toHexString(const std::vector<std::byte>& data);
        static std::vector<std::byte> fromHexString(const std::string& hex);
    };
}