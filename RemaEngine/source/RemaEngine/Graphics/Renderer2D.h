/**
 * @file RemaEngine/Graphics/Renderer2D.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-23
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
#ifndef REMA_RENDERER2D_H
#define REMA_RENDERER2D_H

#include "RemaEngine/Scene/Camera.h"

namespace RemaEngine
{
    class Renderer2D
    {
    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(const OrthographicCamera& m_stOrthoCamera);
        static void EndScene();

        // Primitives
        static void DrawQuad(const glm::vec2& a_vecPosition, const glm::vec2& a_vecSize, const glm::vec4& a_vecColor);
        static void DrawQuad(const glm::vec3& a_vecPosition, const glm::vec2& a_vecSize, const glm::vec4& a_vecColor);
        static void DrawTriangle(const glm::vec3& a_vecPosition, const glm::vec2& a_vecSize, const glm::vec4& a_vecColor);
        static void DrawCircle(const glm::vec3& a_vecPosition, const glm::vec2& a_vecSize, const glm::vec4& a_vecColor);

    };
}

#endif // !REMA_RENDERER2D_H
