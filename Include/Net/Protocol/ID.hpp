#pragma once

namespace Net::Protocol
{
    enum class ID : int
    {
        Ping = 0,
        Notification = 1,
        ReadMemory = 2,
        WriteMemory = 3,
        WriteMemorySuper = 4,
        InputButton = 5,
        InputLeftStick = 6,
        InputRightStick = 7,
        InputClear = 8,

        Pong = 10,
        ByteArray = 11,
        Bool = 12,
    
        Invalid = -1
    };
}