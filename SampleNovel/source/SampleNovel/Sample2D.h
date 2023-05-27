/**
 * @file SampleNovel/Sample2D.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-25
 * @copyright Copyright (c) 2023
 *
 * This file is part of RemaEngine.
 *
 * RemaEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RemaEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 **/

#include <RemaEngine/RemaEngine.h>

class Sample2D : public RemaEngine::Layer
{
private:
    RemaEngine::ShaderLibrary m_stShaderLibrary;
    RemaEngine::ref<RemaEngine::Shader> m_stFlatColorShader;
    RemaEngine::ref<RemaEngine::Texture2D> m_stCheckerTexture;

    glm::vec3 m_vecSquarePosition;
    float m_fSquareMoveSpeed = 13.0f;
    RemaEngine::ref<RemaEngine::VertexArray> m_pSquareVertexArray;
    glm::vec4 m_vecSquareColor = { 0.2f, 0.3f, 0.7f, 1.0f };

    RemaEngine::OrthographicCameraController m_stCameraController;

public:
    Sample2D();
    virtual ~Sample2D() = default;

    virtual void OnAttach() override;
    virtual void OnDetach() override;

    void OnUpdate(RemaEngine::Timestep a_stTimestep) override;
    void OnEvent(RemaEngine::Event& a_stEvent) override;
    virtual void OnImGuiRender() override;

};

