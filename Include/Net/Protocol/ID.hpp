#pragma once

namespace Net::Protocol
{
    enum class ID
    {
        Ping = 0,
        Notification = 1,
        ReadMemory = 2,
        WriteMemory = 3,
        WriteMemorySuper = 4,

        Pong = 10,
        ByteArray = 11,
        Bool = 12,
    
        Invalid = -1
    };
}