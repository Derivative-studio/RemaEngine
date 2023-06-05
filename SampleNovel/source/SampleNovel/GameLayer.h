#ifndef INVADERS_GAMELAYER_H
#define INVADERS_GAMELAYER_H

#include "SampleNovel/Level.h"
#include <RemaEngine/RemaEngine.h>

class GameLayer : public RemaEngine::Layer
{
private:
    RemaEngine::ref<RemaEngine::Shader> m_stFlatColorShader;

    RemaEngine::ref<RemaEngine::Texture2D> m_stRedEnemyTexture;
    RemaEngine::ref<RemaEngine::Texture2D> m_stGreenEnemyTexture;
    RemaEngine::ref<RemaEngine::Texture2D> m_stYellowEnemyTexture;
    RemaEngine::ref<RemaEngine::Texture2D> m_stExtraEnemyTexture;
    RemaEngine::ref<RemaEngine::Texture2D> m_stPlayer1Texture;
    RemaEngine::ref<RemaEngine::Texture2D> m_stPlayer2Texture;

    RemaEngine::OrthographicCameraController m_stCameraController;

    Level m_stLevel;

public:
    GameLayer();
    virtual ~GameLayer() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    virtual void OnUpdate(RemaEngine::Timestep a_stTimestep) override;
    virtual void OnEvent(RemaEngine::Event& a_stEvent) override;
    virtual void OnImGuiRender() override;
};

#endif // !INVADERS_GAMELAYER_H
