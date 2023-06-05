#include "Level.h"

void Level::Init()
{
    m_stStarfieldBGTexture = RemaEngine::Texture2D::Create("assets/textures/environment/starfield.png");
    m_stPlayer1.LoadAsset();

    m_vecYellows.resize(22);
    m_vecReds.resize(22);
    m_vecGreens.resize(11);

    // Yellows

    glm::vec2 xPose = { -0.75f, 0.0f };
    for (int i{}; i < 11; i++) {
        m_vecYellows[i] = Enemy();
        m_vecYellows[i].LoadAsset("assets/textures/enemy/yellow.png", 10);
        m_vecYellows[i].Move(xPose);
        xPose.x += 0.15;
    }

    xPose = { -0.75f, 0.15f };
    for (int i = 11; i < 22; i++) {
        m_vecYellows[i] = Enemy();
        m_vecYellows[i].LoadAsset("assets/textures/enemy/yellow.png", 10);
        m_vecYellows[i].Move(xPose);
        xPose.x += 0.15;
    }

    // Reds

    xPose = { -0.75f, 0.3f };
    for (int i{}; i < 11; i++) {
        m_vecReds[i] = Enemy();
        m_vecReds[i].LoadAsset("assets/textures/enemy/red.png", 10);
        m_vecReds[i].Move(xPose);
        xPose.x += 0.15;
    }

    xPose = { -0.75f, 0.45f };
    for (int i = 11; i < 22; i++) {
        m_vecReds[i] = Enemy();
        m_vecReds[i].LoadAsset("assets/textures/enemy/red.png", 10);
        m_vecReds[i].Move(xPose);
        xPose.x += 0.15;
    }

    // Greens

    xPose = { -0.75f, 0.6f };
    for (int i{}; i < 11; i++) {
        m_vecGreens[i] = Enemy();
        m_vecGreens[i].LoadAsset("assets/textures/enemy/green.png", 10);
        m_vecGreens[i].Move(xPose);
        xPose.x += 0.15;
    }

}

void Level::OnUpdate(RemaEngine::Timestep a_stTimestep)
{
    m_stPlayer1.OnUpdate(a_stTimestep);

    //for (auto& enemy : m_vecYellows) {
    //    enemy.OnUpdate(a_stTimestep);
    //}
}

void Level::OnRender()
{
    RemaEngine::Renderer2D::DrawQuad({ 0.0f, 0.0f }, { 2.0f, 2.0f }, m_stStarfieldBGTexture, 5);
    m_stPlayer1.OnRender();

    for (auto enemy : m_vecYellows) {
        enemy.OnRender();
    }

    for (auto enemy : m_vecReds) {
        enemy.OnRender();
    }

    for (auto enemy : m_vecGreens) {
        enemy.OnRender();
    }
}

void Level::OnImGuiLayer()
{

}
