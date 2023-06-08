/**
 * @file RemaEngine/Graphics/VertexBuffer.cpp
 * @author Nikita Kozlov (nyarstot@yandex.ru)
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
#include "RemaEngine/Graphics/VertexArray.h"
#include "RemaEngine/Graphics/Renderer.h"
#include "RemaEngine/Graphics/OpenGL/OpenGLVertexArray.h"

namespace RemaEngine
{
    ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: REMA_CORE_ASSERT(false, "This renderer api is not supported for now"); return nullptr;
            case RendererAPI::API::OpenGL: return eastl::make_shared<OpenGLVertexArray>();
            case RendererAPI::API::DirectX: REMA_CORE_ASSERT(false, "DirectX renderer API is not supported for now");
        }

        REMA_CORE_ASSERT(false, "Unknown renderer API");
        return nullptr;
    }

}