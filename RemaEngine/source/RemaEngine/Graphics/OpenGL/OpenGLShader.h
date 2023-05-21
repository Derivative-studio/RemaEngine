/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLShader.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-21
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
#ifndef REMA_OPENGLSHADER_H
#define REMA_OPENGLSHADER_H

#include "RemaEngine/Graphics/Shader.h"

#include <glm/glm.hpp>

namespace RemaEngine
{
    class OpenGLShader : public Shader
    {
    private:
        uint32_t m_nRendererID;

    public:
        OpenGLShader(const eastl::string& a_sVertexSrc, const eastl::string& a_sFragmentSrc);
        virtual ~OpenGLShader();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        void UploadUniformInt(const eastl::string& a_sUniformName, int a_nValue);

        void UploadUniformFloat(const eastl::string& a_sUniformName, float a_fValue);
        void UploadUniformFloat2(const eastl::string& a_sUniformName, const glm::vec2& a_vecValues);
        void UploadUniformFloat3(const eastl::string& a_sUniformName, const glm::vec3& a_vecValues);
        void UploadUniformFloat4(const eastl::string& a_sUniformName, const glm::vec4& a_vecValues);

        void UploadUniformMat3(const eastl::string& a_sUniformName, const glm::mat3& a_mtxMatrix);
        void UploadUniformMat4(const eastl::string& a_sUniformName, const glm::mat4& a_mtxMatrix);

    };
}

#endif // !REMA_OPENGLSHADER_H
