#pragma once

#include <vector>
#include <string>
#include <cstring>
#include <cstddef>
#include <cstdint>
#include <type_traits>
#include "Data/Endian.hpp"

namespace Data
{
    class ByteWriter
    {
    private:
        std::vector<std::byte> buffer;

        Endian systemEndian;
        Endian targetEndian;

    public:
        ByteWriter() : systemEndian(getSystemEndian()), targetEndian(Endian::Big) {}

        const std::vector<std::byte>& data() const { return buffer; }
        std::vector<std::byte> copy() const { return buffer; }

        void clear() { buffer.clear(); }

        template<typename T>
        void write(T value)
        {
            static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
            if (systemEndian != targetEndian) value = swapEndian(value);
            const std::byte* ptr = reinterpret_cast<const std::byte*>(&value);
            buffer.insert(buffer.end(), ptr, ptr + sizeof(T));
        }

        void writeBytes(const void* data, std::size_t size)
        {
            const std::byte* ptr = reinterpret_cast<const std::byte*>(data);
            buffer.insert(buffer.end(), ptr, ptr + size);
        }

        // Length + Data
        void writeString(const std::string& str)
        {
            uint32_t len = static_cast<uint32_t>(str.size());
            write(len);
            writeBytes(str.data(), len);
        }

        // Length + Data
        void writeVector(const std::vector<std::byte>& data)
        {
            uint32_t len = static_cast<uint32_t>(data.size());
            write(len);
            buffer.insert(buffer.end(), data.begin(), data.end());
        }

        // 16進文字列としてT型を書き込む
        template<typename T>
        void writeToString(T value)
        {
            static_assert(std::is_trivially_copyable_v<T>, "T must be trivially copyable");
        
            // エンディアン変換
            if (systemEndian != targetEndian)
                value = swapEndian(value);
        
            const unsigned char* ptr = reinterpret_cast<const unsigned char*>(&value);
        
            for (std::size_t i = 0; i < sizeof(T); ++i)
            {
                char buf[3];
                std::snprintf(buf, sizeof(buf), "%02X", ptr[i]);
                // 2文字ずつ std::byte に変換して追加
                buffer.push_back(static_cast<std::byte>(buf[0]));
                buffer.push_back(static_cast<std::byte>(buf[1]));
            }
        }
    };
}