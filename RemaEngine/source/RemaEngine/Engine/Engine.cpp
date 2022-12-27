#include <remapch.h>
#include <RemaEngine/Engine/Engine.h>
#include <RemaEngine/Event/ApplicationEvent.h>
#include <RemaEngine/System/Logger.h>

#include <GLFW/glfw3.h>

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

    void Engine::OnEvent(Event& a_stEvent)
    {
        EventDispatcher dispatcher(a_stEvent);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Engine::CloseWindow));
        REMA_LOG_CORE_INFO("{0}", a_stEvent);
    }

    void Engine::Run()
    {
        while (m_bRunning)
        {
            glClearColor(1, 0, 1, 1);
            glClear(GL_COLOR_BUFFER_BIT);
            m_stWindow->OnUpdate();
        }
    }

    bool Engine::CloseWindow(WindowClosedEvent& a_stEvent)
    {
        m_bRunning = false;
        return true;
    }
}