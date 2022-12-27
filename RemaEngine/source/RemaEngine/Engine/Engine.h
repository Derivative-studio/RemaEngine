#ifndef REMA_ENGINE_H
#define REMA_ENGINE_H

#include <RemaEngine/Engine/EnginePlatformSetup.h>
#include <RemaEngine/Gui/Window.h>
#include <RemaEngine/Event/Event.h>

namespace RemaEngine
{
    class REMA_API Engine
    {
    private:
        std::unique_ptr<Window> m_stWindow;
        bool m_bRunning = true;

    public:
        Engine();
        virtual ~Engine();

        void Run();
    };

    // Need to be defined on client side
    Engine* CreateApplication();
}

#endif REMA_ENGINE_H // !REMA_ENGINE_H

