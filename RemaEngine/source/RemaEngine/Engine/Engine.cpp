#include <remapch.h>
#include <RemaEngine/Engine/Engine.h>
#include <RemaEngine/Event/ApplicationEvent.h>
#include <RemaEngine/System/Logger.h>

#include <glad/glad.h>

namespace RemaEngine
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Engine::Engine()
    {
        m_stWindow = std::unique_ptr<Window>(Window::Create());
        m_stWindow->SetEventCallback(BIND_EVENT_FN(Engine::OnEvent));
    }

    Engine::~Engine()
    {

    }

    void Engine::PushLayer(Layer* a_stLayer)
    {
        m_stLayerStack.PushLayer(a_stLayer);
    }

    void Engine::PushOverlay(Layer* a_stOverlay)
    {
        m_stLayerStack.PushOverlay(a_stOverlay);
    }

    void Engine::OnEvent(Event& a_stEvent)
    {
        EventDispatcher dispatcher(a_stEvent);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Engine::CloseWindow));
        REMA_LOG_CORE_INFO("{0}", a_stEvent);

        for (auto it = m_stLayerStack.end(); it != m_stLayerStack.begin();){
            (*--it)->OnEvent(a_stEvent);
            if (a_stEvent.m_bHandled) {
                break;
            }
        }
    }

    void Engine::Run()
    {
        while (m_bRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            for (Layer* layer : m_stLayerStack) {
                layer->OnUpdate();
            }

            m_stWindow->OnUpdate();
        }
    }

    bool Engine::CloseWindow(WindowClosedEvent& a_stEvent)
    {
        m_bRunning = false;
        return true;
    }
}