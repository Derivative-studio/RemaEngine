#include "SampleNovel/Sample2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

Sample2D::Sample2D()
    : Layer("Sample2D"), m_stCameraController(1280.0f / 720.0f), m_vecSquarePosition(0.0f)
{
}

void Sample2D::OnAttach()
{
    m_stCheckerTexture = RemaEngine::Texture2D::Create("assets/textures/checker.jpg");
}

void Sample2D::OnDetach()
{

}

void Sample2D::OnUpdate(RemaEngine::Timestep a_stTimestep)
{
    // Update
    m_stCameraController.OnUpdate(a_stTimestep);

    // Render
    RemaEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
    RemaEngine::RenderCommand::Clear();

    RemaEngine::Renderer2D::BeginScene(m_stCameraController.GetCamera());
    RemaEngine::Renderer2D::DrawQuad({ -1.0f, 0.0f}, { 0.8f, 0.8f }, {0.8f, 0.2f, 0.3f, 1.0f});
    RemaEngine::Renderer2D::DrawQuad({ 0.5f, -0.5f}, { 0.5f, 0.75f }, {0.2f, 0.3f, 0.8f, 1.0f});
    RemaEngine::Renderer2D::DrawQuad({ 0.2f, 0.5f}, { 0.5f, 0.5f }, m_stCheckerTexture);
    RemaEngine::Renderer2D::EndScene();
}

void Sample2D::OnEvent(RemaEngine::Event& a_stEvent)
{
    m_stCameraController.OnEvent(a_stEvent);
}

void Sample2D::OnImGuiRender()
{
    ImGui::Begin("Settings");
    ImGui::ColorEdit4("Square Color", glm::value_ptr(m_vecSquareColor));
    ImGui::End();
}
