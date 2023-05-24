/**
 * @file RemaEngine/Graphics/Shader.cpp
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-22
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
#include "RemaEngine/Graphics/Shader.h"
#include "RemaEngine/Graphics/Renderer.h"
#include "RemaEngine/Graphics/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace RemaEngine
{
    ref<Shader> Shader::Create(const eastl::string& a_sFilepath)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: REMA_CORE_ASSERT(false, "This renderer api is not supported for now"); return nullptr;
        case RendererAPI::API::OpenGL: return eastl::make_shared<OpenGLShader>(a_sFilepath);
        case RendererAPI::API::DirectX: REMA_CORE_ASSERT(false, "DirectX renderer API is not supported for now");
        }

        REMA_CORE_ASSERT(false, "Unknown renderer API");
        return nullptr;
    }

    ref<Shader> Shader::Create(const eastl::string& a_sName, const eastl::string& a_sVertexSrc, const eastl::string& a_sFragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: REMA_CORE_ASSERT(false, "This renderer api is not supported for now"); return nullptr;
        case RendererAPI::API::OpenGL: return eastl::make_shared<OpenGLShader>(a_sName, a_sVertexSrc, a_sFragmentSrc);
        case RendererAPI::API::DirectX: REMA_CORE_ASSERT(false, "DirectX renderer API is not supported for now");
        }

        REMA_CORE_ASSERT(false, "Unknown renderer API");
        return nullptr;
    }
}
