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

    /// FAKE VARS
    int selectedItem = 1;

    const char* reds[22] = { "red_enemy_1", "red_enemy_2", "red_enemy_3", "red_enemy_4", "red_enemy_5", "red_enemy_6", "red_enemy_7", "red_enemy_8", "red_enemy_9", "red_enemy_10", "red_enemy_10",
    "yellow_enemy_1", "yellow_enemy_2", "yellow_enemy_3", "yellow_enemy_4", "yellow_enemy_5", "yellow_enemy_6", "yellow_enemy_7", "yellow_enemy_8", "yellow_enemyy_9", "yellow_enemy_10", "yellow_enemy_10" };
    std::string yells[10] = {  };
    std::string greens[10] = { "green_enemy_1", "green_enemy_2", "green_enemy_3", "green_enemy_4", "green_enemy_5", "green_enemy_6", "green_enemy_7", "green_enemy_8", "green_enemy_9", "green_enemy_10" };

    std::string logText = "sdfsfdsfsdfsdfssdf \n sfdsfsdfsfsdfsdfsd";

    glm::vec4 mvColorEdit = { 0.0f, 0.0f, 0.0f, 1.0f };
    glm::vec4 mvColorPicker = { 0.0f, 0.0f, 0.0f, 1.0f };

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
