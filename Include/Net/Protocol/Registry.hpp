#pragma once

#include "Net/Protocol/ID.hpp"

#include <map>
#include <functional>
#include <memory>
#include <vector>

namespace Net::Protocol
{
    class IData;

    class Registry
    {
    private:
        std::map<ID, std::function<std::unique_ptr<IData>(std::vector<std::byte> data)>> factories;
    public:
        void registerFactory(ID id, std::function<std::unique_ptr<IData>(std::vector<std::byte> data)> factory);

        std::unique_ptr<IData> deserialize(ID id, std::vector<std::byte> data);
    };
}