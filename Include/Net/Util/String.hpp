#pragma once

#include <string>
#include <vector>

namespace Net::Util
{
    class String
    {
    public:
        static std::string toHexString(const std::vector<std::byte>& data);
    };
}