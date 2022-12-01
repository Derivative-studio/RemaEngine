#ifndef REMA_LOGGER_H
#define REMA_LOGGER_H

#include "RemaEngine/Engine/EnginePlatformSetup.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace RemaEngine
{
    class REMA_API Logger
    {
    private:
        static std::shared_ptr<spdlog::logger> m_pCoreLogger;
        static std::shared_ptr<spdlog::logger> m_pClientLogger;

    public:
        static void Init();

        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_pCoreLogger; }
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_pClientLogger; }
    };
}

// Core logger macroses
#define REMA_LOG_CORE_TRACE(...)    ::RemaEngine::Logger::GetCoreLogger()->trace(__VA_ARGS__)
#define REMA_LOG_CORE_INFO(...)     ::RemaEngine::Logger::GetCoreLogger()->info(__VA_ARGS__)
#define REMA_LOG_CORE_WARNING(...)  ::RemaEngine::Logger::GetCoreLogger()->warn(__VA_ARGS__)
#define REMA_LOG_CORE_ERROR(...)    ::RemaEngine::Logger::GetCoreLogger()->error(__VA_ARGS__)
#define REMA_LOG_CORE_FATAL(...)    ::RemaEngine::Logger::GetCoreLogger()->fatal(__VA_ARGS__)


// Client logger macroses
#define REMA_LOG_APP_TRACE(...)     ::RemaEngine::Logger::GetClientLogger()->trace(__VA_ARGS__)
#define REMA_LOG_APP_INFO(...)      ::RemaEngine::Logger::GetClientLogger()->info(__VA_ARGS__)
#define REMA_LOG_APP_WARNING(...)   ::RemaEngine::Logger::GetClientLogger()->warn(__VA_ARGS__)
#define REMA_LOG_APP_ERROR(...)     ::RemaEngine::Logger::GetClientLogger()->error(__VA_ARGS__)
#define REMA_LOG_APP_FATAL(...)     ::RemaEngine::Logger::GetClientLogger()->fatal(__VA_ARGS__)

#endif // !REMA_LOGGER_H

