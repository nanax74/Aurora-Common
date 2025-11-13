#include "Debug/Logger.hpp"
#include "Net/Protocol/Entry.hpp"
#include "Net/Transport/Connection.hpp"
#include "Data/ByteWriter.hpp"
#include "Data/ByteReader.hpp"
#include <memory>

namespace Net::Protocol::Entry
{
    Bool::Bool(bool flag) : flag(flag) {}

    ID Bool::getId()
    {
        return ID::Bool;
    }

    std::vector<std::byte> Bool::serialize()
    {
        Data::ByteWriter writer;
        writer.write<uint8_t>(static_cast<uint8_t>(flag));
        return writer.copy();
    }

    std::unique_ptr<Bool> Bool::deserialize(const std::vector<std::byte>& data)
    {
        Data::ByteReader reader(data);
        bool flag = static_cast<bool>(reader.read<uint8_t>());
        return std::unique_ptr<Bool>(new Bool(flag));
    }

    void Bool::process(std::shared_ptr<Transport::Connection> connection)
    {
        if(flag)
        {
            Debug::Logger::printf("True");
        }
        else
        {
            Debug::Logger::printf("False");
        }
    }
}