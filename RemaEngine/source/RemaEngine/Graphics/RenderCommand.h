/**
 * @file RemaEngine/Graphics/RenderCommand.h
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
#ifndef REMA_RENDERCOMMAND_H
#define REMA_RENDERCOMMAND_H

#include "RemaEngine/Graphics/RendererAPI.h"

namespace RemaEngine
{
    /**
    * @class RemaEngine::RenderCommand
    **/
    class RenderCommand
    {
    private:
        static RendererAPI* sm_RendererAPI;

    public:
        inline static void Init() 
        {
            REMA_PROFILE_FUNCTION();

            sm_RendererAPI->Init();
        }

        inline static void SetViewport(uint32_t x, uint32_t y, uint32_t a_unWidth, uint32_t a_unHeight) {
            sm_RendererAPI->SetViewport(x, y, a_unWidth, a_unHeight);
        }

        /**
        * @brief clears the screen with the default color
        * @details dispatches RemaEngine::RendererAPI::Clear method;
        * to change clear color use **SetClearColor** method
        * @see RemaEngine/Graphics/RendererAPI.h
        **/
        inline static void Clear() {
            sm_RendererAPI->Clear();
        }
        /**
        * @brief sets default clear color for Clear method
        * @details dispatches RemaEngine::RendererAPI::SetClearColor method
        * @see RemaEngine/Graphics/RendererAPI.h
        **/
        inline static void SetClearColor(const glm::vec4& a_arrColor) {
            sm_RendererAPI->SetClearColor(a_arrColor);
        }

        /**
        * @brief draw given vertex array in renderable window
        * @details dispatches RemaEngine::RendererAPI::DrawIndexed method
        * @see RemaEngine/Graphics/RendererAPI.h
        **/
        inline static void DrawIndexed(const ref<VertexArray>& a_arrVertexArray) {
            sm_RendererAPI->DrawIndexed(a_arrVertexArray);
        }

    };
}

#endif // !REMA_RENDERCOMMAND_H
