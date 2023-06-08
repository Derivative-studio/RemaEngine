/**
 * @file RemaEngine/System/Logger.cpp
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @copyright Copyright (c) 2023
 *
 * This file is part of RemaEngine.
 *
 * RemaEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RemaEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 **/
#include <remapch.h>
#include <RemaEngine/System/Logger.h>
#include <spdlog/sinks/stdout_color_sinks.h>

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