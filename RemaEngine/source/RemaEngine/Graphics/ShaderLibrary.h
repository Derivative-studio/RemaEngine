/**
 * @file RemaEngine/Graphics/ShaderLibrary.h
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
#ifndef REMA_SHADERLIBRARY_H
#define REMA_SHADERLIBRARY_H

#include "RemaEngine/Graphics/Shader.h"

namespace RemaEngine
{
    class ShaderLibrary
    {
    private:
        eastl::unordered_map<eastl::string, ref<Shader>> m_stShaders;

    public:
        void Add(const ref<Shader>& a_stShader);
        void Add(const eastl::string& a_sName, const ref<Shader>& a_stShader);
        ref<Shader> Load(const eastl::string& a_sFilepath);
        ref<Shader> Load(const eastl::string& a_sName, const eastl::string& a_sFilepath);

        ref<Shader> Get(const eastl::string& a_sName);

        bool Exists(const eastl::string& a_sName) const;
    };
}

#endif // !REMA_SHADERLIBRARY_H
