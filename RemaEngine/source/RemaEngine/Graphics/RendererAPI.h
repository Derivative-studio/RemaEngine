/**
 * @file RemaEngine/Graphics/RendererAPI.h
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
#ifndef REMA_RENDERERAPI_H
#define REMA_RENDERERAPI_H

#include "glm/glm.hpp"
#include "EASTL/shared_ptr.h"

#include "RemaEngine/Graphics/VertexArray.h"

namespace RemaEngine
{
    /**
    * @class RemaEngine::RendererAPI
    * @brief RemaEngine renderer interface class
    **/
    class RendererAPI
    {
    public:
        /**
        * @class RemaEngine::RendererAPI::API
        * @brief The RemaEngine enum class with graphics
        * SDK for renderer
        **/
        enum class API
        {
            None = 0,
            OpenGL = 1,
            DirectX = 2
        };

    public:
        /**
        * @brief clears the screen with the default color
        * @details to change clear color use **SetClearColor** method
        **/
        virtual void Clear() = 0;
        /**
        * @brief sets default clear color for Clear method
        **/
        virtual void SetClearColor(const glm::vec4& a_arrColor) = 0;

        /**
        * @brief draw given vertex array in renderable window
        **/
        virtual void DrawIndexed(const eastl::shared_ptr<VertexArray>& a_arrVertexArray) = 0;

        /**
        * @brief gets the currently used graphics API
        * @returns currently used graphics API value
        * @return object of **RemaEngine::RendererAPI::API** class
        **/
        inline static API GetAPI() { return sm_stAPI; }

    private:
        static API sm_stAPI;

    };
}

#endif // !REMA_RENDERERAPI_H
