#include <remapch.h>

#include <RemaEngine/IO/Input.h>
#include <RemaEngine/Engine/Engine.h>
#include <RemaEngine/System/Logger.h>
#include <RemaEngine/Event/ApplicationEvent.h>
#include <RemaEngine/Graphics/BufferLayout.h>

#include <glad/glad.h>

namespace RemaEngine
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Engine* Engine::s_Instance = nullptr;

    static GLenum ShaderDataType2OGLBaseType(ShaderDataType m_stDataType)
    {
        switch (m_stDataType)
        {
            case RemaEngine::ShaderDataType::Float:     return GL_FLOAT;
            case RemaEngine::ShaderDataType::Float2:    return GL_FLOAT;
            case RemaEngine::ShaderDataType::Float3:    return GL_FLOAT;
            case RemaEngine::ShaderDataType::Float4:    return GL_FLOAT;
            case RemaEngine::ShaderDataType::Mat3:      return GL_FLOAT;
            case RemaEngine::ShaderDataType::Mat4:      return GL_FLOAT;
            case RemaEngine::ShaderDataType::Int:       return GL_INT;
            case RemaEngine::ShaderDataType::Int2:      return GL_INT;
            case RemaEngine::ShaderDataType::Int3:      return GL_INT;
            case RemaEngine::ShaderDataType::Int4:      return GL_INT;
            case RemaEngine::ShaderDataType::Bool:      return GL_BOOL;
        }

        REMA_CORE_ASSERT(false, "Illigal shader data type");
        return 0;
    }

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

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.3f, 0.4f, 0.2f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.2f, 0.5f, 1.0f
        };

        m_pVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };

        uint32_t index = 0;
        //const auto& layout = m_pVertexBuffer->GetLayout();
        for (const auto& elem : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                elem.GetComponentCount(),
                ShaderDataType2OGLBaseType(elem.m_stShaderDataType),
                elem.m_bNormolized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)elem.m_unOffset);
            index++;
        }

        uint32_t indices[3] = { 0, 1, 2 };
        m_pIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));

        std::string tmpVtxShader = R"(
            # version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string tmpFragShader = R"(
            # version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
                color = v_Color;
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