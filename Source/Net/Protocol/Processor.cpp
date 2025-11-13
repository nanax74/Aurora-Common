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
        registry->registerFactory(ID::Notification, &Entry::Notification::deserialize);
        registry->registerFactory(ID::ReadMemory, &Entry::ReadMemory::deserialize);
        registry->registerFactory(ID::WriteMemory, &Entry::WriteMemory::deserialize);
        registry->registerFactory(ID::ByteArray, &Entry::ByteArray::deserialize);
        registry->registerFactory(ID::Bool, &Entry::Bool::deserialize);
    }
}