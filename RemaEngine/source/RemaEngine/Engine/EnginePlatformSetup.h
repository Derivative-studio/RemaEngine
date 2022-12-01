#ifndef REMA_ENGINE_PLATFORM_SETUP_H
#define REMA_ENGINE_PLATFORM_SETUP_H

#ifdef REMA_WIN
    #ifdef REMA_BUILD_DLL
        #define REMA_API __declspec(dllexport)
    #else
        #define REMA_API __declspec(dllimport)
    #endif // REMA_BUILD_DLL
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

#define BIT(x) (1 << x)
#define RUINT unsigned int

#endif // !REMA_ENGINE_PLATFORM_SETUP_H

