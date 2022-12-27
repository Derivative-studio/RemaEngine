#include <remapch.h>
#include <RemaEngine/Engine/Engine.h>
#include <RemaEngine/Event/ApplicationEvent.h>
#include <RemaEngine/System/Logger.h>

#include <GLFW/glfw3.h>

namespace RemaEngine
{
    Engine::Engine()
    {
        m_stWindow = std::unique_ptr<Window>(Window::Create());
    }

    Engine::~Engine()
    {

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
}