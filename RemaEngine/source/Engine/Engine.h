#ifndef REMA_ENGINE_H
#define REMA_ENGINE_H

#include <Engine/EnginePlatformSetup.h>
#include <Event/Event.h>

namespace RemaEngine
{
    class REMA_API Engine
    {
    private:

    public:
        Engine();
        virtual ~Engine();

        void Run();
    };

    // Need to be defined on client side
    Engine* CreateApplication();
}

#endif REMA_ENGINE_H // !REMA_ENGINE_H

