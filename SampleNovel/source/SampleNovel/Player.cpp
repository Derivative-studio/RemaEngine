#include "Player.h"

void Player::OnUpdate(RemaEngine::Timestep& a_stTimestep)
{
    if (RemaEngine::Input::IsKeyPressed(REMA_KEY_RIGHT) && m_vecPosition.x < 1.4f) {
        m_vecPosition.x += m_fPlayerSpeed * a_stTimestep;
    }
    else if(RemaEngine::Input::IsKeyPressed(REMA_KEY_LEFT) && m_vecPosition.x > -1.4f) {
        m_vecPosition.x -= m_fPlayerSpeed * a_stTimestep;
    }

    if (RemaEngine::Input::IsKeyPressed(REMA_KEY_SPACE)) {
        if (m_nCurrentBulletIndex >= 8) {
            m_nCurrentBulletIndex = 0;
        }
        m_Bullets[m_nCurrentBulletIndex].Shoot(m_vecPosition);
    }

    m_Bullets[m_nCurrentBulletIndex].OnUpdate(a_stTimestep);
}

void Player::OnRender()
{
    RemaEngine::Renderer2D::DrawQuad({ m_vecPosition.x, m_vecPosition.y, 0.2f }, { 0.05f, 0.1f }, m_stPlayerTexture);
    m_Bullets[m_nCurrentBulletIndex].OnRender();
}

void Player::OnImGuiRender()
{

}

void Player::LoadAsset()
{
    m_stPlayerTexture = RemaEngine::Texture2D::Create("assets/textures/player/player1.png");

    m_Bullets.resize(8);
    for (int i{}; i < m_Bullets.size(); i++) {
        Bullet bullet;
        m_Bullets.push_back(bullet);
    }
}

void Player::Reset()
{
    m_nScore = 0;
    m_nTryCount = 0;
    m_vecPosition = { 0.0f, 0.0f };
}
