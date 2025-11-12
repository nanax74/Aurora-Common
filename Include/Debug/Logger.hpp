#pragma once

#include <string>
#include <format>

namespace Debug
{
    class Logger
    {
    public:
        static bool init();
        static bool shutdown();

        template<typename... Args>
        static bool printf(std::format_string<Args...> fmt, Args&&... args)
        {
            if (!isEnabled) return false;
            try
            {
                std::string formatted = std::format(fmt, std::forward<Args>(args)...);
                return write(std::format("[Aurora] {}", formatted));
            }
            catch (const std::format_error& e)
            {
                write(std::format("[Aurora][format error] {}", e.what()));
                return false;
            }
        }

    private:
        static bool write(const std::string& msg);
        static inline bool isEnabled = false;
    };
}
