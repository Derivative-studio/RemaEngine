/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLRendererAPI.cpp
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-14
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
#include "remapch.h"
#include "RemaEngine/Graphics/OpenGL/OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace RemaEngine
{
    void RemaEngine::OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& a_arrColor)
    {
        glClearColor(a_arrColor.r, a_arrColor.g, a_arrColor.b, a_arrColor.a);
    }

    void OpenGLRendererAPI::DrawIndexed(const ref<VertexArray>& a_arrVertexArray)
    {
        glDrawElements(GL_TRIANGLES, a_arrVertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

}
