#pragma once

#include "Net/Protocol/ID.hpp"
#include "Net/Protocol/Registry.hpp"
#include <memory>
#include <vector>

namespace Net
{
    namespace Transport
    {
        class Connection;
    }

    namespace Protocol
    {
        class IData
        {
        public:
            virtual ~IData() = default;
            virtual ID getId() = 0;
            virtual std::vector<std::byte> serialize() = 0;
            virtual void process(std::shared_ptr<Transport::Connection> connection) = 0;
        };
    }
}