#ifndef REMA_ENGINE_H
#define REMA_ENGINE_H

#include <RemaEngine/IO/Window.h>
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
        LayerStack m_stLayerStack;
        static Engine* s_Instance;

        bool CloseWindow(WindowClosedEvent& a_stEvent);

    public:
        Engine();
        virtual ~Engine();

        void Run();

        void OnEvent(Event& a_stEvent);
        void PushLayer(Layer* a_stLayer);
        void PushOverlay(Layer* a_stOverlay);

        inline Window& GetWindow() { return *m_stWindow; } 
        inline static Engine& GetInstance() { return *s_Instance; }
    };

    // Need to be defined on client side
    Engine* CreateApplication();
}

#endif REMA_ENGINE_H // !REMA_ENGINE_H

