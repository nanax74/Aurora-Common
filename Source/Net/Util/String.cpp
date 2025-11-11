#include <sstream>
#include <iomanip>
#include "Util/String.hpp"

namespace Net::Util
{
    std::string String::toHexString(const std::vector<std::byte>& data)
    {
        std::ostringstream oss;
        oss << std::hex << std::setfill('0');
        for (auto b : data)
            oss << std::setw(2) << static_cast<int>(std::to_integer<unsigned char>(b));
        return oss.str();
    }
}