/**
 * @file RemaEngine/Graphics/Shader.h
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
#ifndef REMA_SHADER_H
#define REMA_SHADER_H

#include <glm/glm.hpp>

namespace RemaEngine
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetInt(const eastl::string& a_sName, const int a_nValue) = 0;
        virtual void SetFloat(const eastl::string& a_sName, const float a_fValue) = 0;
        virtual void SetFloat2(const eastl::string& a_sName, const glm::vec2& a_vecValue) = 0;
        virtual void SetFloat3(const eastl::string& a_sName, const glm::vec3& a_vecValue) = 0;
        virtual void SetFloat4(const eastl::string& a_sName, const glm::vec4& a_vecValue) = 0;
        virtual void SetMat3(const eastl::string& a_sName, const glm::mat3& a_mtxValue) = 0;
        virtual void SetMat4(const eastl::string& a_sName, const glm::mat4& a_mtxValue) = 0;

        virtual const eastl::string& GetName() const = 0;

        static ref<Shader> Create(const eastl::string& a_sFilepath);
        static ref<Shader> Create(const eastl::string& a_sName, const eastl::string& a_sVertexSrc, const eastl::string& a_sFragmentSrc);

    };
}

#endif // !REMA_SHADER_H
