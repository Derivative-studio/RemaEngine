/**
 * @file RemaEngine/Graphics/ShaderLibrary.cpp
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
#include "remapch.h"
#include "RemaEngine/Graphics/ShaderLibrary.h"

namespace RemaEngine
{
    void ShaderLibrary::Add(const ref<Shader>& a_stShader)
    {
        auto& name = a_stShader->GetName();
        Add(name, a_stShader);
    }

    void ShaderLibrary::Add(const eastl::string& a_sName, const ref<Shader>& a_stShader)
    {
        REMA_CORE_ASSERT(!Exists(a_sName), "Shader already exists.");
        m_stShaders[a_sName] = a_stShader;
    }

    ref<Shader> ShaderLibrary::Load(const eastl::string& a_sFilepath)
    {
        auto shader = Shader::Create(a_sFilepath);
        Add(shader);
        return shader;
    }

    ref<Shader> ShaderLibrary::Load(const eastl::string& a_sName, const eastl::string& a_sFilepath)
    {
        auto shader = Shader::Create(a_sFilepath);
        Add(a_sName, shader);
        return shader;
    }

    ref<Shader> ShaderLibrary::Get(const eastl::string& a_sName)
    {
        REMA_CORE_ASSERT(Exists(a_sName), "Shader not found.");
        return m_stShaders[a_sName];
    }

    bool ShaderLibrary::Exists(const eastl::string& a_sName) const
    {
        return m_stShaders.find(a_sName) != m_stShaders.end();
    }
}
