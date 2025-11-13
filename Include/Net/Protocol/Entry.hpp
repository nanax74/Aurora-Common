#pragma once

#include "Net/Protocol/IData.hpp"
#include <cstdint>
#include <memory>
#include <string>
#include <optional>
#include <vector>

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

    class Notification : public IData
    {
    private:
        std::string msg;
    public:
        Notification(std::string msg);
        ID getId() override;
        std::vector<std::byte> serialize() override;
        static std::unique_ptr<Notification> deserialize(const std::vector<std::byte>& data);
        void process(std::shared_ptr<Transport::Connection> connection) override;
    };

    class ByteArray : public IData
    {
    private:
        std::optional<std::vector<std::byte>> data;
    public:
        ByteArray(std::optional<std::vector<std::byte>> data);
        ID getId() override;
        std::vector<std::byte> serialize() override;
        static std::unique_ptr<ByteArray> deserialize(const std::vector<std::byte>& data);
        void process(std::shared_ptr<Transport::Connection> connection) override;
    };

    class ReadMemory : public IData
    {
    private:
        uint32_t address;
        uint32_t size;
    public:
        ReadMemory(uint32_t address, uint32_t size);
        ID getId() override;
        std::vector<std::byte> serialize() override;
        static std::unique_ptr<ReadMemory> deserialize(const std::vector<std::byte>& data);
        void process(std::shared_ptr<Transport::Connection> connection) override;
    };

    class WriteMemory : public IData
    {
    private:
        uint32_t address;
        std::vector<std::byte> data;
    public:
        WriteMemory(uint32_t address, std::vector<std::byte> data);
        ID getId() override;
        std::vector<std::byte> serialize() override;
        static std::unique_ptr<WriteMemory> deserialize(const std::vector<std::byte>& data);
        void process(std::shared_ptr<Transport::Connection> connection) override;
    };

    class Bool : public IData
    {
    private:
        bool flag;
    public:
        Bool(bool flag);
        ID getId() override;
        std::vector<std::byte> serialize() override;
        static std::unique_ptr<Bool> deserialize(const std::vector<std::byte>& data);
        void process(std::shared_ptr<Transport::Connection> connection) override;
    };
    
    class WriteMemorySuper : public IData
    {
    private:
        uint32_t address;
        std::vector<std::byte> data;
    public:
        WriteMemorySuper(uint32_t address, std::vector<std::byte> data);
        ID getId() override;
        std::vector<std::byte> serialize() override;
        static std::unique_ptr<WriteMemorySuper> deserialize(const std::vector<std::byte>& data);
        void process(std::shared_ptr<Transport::Connection> connection) override;
    };
}