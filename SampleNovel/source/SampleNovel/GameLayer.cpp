#include "GameLayer.h"

GameLayer::GameLayer()
    : Layer("GameLayer"),
    m_stCameraController(1280.0f / 720.0f, true)
{

}

void GameLayer::OnAttach()
{
    REMA_PROFILE_FUNCTION();
    m_stLevel.Init();
}

void GameLayer::OnDetach()
{
    REMA_PROFILE_FUNCTION();

}

void GameLayer::OnUpdate(RemaEngine::Timestep a_stTimestep)
{
    REMA_PROFILE_FUNCTION("GameUpdate");

    // Update
    {
        REMA_SET_PROFILE_SCOPE("CameraControllerUpdate");
        m_stCameraController.OnUpdate(a_stTimestep);
        m_stLevel.OnUpdate(a_stTimestep);
    }

    // Prerender
    {
        REMA_SET_PROFILE_SCOPE("GamePrerender");
        RemaEngine::RenderCommand::SetClearColor({ 0.0f, 0.0f, 0.0f, 1.0f });
        RemaEngine::RenderCommand::Clear();
    }

    // Render
    {
        REMA_SET_PROFILE_SCOPE("GameRender");

        RemaEngine::Renderer2D::BeginScene(m_stCameraController.GetCamera());
        m_stLevel.OnRender();
        RemaEngine::Renderer2D::EndScene();
    }
}

void GameLayer::OnEvent(RemaEngine::Event& a_stEvent)
{
    REMA_PROFILE_FUNCTION();

}

void GameLayer::OnImGuiRender()
{
    REMA_PROFILE_FUNCTION();

}
