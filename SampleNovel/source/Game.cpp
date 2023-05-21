#include <RemaEngine/RemaEngine.h>
#include <RemaEngine/Graphics/OpenGL/OpenGLShader.h>
#include <RemaEngine/Utils/MemoryUtils.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

class ExampleLayer : public RemaEngine::Layer
{
private:
    RemaEngine::ref<RemaEngine::Shader> m_stTriangleShader;
    RemaEngine::ref<RemaEngine::Shader> m_stFlatColorShader;

    RemaEngine::ref<RemaEngine::Shader> m_stTextureShader;
    RemaEngine::ref<RemaEngine::Texture2D> m_stCheckerTexture;

    RemaEngine::ref<RemaEngine::VertexArray> m_pTriangleVertexArray;
    RemaEngine::ref<RemaEngine::VertexArray> m_pSquareVertexArray;

    RemaEngine::OrthographicCamera m_stCamera;
    glm::vec3 m_vecCameraPosition;
    /**
    * @brief Initial degree of camera rotation angle.
    **/
    float m_fCameraRotation = 0.0f;
    /**
    * @brief The initial rotation speed of the camera
    * in degrees per second.
    **/
    float m_fCameraRotationSpeed = 180.0f;
    /**
    * @brief The initial movement speed of the camera
    * in units per second.
    **/
    float m_fCameraMoveSpeed = 10.0f;

    glm::vec3 m_vecSquarePosition;
    float m_fSquareMoveSpeed = 13.0f;

    glm::vec3 m_vecSquareColor = { 0.2f, 0.3f, 0.7f };

public:
    ExampleLayer()
        : Layer("Example"), m_stCamera(-1.6f, 1.6f, -0.9f, 0.9f), m_vecCameraPosition(0.0f),
        m_vecSquarePosition(0.0f)
    {
        m_pTriangleVertexArray.reset(RemaEngine::VertexArray::Create());

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

        m_pSquareVertexArray.reset(RemaEngine::VertexArray::Create());

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

        m_stTriangleShader.reset(RemaEngine::Shader::Create(TriangleVtxShader, TriangleFragShader));

        eastl::string flatColorVertexShader = R"(
            # version 330 core

            layout(location = 0) in vec3 a_Position;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_TransformMatrix;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = u_ViewProjection * u_TransformMatrix * vec4(a_Position, 1.0);
            }
        )";

        eastl::string flatColorFragmentShader = R"(
            # version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            uniform vec3 u_Color;

            void main()
            {
                color = vec4(u_Color, 1.0);
            }
        )";

        m_stFlatColorShader.reset(RemaEngine::Shader::Create(flatColorVertexShader, flatColorFragmentShader));

        eastl::string textureVertexShader = R"(
            # version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_TexCoord;

            uniform mat4 u_ViewProjection;
            uniform mat4 u_TransformMatrix;

            out vec2 v_TexCoord;

            void main()
            {
                v_TexCoord = a_TexCoord;
                gl_Position = u_ViewProjection * u_TransformMatrix * vec4(a_Position, 1.0);
            }
        )";

        eastl::string textureFragmentShader = R"(
            # version 330 core

            layout(location = 0) out vec4 color;

            in vec2 v_TexCoord;

            uniform sampler2D u_Texture;

            void main()
            {
                color = texture(u_Texture, v_TexCoord);
            }
        )";

        m_stTextureShader.reset(RemaEngine::Shader::Create(textureVertexShader, textureFragmentShader));
        m_stCheckerTexture = RemaEngine::Texture2D::Create("assets/textures/checker.jpg");

        RemaEngine::eastl_dynamic_pointer_cast<RemaEngine::OpenGLShader>(m_stTextureShader)->Bind();
        RemaEngine::eastl_dynamic_pointer_cast<RemaEngine::OpenGLShader>(m_stTextureShader)->UploadUniformInt("u_Texture", 0);
    }

    void OnUpdate(RemaEngine::Timestep a_stTimestep) override
    {
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

        m_stCamera.SetPosition(m_vecCameraPosition);
        m_stCamera.SetRotation(m_fCameraRotation);

        RemaEngine::Renderer::BeginScene(m_stCamera);

        glm::mat4 mtxTransform = glm::translate(glm::mat4(1.0f), m_vecSquarePosition);

        //RemaEngine::eastl_dynamic_pointer_cast<RemaEngine::OpenGLShader>(m_stFlatColorShader)->Bind();
        //RemaEngine::eastl_dynamic_pointer_cast<RemaEngine::OpenGLShader>(m_stFlatColorShader)->UploadUniformFloat3("u_Color", m_vecSquareColor);

        m_stCheckerTexture->Bind();
        RemaEngine::Renderer::Submit(m_stTextureShader, m_pSquareVertexArray, mtxTransform);

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

