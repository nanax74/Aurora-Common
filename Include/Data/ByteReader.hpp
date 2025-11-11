#pragma once

#include <vector>
#include <cstddef>
#include <cstring>
#include <stdexcept>
#include "Data/Endian.hpp"

namespace Data
{
    class ByteReader
    {
    private:
        const std::vector<std::byte>& data;
        std::size_t pos;

        Endian systemEndian;
        Endian targetEndian;

    public:
        ByteReader(const std::vector<std::byte>& data) : data(data), pos(0), systemEndian(getSystemEndian()), targetEndian(Endian::Big) {}

        template<typename T>
        T read()
        {
            if (pos + sizeof(T) > data.size()) throw std::out_of_range("ByteReader: out of range");

            T value;
            std::memcpy(&value, data.data() + pos, sizeof(T));
            pos += sizeof(T);

            if (systemEndian != targetEndian) value = swapEndian(value);

            return value;
        }

        std::vector<std::byte> readBytes(std::size_t count)
        {
            if (pos + count > data.size()) throw std::out_of_range("ByteReader: out of range");

            std::vector<std::byte> out(data.begin() + pos, data.begin() + pos + count);
            pos += count;
            return out;
        }

        std::string readString()
        {
            int length = read<int>();
            if(length > 1024 * 1024) throw std::runtime_error("ByteReader: too long string");
            auto bytes = readBytes(length);
            return std::string(reinterpret_cast<const char*>(bytes.data()), bytes.size());
        }

        void skip(std::size_t count)
        {
            if (pos + count > data.size()) throw std::out_of_range("ByteReader: out of range");
            pos += count;
        }

        std::size_t remain() const
        {
            if (pos > data.size()) return 0;
            return data.size() - pos;
        }

        std::size_t position() const { return pos; }
        bool eof() const { return pos >= data.size(); }
    };
}