#ifndef INVADERS_ENEMY_H
#define INVADERS_ENEMY_H

#include "SampleNovel/Bullet.h"
#include <RemaEngine/RemaEngine.h>

class Enemy
{
private:
    int m_nCost = 10;
    bool m_bDead = false;
    glm::vec2 m_vecPosition = { 0.0f, 0.0f };

    int m_nCurrentBulletIndex = 0;
    eastl::ring_buffer<Bullet> m_Bullets;
    RemaEngine::ref<RemaEngine::Texture2D> m_stEnemyDefaultTexture;

public:
    ~Enemy() = default;

    void OnUpdate(RemaEngine::Timestep a_stTimestep);
    void OnRender();
    void LoadAsset(const eastl::string& a_sTexturePath, int a_nCost);

    void Move(glm::vec2& a_vecMoveTo);
    void Shoot(glm::vec2& a_vecEnemyPosition);


};

#endif // !INVADERS_ENEMY_H
