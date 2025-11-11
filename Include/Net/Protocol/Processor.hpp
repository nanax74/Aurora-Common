#pragma once

#include "Net/Protocol/Registry.hpp"

#include <memory>

namespace Net::Protocol
{
    class Processor
    {
    public:
        static void registerData(std::shared_ptr<Registry> registry);
    };
}