/**
 * @file RemaEngine/Engine/EnginePlatformSetup.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-04-02
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
#ifndef REMA_ENGINE_PLATFORM_SETUP_H
#define REMA_ENGINE_PLATFORM_SETUP_H

#include <EASTL/shared_ptr.h>
#include <EASTL/unique_ptr.h>

#ifdef REMA_WIN
#if REMA_DYNAMIC_LINKAGE
    #ifdef REMA_BUILD_DLL
        #define REMA_API __declspec(dllexport)
    #else
        #define REMA_API __declspec(dllimport)
    #endif // REMA_BUILD_DLL
#else
    #define REMA_API
#endif
#else
    #error Engine only supports windows now!
#endif // REMA_WIN

#ifdef REMA_ENABLE_ASSERT
    #define REMA_ASSERT(x, ...) { if(!(x)) { REMA_ERROR("Assertion filed: {0}", __VA_ARGS__); __debugbreak(); }}
    #define REMA_CORE_ASSERT(x, ...) { if(!(x)) { REMA_CORE_ERROR("Assertion failed: {0}", __VA_ARGS__); __debugbreak(); }}
#else
    #define REMA_ASSERT(x, ...)
    #define REMA_CORE_ASSERT(x, ...)
#endif // REMA_ENABLE_ASSERT

#define REMA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#define BIT(x) (1 << x)
#define RUINT unsigned int

namespace RemaEngine
{
    template<typename _Ty>
    using scope = eastl::unique_ptr<_Ty>;
    template<typename _Ty, typename ..._Args>
    constexpr scope<_Ty> CreateScope(_Args&& ... args) {
        return eastl::make_unique<_Ty>(std::forward<_Args>(args)...);
    }

    template<typename _Ty>
    using ref = eastl::shared_ptr<_Ty>;
    template<typename _Ty, typename ..._Args>
    constexpr ref<_Ty> CreateRef(_Args&& ... args) {
        return eastl::make_shared<_Ty>(std::forward<_Args>(args)...);
    }
}

#endif // !REMA_ENGINE_PLATFORM_SETUP_H
