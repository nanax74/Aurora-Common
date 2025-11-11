#include "Net/Protocol/InvalidData.hpp"

namespace Net::Protocol
{
    ID InvalidData::getId()
    {
        return ID::Invalid;
    }

    std::vector<std::byte> InvalidData::serialize()
    {
        return {};
    }

    void InvalidData::process(std::unique_ptr<Transport::Connection> connection) {}
}