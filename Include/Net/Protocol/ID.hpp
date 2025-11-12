#pragma once

namespace Net::Protocol
{
    enum class ID
    {
        Ping = 0,
        Pong = 1,
        Notification = 2,
    
        Invalid = -1
    };
}