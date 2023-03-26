#ifndef REMA_ENGINE_H
#define REMA_ENGINE_H

#include <RemaEngine/IO/Window.h>
#include <RemaEngine/Gui/ImGuiLayer.h>

#include <RemaEngine/Engine/LayerStack.h>
#include <RemaEngine/Engine/EnginePlatformSetup.h>

#include <RemaEngine/Event/Event.h>
#include <RemaEngine/Event/ApplicationEvent.h>

#include <RemaEngine/Graphics/OpenGL/Shader.h>
#include <RemaEngine/Graphics/VertexBuffer.h>
#include <RemaEngine/Graphics/IndexBuffer.h>


namespace RemaEngine
{
    class REMA_API Engine
    {
    private:
        std::unique_ptr<Window> m_stWindow;
        ImGuiLayer* m_stpImGuiLayer;
        bool m_bRunning = true;
        LayerStack m_stLayerStack;
        static Engine* s_Instance;

        bool CloseWindow(WindowClosedEvent& a_stEvent);

        RUINT m_unVertexArray;

        std::unique_ptr<Shader> m_stShader;
        std::unique_ptr<VertexBuffer> m_pVertexBuffer;
        std::unique_ptr<IndexBuffer> m_pIndexBuffer;

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

