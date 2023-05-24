/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLRendererAPI.h
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
#ifndef REMA_OPENGLRENDERERAPI_H
#define REMA_OPENGLRENDERERAPI_H

#include "RemaEngine/Graphics/RendererAPI.h"

namespace RemaEngine
{
    /**
    * @class RemaEngine::OpenGLRendererAPI
    * @implements RemaEngine::RendererAPI
    * @brief OpenGL implementation class for RendererAPI
    * @see RemaEngine/Graphics/RendererAPI.h
    **/
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Init() override;
        virtual void SetViewport(uint32_t x, uint32_t y, uint32_t a_unWidth, uint32_t a_unHeight) override;
        /**
        * @brief OpenGL implementation of RemaEngine::RendererAPI::Clear method
        * @details to change clear color use **SetClearColor** method
        * @see RemaEngine/Graphics/RendererAPI.h
        **/
        virtual void Clear() override;
        /**
        * @brief OpenGL implementation of RemaEngine::RendererAPI::SetClearColor method
        * @see RemaEngine/Graphics/RendererAPI.h
        **/
        virtual void SetClearColor(const glm::vec4& a_arrColor) override;

        /**
        * @brief OpenGL implementation of RemaEngine::RendererAPI::DrawIndexed method
        * @see RemaEngine/Graphics/RendererAPI.h
        **/
        virtual void DrawIndexed(const ref<VertexArray>& a_arrVertexArray) override;

    };
}

#endif // !REMA_OPENGLRENDERERAPI_H
