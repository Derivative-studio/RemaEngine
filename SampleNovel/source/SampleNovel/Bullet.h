#ifndef INVADERS_BULLET_H
#define INVADERS_BULLET_H

#include <RemaEngine/RemaEngine.h>

class Bullet
{
private:
    float m_fSpeed = 4.0f;
    glm::vec2 m_vecPosition;

    float m_bHit = false;
    float m_bShoot = false;

    RemaEngine::ref<RemaEngine::Texture2D> m_stCrashBulletTexture;
    RemaEngine::ref<RemaEngine::Texture2D> m_StHitBulletTexture;

public:
    Bullet();
    ~Bullet() = default;

    void OnUpdate(RemaEngine::Timestep& a_stTimestep);
    void OnRender();

    void Shoot(glm::vec2& a_vecPlayerPosition);

    void SetPosition(glm::vec2 a_vecPosition) { m_vecPosition = a_vecPosition; }

    const glm::vec2& GetPosition() const { return m_vecPosition; }
    glm::vec2& GetPosition() { return m_vecPosition; }

};

#endif // !INVADERS_BULLET_H
