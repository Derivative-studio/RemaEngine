#ifndef REMA_ENGINE_H
#define REMA_ENGINE_H

#include <RemaEngine/Gui/Window.h>
#include <RemaEngine/Event/Event.h>
#include <RemaEngine/Engine/LayerStack.h>
#include <RemaEngine/Event/ApplicationEvent.h>
#include <RemaEngine/Engine/EnginePlatformSetup.h>

namespace RemaEngine
{
    class REMA_API Engine
    {
    private:
        std::unique_ptr<Window> m_stWindow;
        bool m_bRunning = true;

        bool CloseWindow(WindowClosedEvent& a_stEvent);

    public:
        Engine();
        virtual ~Engine();

        void Run();

        void OnEvent(Event& a_stEvent);
    };

    // Need to be defined on client side
    Engine* CreateApplication();
}

#endif REMA_ENGINE_H // !REMA_ENGINE_H

