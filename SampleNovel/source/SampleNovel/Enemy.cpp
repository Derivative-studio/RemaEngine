#include "Enemy.h"

void Enemy::OnUpdate(RemaEngine::Timestep a_stTimestep)
{
    //m_Bullets[m_nCurrentBulletIndex].OnUpdate(a_stTimestep);
}

void Enemy::OnRender()
{
    RemaEngine::Renderer2D::DrawQuad({ m_vecPosition.x, m_vecPosition.y, 0.2f }, { 0.08f, 0.08f }, m_stEnemyDefaultTexture);
    //m_Bullets[m_nCurrentBulletIndex].OnRender();
}

void Enemy::LoadAsset(const eastl::string& a_sTexturePath, int a_nCost)
{
    m_nCost = a_nCost;
    m_stEnemyDefaultTexture = RemaEngine::Texture2D::Create(a_sTexturePath);
    for (int i{}; i < m_Bullets.size(); i++) {
        Bullet bullet;
        m_Bullets.push_back(bullet);
    }
}

void Enemy::Move(glm::vec2& a_vecMoveTo)
{
    m_vecPosition = a_vecMoveTo;
}

void Enemy::Shoot(glm::vec2& a_vecEnemyPosition)
{
    //m_Bullets[m_nCurrentBulletIndex].Shoot(a_vecEnemyPosition);
}
