#include <remapch.h>

#include <RemaEngine/IO/Input.h>
#include <RemaEngine/Engine/Engine.h>
#include <RemaEngine/System/Logger.h>
#include <RemaEngine/Event/ApplicationEvent.h>

#include <glad/glad.h>

namespace RemaEngine
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Engine* Engine::s_Instance = nullptr;

    Engine::Engine()
    {
        REMA_CORE_ASSERT(s_Instance, "Engine instance already exists");
        s_Instance = this;

        m_stWindow = std::unique_ptr<Window>(Window::Create());
        m_stWindow->SetEventCallback(BIND_EVENT_FN(Engine::OnEvent));

        m_stpImGuiLayer = new ImGuiLayer();
        PushOverlay(m_stpImGuiLayer);

        glGenVertexArrays(1, &m_unVertexArray);
        glBindVertexArray(m_unVertexArray);

        float vertices[3 * 3] = {
            -0.5f, -0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
             0.0f, 0.5f, 0.0f
        };

        m_pVertexBuffer.reset(VirtualVertexBuffer::Create(vertices, sizeof(vertices)));

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        uint32_t indices[3] = { 0, 1, 2 };
        m_pIndexBuffer.reset(VirtualIndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string tmpVtxShader = R"(
            # version 330 core
            
            layout(location = 0) in vec3 a_Position;
            out vec3 v_Position;
            
            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string tmpFragShader = R"(
            # version 330 core
            
            layout(location = 0) out vec4 color;
            in vec3 v_Position;
            
            void main()
            {
                color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
            }
        )";

        m_stShader.reset(new Shader(tmpVtxShader, tmpFragShader));
    }

    Engine::~Engine()
    {

    }

    void Engine::PushLayer(Layer* a_stLayer)
    {
        m_stLayerStack.PushLayer(a_stLayer);
        a_stLayer->OnAttach();
    }

    void Engine::PushOverlay(Layer* a_stOverlay)
    {
        m_stLayerStack.PushOverlay(a_stOverlay);
        a_stOverlay->OnAttach();
    }

    void Engine::OnEvent(Event& a_stEvent)
    {
        EventDispatcher dispatcher(a_stEvent);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Engine::CloseWindow));

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
            glClearColor(0, 0, 0, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_stShader->Bind();

            glBindVertexArray(m_unVertexArray);
            glDrawElements(GL_TRIANGLES, m_pIndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

            for (Layer* layer : m_stLayerStack) {
                layer->OnUpdate();
            }

            m_stpImGuiLayer->Begin();

            for (Layer* layer : m_stLayerStack) {
                layer->OnImGuiRender();
            }

            m_stpImGuiLayer->End();

            m_stWindow->OnUpdate();
        }
    }

    bool Engine::CloseWindow(WindowClosedEvent& a_stEvent)
    {
        m_bRunning = false;
        return true;
    }
}