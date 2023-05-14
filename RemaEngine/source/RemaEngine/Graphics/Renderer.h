/**
 * @file RemaEngine/Graphics/RenderCommand.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-03-21
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
#ifndef REMA_RENDERER_H
#define REMA_RENDERER_H

#include "EASTL/shared_ptr.h"

#include "RemaEngine/Graphics/RenderCommand.h"
#include "RemaEngine/Graphics/RendererAPI.h"

namespace RemaEngine
{
    /**
    * @class RemaEngine::Renderer
    * @brief RemaEngine virtual renderer class
    **/
    class Renderer
    {
    public:
        static void BeginScene(); 
        static void EndScene();
        static void Submit(const eastl::shared_ptr<VertexArray>& a_arrVertexArray);

        /**
        * @returns returns currently used graphics API
        * @return object of RemaEngine::RendererAPI::API class
        **/
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    };
}

#endif // !REMA_RENDERER_H
