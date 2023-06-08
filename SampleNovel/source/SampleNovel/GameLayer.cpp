#include "GameLayer.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

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

    ImGui::Begin("Scene edit");
    ImGui::Text("Color Picker");
    ImGui::ColorPicker3(" ", glm::value_ptr(mvColorPicker));
    ImGui::Text("Object bank");
    ImGui::ListBox(" ", &selectedItem, reds, 22, 15);
    ImGui::Button("Create object", { 200 , 20});
    ImGui::End();

    ImGui::Begin("Log");
    ImGui::TextColored({ 0.1f, 0.4f, 0.4f, 1.0f }, "[00:14:24] [ENGINE info]: Object green_enemy_11 created");
    ImGui::TextColored({ 0.1f, 0.4f, 0.4f, 1.0f }, "[00:13:53] [ENGINE info]: Object green_enemy_10 created");
    ImGui::TextColored({ 0.1f, 0.4f, 0.4f, 1.0f }, "[00:05:36] [ENGINE info]: Color changed red_enemy_4");
    ImGui::TextColored({ 0.1f, 0.4f, 0.4f, 1.0f }, "[23:58:12] [ENGINE info]: Object green_enemy_9 created");
    ImGui::TextColored({ 0.1f, 0.4f, 0.4f, 1.0f }, "[23:57:45] [ENGINE info]: Object green_enemy_8 created");
    ImGui::TextColored({ 0.1f, 0.4f, 0.4f, 1.0f }, "[23:57:14] [ENGINE info]: Object green_enemy_7 created");
    ImGui::End();
}
