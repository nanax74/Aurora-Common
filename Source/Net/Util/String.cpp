#include <sstream>
#include <iomanip>
#include "Util/String.hpp"

namespace Util
{
    std::string String::toHexString(const std::vector<std::byte>& data)
    {
        std::ostringstream oss;
        oss << std::hex << std::uppercase << std::setfill('0');
        for (auto b : data)
            oss << std::setw(2) << static_cast<int>(std::to_integer<unsigned char>(b));
        return oss.str();
    }

    std::vector<std::byte> String::fromHexString(const std::string& hex)
    {
        if (hex.size() % 2 != 0)
            throw std::invalid_argument("Hex string length must be even");

        std::vector<std::byte> data;
        data.reserve(hex.size() / 2);

        for (size_t i = 0; i < hex.size(); i += 2)
        {
            unsigned int value;
            std::string byteStr = hex.substr(i, 2);

            if (!std::isxdigit(byteStr[0]) || !std::isxdigit(byteStr[1]))
                throw std::invalid_argument("Invalid hex digit in input string");

            value = std::stoul(byteStr, nullptr, 16);
            data.push_back(static_cast<std::byte>(value));
        }

        return data;
    }
}