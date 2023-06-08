/**
 * @file RemaEngine/System/Logger.h
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
#ifndef REMA_LOGGER_H
#define REMA_LOGGER_H

#include <RemaEngine/Engine/Core.h>
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace RemaEngine
{
    /**
    * @class RemaEngine::Logger
    * @brief A static class which implements engine logger.
    **/
    class REMA_API Logger
    {
    private:
        /**
        * @var m_pCoreLogger
        * @brief The engine-side logger object.
        **/
        static std::shared_ptr<spdlog::logger> m_pCoreLogger;
        /**
        * @var m_pClientLogger
        * @brief The app-side logger object.
        **/
        static std::shared_ptr<spdlog::logger> m_pClientLogger;

    public:
        /**
        * @brief Iinitializes logger parameters.
        * @details Iinitializes logger parameters such as color,
        * level prefix and output pattern.
        **/
        static void Init();

        /**
        * @brief Returns logger for engine-side.
        * @returns A reference to the spdlog logger object for the engine-side.
        **/
        inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return m_pCoreLogger; }
        /**
        * @brief Returns logger for application-side.
        * @returns A reference to the spdlog logger object for the application-side.
        **/
        inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return m_pClientLogger; }
    };
}

/////////////////////////
// Core logger macroses
////////////////////////

/**
* @brief The engine-side logger message with **trace** logging level.
* @details Macros that allows engine-side logger log with the
* **trace** logging level. Messages with this level will be marked
* with *white* color.
* @param[in] __VA_ARGS__ - string arguments for engine-side logger.
**/
#define REMA_ENGINE_TRACE(...)    ::RemaEngine::Logger::GetCoreLogger()->trace(__VA_ARGS__)
/**
* @brief The engine-side logger message with **info** logging level.
* @details Macros that allows engine-side logger log with the
* **info** logging level. Messages with this level will be marked
* with *green* color.
* @param[in] __VA_ARGS__ - string arguments for engine-side logger.
**/
#define REMA_ENGINE_INFO(...)     ::RemaEngine::Logger::GetCoreLogger()->info(__VA_ARGS__)
/**
* @brief The engine-side logger message with **warning** logging level.
* @details Macros that allows engine-side logger log with the
* **warning** logging level. Messages with this level will be marked
* with *yellow* color.
* @param[in] __VA_ARGS__ - string arguments for engine-side logger.
**/
#define REMA_ENGINE_WARNING(...)  ::RemaEngine::Logger::GetCoreLogger()->warn(__VA_ARGS__)
/**
* @brief The engine-side logger message with **error** logging level.
* @details Macros that allows engine-side logger log with the
* **error** logging level. Messages with this level will be marked
* with *red* color.
* @param[in] __VA_ARGS__ - string arguments for engine-side logger.
**/
#define REMA_ENGINE_ERROR(...)    ::RemaEngine::Logger::GetCoreLogger()->error(__VA_ARGS__)
/**
* @brief The engine-side logger message with **critical** logging level.
* @details Macros that allows engine-side logger log with the
* **critical** logging level. Messages with this level will be marked
* with *dark red* color.
* @param[in] __VA_ARGS__ - string arguments for engine-side logger.
**/
#define REMA_ENGINE_CRITICAL(...)    ::RemaEngine::Logger::GetCoreLogger()->critical(__VA_ARGS__)

///////////////////////////
// Client logger macroses
//////////////////////////

/**
* @brief The app-side logger message with **trace** logging level.
* @details Macros that allows app-side logger log with the
* **trace** logging level. Messages with this level will be marked
* with *white* color.
* @param[in] __VA_ARGS__ - string arguments for app-side logger.
**/
#define REMA_APP_TRACE(...)     ::RemaEngine::Logger::GetClientLogger()->trace(__VA_ARGS__)
/**
* @brief The app-side logger message with **info** logging level.
* @details Macros that allows app-side logger log with the
* **info** logging level. Messages with this level will be marked
* with *green* color.
* @param[in] __VA_ARGS__ - string arguments for app-side logger.
**/
#define REMA_APP_INFO(...)      ::RemaEngine::Logger::GetClientLogger()->info(__VA_ARGS__)
/**
* @brief The app-side logger message with **warning** logging level.
* @details Macros that allows app-side logger log with the
* **warning** logging level. Messages with this level will be marked
* with *yellow* color.
* @param[in] __VA_ARGS__ - string arguments for app-side logger.
**/
#define REMA_APP_WARNING(...)   ::RemaEngine::Logger::GetClientLogger()->warn(__VA_ARGS__)
/**
* @brief The app-side logger message with **warning** logging level.
* @details Macros that allows app-side logger log with the
* **warning** logging level. Messages with this level will be marked
* with *red* color.
* @param[in] __VA_ARGS__ - string arguments for app-side logger.
**/
#define REMA_APP_ERROR(...)     ::RemaEngine::Logger::GetClientLogger()->error(__VA_ARGS__)
/**
* @brief The app-side logger message with **critical** logging level.
* @details Macros that allows app-side logger log with the
* **critical** logging level. Messages with this level will be marked
* with *dark red* color.
* @param[in] __VA_ARGS__ - string arguments for engine-side logger.
**/
#define REMA_APP_CRITICAL(...)     ::RemaEngine::Logger::GetClientLogger()->critical(__VA_ARGS__)

#endif // !REMA_LOGGER_H
