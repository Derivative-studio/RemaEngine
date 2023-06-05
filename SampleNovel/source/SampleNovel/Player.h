#ifndef INVADERS_PLAYER_H
#define INVADERS_PLAYER_H

#include "SampleNovel/Bullet.h"

#include <RemaEngine/RemaEngine.h>
#include <glm/glm.hpp>

class Player
{
private:
    int m_nTryCount = 3;
    int m_nScore = 0;
    int m_nHighScore = 0;

    int m_nCurrentBulletIndex = 0;
    eastl::ring_buffer<Bullet> m_Bullets;

    RemaEngine::ref<RemaEngine::Texture2D> m_stPlayerTexture;
    glm::vec2 m_vecPosition = { -1.0f, -0.8f };
    float m_fPlayerSpeed = 1.5f;

public:
    Player() {};
    ~Player() = default;

    void OnUpdate(RemaEngine::Timestep& a_stTimestep);
    void OnRender();
    void OnImGuiRender();

    void LoadAsset();
    void Reset();

    int GetTryCount() const { return m_nTryCount; }
    int GetHighScore() const { return m_nHighScore; }
    int GetCurrentScore() const { return m_nScore; }

    const glm::vec2& GetPosition() const { return m_vecPosition; }
    glm::vec2& GetPosition() { return m_vecPosition; }

};

#endif // !INVADERS_PLAYER_H
