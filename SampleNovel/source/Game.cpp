#include <RemaEngine/RemaEngine.h>

class ExampleLayer : public RemaEngine::Layer
{
private:
    eastl::shared_ptr<RemaEngine::Shader> m_stTriangleShader;
    eastl::shared_ptr<RemaEngine::Shader> m_stSquareShader;

    eastl::shared_ptr<RemaEngine::VertexArray> m_pTriangleVertexArray;
    eastl::shared_ptr<RemaEngine::VertexArray> m_pSquareVertexArray;

    RemaEngine::OrthographicCamera m_stCamera;
    glm::vec3 m_vecCameraPosition;
    float m_fCameraRotation = 0.1f;
    float m_fCameraRotationSpeed = 0.7f;
    float m_fCameraMoveSpeed = 0.1f;

public:
    ExampleLayer()
        : Layer("Example"), m_stCamera(-1.6f, 1.6f, -0.9f, 0.9f), m_vecCameraPosition(0.0f)
    {
        m_pTriangleVertexArray.reset(RemaEngine::VertexArray::Create());

        float TriangleVertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.3f, 0.4f, 0.2f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.2f, 0.5f, 1.0f
        };

        eastl::shared_ptr<RemaEngine::VertexBuffer> m_pTriangleVertexBuffer;
        m_pTriangleVertexBuffer.reset(RemaEngine::VertexBuffer::Create(TriangleVertices, sizeof(TriangleVertices)));
        RemaEngine::BufferLayout layout = {
            { RemaEngine::ShaderDataType::Float3, "a_Position" },
            { RemaEngine::ShaderDataType::Float4, "a_Color" }
        };

        m_pTriangleVertexBuffer->SetLayout(layout);
        m_pTriangleVertexArray->AddVertexBuffer(m_pTriangleVertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        eastl::shared_ptr<RemaEngine::IndexBuffer> m_pTriangleIndexBuffer;
        m_pTriangleIndexBuffer.reset(RemaEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_pTriangleVertexArray->SetIndexBuffer(m_pTriangleIndexBuffer);

        m_pSquareVertexArray.reset(RemaEngine::VertexArray::Create());

        float SquareVertices[3 * 4] = {
           -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f,  0.75f, 0.0f,
           -0.75f,  0.75f, 0.0f
        };

        eastl::shared_ptr<RemaEngine::VertexBuffer> m_pSquareVertexBuffer;
        m_pSquareVertexBuffer.reset(RemaEngine::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));

        RemaEngine::BufferLayout SquareVBLayout = {
            { RemaEngine::ShaderDataType::Float3, "a_Position" },
        };

        m_pSquareVertexBuffer->SetLayout(SquareVBLayout);
        m_pSquareVertexArray->AddVertexBuffer(m_pSquareVertexBuffer);

        uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        eastl::shared_ptr<RemaEngine::IndexBuffer> m_pSquareIndexBuffer;
        m_pSquareIndexBuffer.reset(RemaEngine::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
        m_pSquareVertexArray->SetIndexBuffer(m_pSquareIndexBuffer);

        std::string TriangleVtxShader = R"(
            # version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            
            uniform mat4 u_ViewProjection;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string TriangleFragShader = R"(
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

        m_stTriangleShader.reset(new RemaEngine::Shader(TriangleVtxShader, TriangleFragShader));

        std::string SquareVtxShader = R"(
            # version 330 core

            layout(location = 0) in vec3 a_Position;
            
            uniform mat4 u_ViewProjection;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
            }
        )";

        std::string SquareFragShader = R"(
            # version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
            }
        )";

        m_stSquareShader.reset(new RemaEngine::Shader(SquareVtxShader, SquareFragShader));
    }

    void OnUpdate(RemaEngine::Timestep a_stTimestep) override
    {
        REMA_APP_TRACE("Delta time: {0}s", a_stTimestep.GetSeconds());

        if (RemaEngine::Input::IsKeyPressed(REMA_KEY_A)) {
            m_vecCameraPosition.x -= m_fCameraMoveSpeed * a_stTimestep;
        }
        else if (RemaEngine::Input::IsKeyPressed(REMA_KEY_D)) {
            m_vecCameraPosition.x += m_fCameraMoveSpeed * a_stTimestep;
        }

        if (RemaEngine::Input::IsKeyPressed(REMA_KEY_S)) {
            m_vecCameraPosition.y -= m_fCameraMoveSpeed * a_stTimestep;
        }
        else if (RemaEngine::Input::IsKeyPressed(REMA_KEY_W)) {
            m_vecCameraPosition.y += m_fCameraMoveSpeed * a_stTimestep;
        }

        if (RemaEngine::Input::IsKeyPressed(REMA_KEY_Q)) {
            m_fCameraRotation -= m_fCameraRotationSpeed * a_stTimestep;
        }
        else if (RemaEngine::Input::IsKeyPressed(REMA_KEY_E)) {
            m_fCameraRotation += m_fCameraRotationSpeed * a_stTimestep;
        }

        RemaEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RemaEngine::RenderCommand::Clear();

        m_stCamera.SetPosition(m_vecCameraPosition);
        m_stCamera.SetRotation(m_fCameraRotation);

        RemaEngine::Renderer::BeginScene(m_stCamera);
        RemaEngine::Renderer::Submit(m_stSquareShader, m_pSquareVertexArray);
        RemaEngine::Renderer::Submit(m_stTriangleShader, m_pTriangleVertexArray);
        RemaEngine::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        
    }

    void OnEvent(RemaEngine::Event& a_stEvent) override
    {
    }

};

class Game : public RemaEngine::Engine
{
public:
    Game()
    {
        PushLayer(new ExampleLayer());
    }

    ~Game()
    {

    }
};

RemaEngine::Engine* RemaEngine::CreateApplication()
{
    return new Game();
}

