#include "Net/Protocol/Processor.hpp"
#include "Net/Protocol/Entry.hpp"
#include "Net/Protocol/Registry.hpp"
#include <memory>

namespace Net::Protocol
{
    void Processor::registerData(std::shared_ptr<Registry> registry)
    {
        registry->registerFactory(ID::Ping, &Entry::Ping::deserialize);
        registry->registerFactory(ID::Pong, &Entry::Pong::deserialize);
    }
}