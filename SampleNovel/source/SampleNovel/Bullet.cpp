#include "Bullet.h"

Bullet::Bullet()
{
    m_StHitBulletTexture = RemaEngine::Texture2D::Create("assets/textures/bullet-hit.png");
}

void Bullet::OnUpdate(RemaEngine::Timestep& a_stTimestep)
{
    if (m_vecPosition.y < 1) {
        m_vecPosition.y += m_fSpeed * a_stTimestep;
    }
    else
    {
        m_bShoot = false;
        m_vecPosition.y = -1.0f;
    }
}

void Bullet::OnRender()
{
    if (m_vecPosition.y < 1 && m_bShoot) {
        RemaEngine::Renderer2D::DrawQuad({ m_vecPosition.x, m_vecPosition.y, 0.2f }, { 0.005, 0.1 }, { 1.0f, 1.0f, 1.0f, 1.0f });
    }
    if (m_bHit) {
        RemaEngine::Renderer2D::DrawQuad({ m_vecPosition.x, m_vecPosition.y, 0.2f }, { 0.1, 0.1 }, m_StHitBulletTexture);
        m_bHit = false;
    }
}

void Bullet::Shoot(glm::vec2& a_vecPlayerPosition)
{
    if (m_bShoot == false) {
        SetPosition(a_vecPlayerPosition);
        m_bShoot = true;
    }
}
