#include "System/Logger.h"

#include "spdlog/sinks/stdout_color_sinks.h"

namespace RemaEngine
{
    std::shared_ptr<spdlog::logger> Logger::m_pCoreLogger;
    std::shared_ptr<spdlog::logger> Logger::m_pClientLogger;

    void Logger::Init()
    {
        spdlog::set_pattern("%^[%T] [%n %l]: %v%$");

        m_pCoreLogger = spdlog::stdout_color_mt("ENGINE");
        m_pCoreLogger->set_level(spdlog::level::trace);

        m_pClientLogger = spdlog::stdout_color_mt("APP");
        m_pClientLogger->set_level(spdlog::level::trace);
    }
}