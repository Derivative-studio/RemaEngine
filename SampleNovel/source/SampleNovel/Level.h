#ifndef INVADERS_LEVEL_H
#define INVADERS_LEVEL_H

#include "SampleNovel/Player.h"
#include "SampleNovel/Bullet.h"
#include "SampleNovel/Enemy.h"

#include <RemaEngine/RemaEngine.h>

class Level
{
private:
    Player m_stPlayer1;
    //Player m_stPlayer2;

    eastl::vector<Enemy> m_vecGreens;
    eastl::vector<Enemy> m_vecReds;
    eastl::vector<Enemy> m_vecYellows;

    RemaEngine::ref<RemaEngine::Texture2D> m_stStarfieldBGTexture;

    bool m_bGameOver = false;

public:
    void Init();

    void OnUpdate(RemaEngine::Timestep a_stTimestep);
    void OnRender();
    void OnImGuiLayer();

};

#endif // !INVADERS_LEVEL_H
