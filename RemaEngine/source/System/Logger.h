#ifndef REMA_LOGGER_H
#define REMA_LOGGER_H

#include "../Engine/EnginePlatformSetup.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace RemaEngine
{
    class REMA_API Logger
    {
    private:
        static std::shared_ptr<spdlog::logger> s_CoreLogger;
        static std::shared_ptr<spdlog::logger> s_ClientLogger;

    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
    };
}

// Core logger macroses
#define REMA_CORE_TRACE(...)    ::RemaEngine::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define REMA_CORE_INFO(...)     ::RemaEngine::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define REMA_CORE_WARNING(...)  ::RemaEngine::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define REMA_CORE_ERROR(...)    ::RemaEngine::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define REMA_CORE_FATAL(...)    ::RemaEngine::Logger::GetCoreLogger()->fatal(__VA_ARGS__)


// Client logger macroses
#define REMA_TRACE(...)     ::RemaEngine::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define REMA_INFO(...)      ::RemaEngine::Logger::GetClientLogger()->info(__VA_ARGS__)
#define REMA_WARNING(...)   ::RemaEngine::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define REMA_ERROR(...)     ::RemaEngine::Logger::GetClientLogger()->error(__VA_ARGS__)
#define REMA_FATAL(...)     ::RemaEngine::Logger::GetClientLogger()->fatal(__VA_ARGS__)

#endif // !REMA_LOGGER_H

