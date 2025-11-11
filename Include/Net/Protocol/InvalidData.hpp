#pragma once

#include "Net/Protocol/IData.hpp"

namespace Net::Protocol
{
    class InvalidData : public IData
    {
    public:
        ID getId() override;
        std::vector<std::byte> serialize() override;
        void process(std::shared_ptr<Transport::Connection> connection) override;
    };
}