#include "Debug/Logger.hpp"
#include "Net/Protocol/Entry.hpp"
#include "Net/Transport/Connection.hpp"
#include "Data/ByteWriter.hpp"
#include "Data/ByteReader.hpp"
#include "Util/String.hpp"
#include <memory>

namespace Net::Protocol::Entry
{
    ByteArray::ByteArray(std::optional<std::vector<std::byte>> data) : data(data) {}

    ID ByteArray::getId()
    {
        return ID::ByteArray;
    }

    std::vector<std::byte> ByteArray::serialize()
    {
        Data::ByteWriter writer;
        if(data)
        {
            writer.writeVector(data.value());
        }
        return writer.copy();
    }

    std::unique_ptr<ByteArray> ByteArray::deserialize(const std::vector<std::byte>& data)
    {
        Data::ByteReader reader(data);
        auto d = reader.readVector();
        return std::unique_ptr<ByteArray>(new ByteArray(d));
    }

    void ByteArray::process(std::shared_ptr<Transport::Connection> connection)
    {
        if(!data)
        {
            Debug::Logger::printf("Data is invalid");
            return;
        }
        std::string str = Util::String::toHexString(data.value());
        Debug::Logger::printf("Data: {}", str);
    }
}