#include "SampleNovel/Sample2D.h"

#include <RemaEngine/RemaEngine.h>
#include <RemaEngine/Graphics/OpenGL/OpenGLShader.h>
#include <RemaEngine/Graphics/ShaderLibrary.h>
#include <RemaEngine/Utils/MemoryUtils.h>
#include <RemaEngine/Engine/EntryPoint.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

class ExampleLayer : public RemaEngine::Layer
{
private:
    RemaEngine::ShaderLibrary m_stShaderLibrary;

    RemaEngine::ref<RemaEngine::Shader> m_stTriangleShader;
    RemaEngine::ref<RemaEngine::Shader> m_stFlatColorShader;

    RemaEngine::ref<RemaEngine::Texture2D> m_stCheckerTexture;
    RemaEngine::ref<RemaEngine::Texture2D> m_stTransparentTexture;

    RemaEngine::ref<RemaEngine::VertexArray> m_pTriangleVertexArray;
    RemaEngine::ref<RemaEngine::VertexArray> m_pSquareVertexArray;

    RemaEngine::OrthographicCameraController m_stCameraController;

    glm::vec3 m_vecSquarePosition;
    float m_fSquareMoveSpeed = 13.0f;

    glm::vec3 m_vecSquareColor = { 0.2f, 0.3f, 0.7f };

public:
    ExampleLayer()
        : Layer("Example"), m_stCameraController(1280.0f / 720.0f), m_vecSquarePosition(0.0f)
    {
        m_pTriangleVertexArray = RemaEngine::VertexArray::Create();

        float TriangleVertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.3f, 0.4f, 0.2f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.2f, 0.5f, 1.0f
        };

        RemaEngine::ref<RemaEngine::VertexBuffer> m_pTriangleVertexBuffer;
        m_pTriangleVertexBuffer.reset(RemaEngine::VertexBuffer::Create(TriangleVertices, sizeof(TriangleVertices)));
        RemaEngine::BufferLayout layout = {
            { RemaEngine::ShaderDataType::Float3, "a_Position" },
            { RemaEngine::ShaderDataType::Float4, "a_Color" }
        };

        m_pTriangleVertexBuffer->SetLayout(layout);
        m_pTriangleVertexArray->AddVertexBuffer(m_pTriangleVertexBuffer);

        uint32_t indices[3] = { 0, 1, 2 };
        RemaEngine::ref<RemaEngine::IndexBuffer> m_pTriangleIndexBuffer;
        m_pTriangleIndexBuffer.reset(RemaEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_pTriangleVertexArray->SetIndexBuffer(m_pTriangleIndexBuffer);

        m_pSquareVertexArray = RemaEngine::VertexArray::Create();

        float SquareVertices[5 * 4] = {
           -0.75f, -0.75f, 0.0f, 0.0f, 0.0f,
            0.75f, -0.75f, 0.0f, 1.0f, 0.0f,
            0.75f,  0.75f, 0.0f, 1.0f, 1.0f,
           -0.75f,  0.75f, 0.0f, 0.0f, 1.0f
        };

        RemaEngine::ref<RemaEngine::VertexBuffer> m_pSquareVertexBuffer;
        m_pSquareVertexBuffer.reset(RemaEngine::VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));

        RemaEngine::BufferLayout SquareVBLayout = {
            { RemaEngine::ShaderDataType::Float3, "a_Position" },
            { RemaEngine::ShaderDataType::Float2, "a_TexCoord"}
        };

        m_pSquareVertexBuffer->SetLayout(SquareVBLayout);
        m_pSquareVertexArray->AddVertexBuffer(m_pSquareVertexBuffer);

        uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        RemaEngine::ref<RemaEngine::IndexBuffer> m_pSquareIndexBuffer;
        m_pSquareIndexBuffer.reset(RemaEngine::IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
        m_pSquareVertexArray->SetIndexBuffer(m_pSquareIndexBuffer);

        eastl::string TriangleVtxShader = R"(
            # version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_TransformMatrix;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = u_ViewProjection * u_TransformMatrix * vec4(a_Position, 1.0);
            }
        )";

        eastl::string TriangleFragShader = R"(
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

        //m_stTriangleShader = RemaEngine::Shader::Create("TriangleShader", TriangleVtxShader, TriangleFragShader);
        //m_stFlatColorShader = RemaEngine::Shader::Create("assets/shaders/FlatColorShader.glsl");

        auto textureShader = m_stShaderLibrary.Load("assets/shaders/TextureShader.glsl");
        m_stCheckerTexture = RemaEngine::Texture2D::Create("assets/textures/checker.jpg");
        m_stTransparentTexture = RemaEngine::Texture2D::Create("assets/textures/red.png");

        RemaEngine::eastl_dynamic_pointer_cast<RemaEngine::OpenGLShader>(textureShader)->Bind();
        RemaEngine::eastl_dynamic_pointer_cast<RemaEngine::OpenGLShader>(textureShader)->UploadUniformInt("u_Texture", 0);

    }

    void OnUpdate(RemaEngine::Timestep a_stTimestep) override
    {
        m_stCameraController.OnUpdate(a_stTimestep);

        if (RemaEngine::Input::IsKeyPressed(REMA_KEY_LEFT)) {
            m_vecSquarePosition.x -= m_fSquareMoveSpeed * a_stTimestep;
        }
        else if (RemaEngine::Input::IsKeyPressed(REMA_KEY_RIGHT)) {
            m_vecSquarePosition.x += m_fSquareMoveSpeed * a_stTimestep;
        }

        if (RemaEngine::Input::IsKeyPressed(REMA_KEY_DOWN)) {
            m_vecSquarePosition.y -= m_fSquareMoveSpeed * a_stTimestep;
        }
        else if (RemaEngine::Input::IsKeyPressed(REMA_KEY_UP)) {
            m_vecSquarePosition.y += m_fSquareMoveSpeed * a_stTimestep;
        }

        RemaEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
        RemaEngine::RenderCommand::Clear();

        RemaEngine::Renderer::BeginScene(m_stCameraController.GetCamera());

        glm::mat4 mtxTransform = glm::translate(glm::mat4(1.0f), m_vecSquarePosition);

        auto textureShader = m_stShaderLibrary.Get("TextureShader");

        m_stCheckerTexture->Bind();
        RemaEngine::Renderer::Submit(textureShader, m_pSquareVertexArray, mtxTransform);

        m_stTransparentTexture->Bind();
        RemaEngine::Renderer::Submit(textureShader, m_pSquareVertexArray, mtxTransform);

        //RemaEngine::Renderer::Submit(m_stTriangleShader, m_pTriangleVertexArray);

        RemaEngine::Renderer::EndScene();
    }

    virtual void OnImGuiRender() override
    {
        ImGui::Begin("Settings");
        ImGui::ColorEdit3("Square Color", glm::value_ptr(m_vecSquareColor));
        ImGui::End();
    }

    void OnEvent(RemaEngine::Event& a_stEvent) override
    {
        m_stCameraController.OnEvent(a_stEvent);
    }

};

class Game : public RemaEngine::Engine
{
public:
    Game()
    {
        //PushLayer(new ExampleLayer());
        PushLayer(new Sample2D());
    }

    ~Game()
    {

    }
};

RemaEngine::Engine* RemaEngine::CreateApplication()
{
    return new Game();
}

