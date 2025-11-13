#pragma once

#include <vector>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include <string>
#include <cstdint>
#include "Data/Endian.hpp"

namespace Data
{
    class ByteReader
    {
    private:
        const std::vector<std::byte>& buffer;
        std::size_t pos;

        Endian systemEndian;
        Endian targetEndian;

    public:
        ByteReader(const std::vector<std::byte>& data) 
            : buffer(data), pos(0), systemEndian(getSystemEndian()), targetEndian(Endian::Big) {}

        const std::vector<std::byte>& data() const { return buffer; }
        std::size_t position() const { return pos; }
        std::size_t remain() const { return buffer.size() - pos; }
        bool eof() const { return pos >= buffer.size(); }

        void skip(std::size_t count)
        {
            if (pos + count > buffer.size()) throw std::out_of_range("ByteReader: out of range");
            pos += count;
        }

        template<typename T>
        T read()
        {
            static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
            if (pos + sizeof(T) > buffer.size()) throw std::out_of_range("ByteReader: out of range");

            T value;
            std::memcpy(&value, buffer.data() + pos, sizeof(T));
            pos += sizeof(T);

            if (systemEndian != targetEndian) value = swapEndian(value);

            return value;
        }

        std::vector<std::byte> readBytes(std::size_t count)
        {
            if (pos + count > buffer.size()) throw std::out_of_range("ByteReader: out of range");
            std::vector<std::byte> out(buffer.begin() + pos, buffer.begin() + pos + count);
            pos += count;
            return out;
        }
 
        // Length + Data
        std::vector<std::byte> readVector()
        {
            uint32_t len = read<uint32_t>();
            if (pos + len > buffer.size()) throw std::out_of_range("ByteReader: readVector out of range");
            std::vector<std::byte> out(buffer.begin() + pos, buffer.begin() + pos + len);
            pos += len;
            return out;
        }

        // Length + Data
        std::string readString()
        {
            uint32_t len = read<uint32_t>();
            if (pos + len > buffer.size()) throw std::out_of_range("ByteReader: readString out of range");
            std::string out(reinterpret_cast<const char*>(buffer.data() + pos), len);
            pos += len;
            return out;
        }

        // 16進文字列からT型を読み取る
        template<typename T>
        T readFromString()
        {
            static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");

            std::size_t neededChars = sizeof(T) * 2;
            if (pos + neededChars > buffer.size()) 
                throw std::out_of_range("readFromString: out of buffer range");

            T value{};
            unsigned char* ptr = reinterpret_cast<unsigned char*>(&value);

            for (std::size_t i = 0; i < sizeof(T); ++i)
            {
                char high = reinterpret_cast<const char*>(buffer.data() + pos)[i * 2];
                char low  = reinterpret_cast<const char*>(buffer.data() + pos)[i * 2 + 1];
                std::string byteStr{high, low};
                ptr[i] = static_cast<unsigned char>(std::stoul(byteStr, nullptr, 16));
            }

            pos += neededChars;

            if (systemEndian != targetEndian)
                value = swapEndian(value);

            return value;
        }
    };
}
