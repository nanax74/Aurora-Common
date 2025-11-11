#pragma once

#include "Net/Protocol/IData.hpp"
#include <memory>

namespace Net::Protocol::Entry
{
    class Ping : public IData
    {
    private:
        uint64_t timestamp;
    public:
        Ping(); // Gen
        Ping(uint64_t timestamp);
        ID getId() override;
        std::vector<std::byte> serialize() override;
        static std::unique_ptr<Ping> deserialize(const std::vector<std::byte>& data);
        void process(std::shared_ptr<Transport::Connection> connection) override;
    };

    class Pong : public IData
    {
    private:
        uint64_t timestamp;
    public:
        Pong(uint64_t timestamp);
        ID getId() override;
        std::vector<std::byte> serialize() override;
        static std::unique_ptr<Pong> deserialize(const std::vector<std::byte>& data);
        void process(std::shared_ptr<Transport::Connection> connection) override;
    };
}