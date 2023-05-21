/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLShader.cpp
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
#include "remapch.h"
#include "RemaEngine/Graphics/OpenGL/OpenGLShader.h"

#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace RemaEngine
{
    OpenGLShader::OpenGLShader(const eastl::string& a_sVertexSrc, const eastl::string& a_sFragmentSrc)
    {
        // Create an empty vertex shader handle
        GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);

        // Send the vertex shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        const GLchar* source = a_sVertexSrc.c_str();
        glShaderSource(vertexShader, 1, &source, 0);

        // Compile the vertex shader
        glCompileShader(vertexShader);

        GLint isCompiled = 0;
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.

            REMA_ENGINE_ERROR("{0}", infoLog.data());
            REMA_CORE_ASSERT(false, "Vertex shader compilation failure");
            return;
        }

        // Create an empty fragment shader handle
        GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

        // Send the fragment shader source code to GL
        // Note that std::string's .c_str is NULL character terminated.
        source = a_sFragmentSrc.c_str();
        glShaderSource(fragmentShader, 1, &source, 0);

        // Compile the fragment shader
        glCompileShader(fragmentShader);

        glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
        if (isCompiled == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

            // We don't need the shader anymore.
            glDeleteShader(fragmentShader);
            // Either of them. Don't leak shaders.
            glDeleteShader(vertexShader);

            // Use the infoLog as you see fit.

            REMA_ENGINE_ERROR("{0}", infoLog.data());
            REMA_CORE_ASSERT(false, "Fragment shader compilation failure");
            return;
        }

        // Vertex and fragment shaders are successfully compiled.
        // Now time to link them together into a program.
        // Get a program object.
        m_nRendererID = glCreateProgram();
        GLuint program = m_nRendererID;

        // Attach our shaders to our program
        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        // Link our program
        glLinkProgram(program);

        // Note the different functions here: glGetProgram* instead of glGetShader*.
        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            // The maxLength includes the NULL character
            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            // We don't need the program anymore.
            glDeleteProgram(program);
            // Don't leak shaders either.
            glDeleteShader(vertexShader);
            glDeleteShader(fragmentShader);

            // Use the infoLog as you see fit.

            REMA_ENGINE_ERROR("{0}", infoLog.data());
            REMA_CORE_ASSERT(false, "Shader linkage failure");
            return;
        }

        // Always detach shaders after a successful link.
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_nRendererID);
    }

    void OpenGLShader::Bind() const
    {
        glUseProgram(m_nRendererID);
    }

    void OpenGLShader::Unbind() const
    {
        glUseProgram(0);
    }

    void OpenGLShader::UploadUniformInt(const eastl::string& a_sUniformName, int a_nValue)
    {
        GLint nLocation = glGetUniformLocation(m_nRendererID, a_sUniformName.c_str());
        glUniform1i(nLocation, a_nValue);
    }

    void OpenGLShader::UploadUniformFloat(const eastl::string& a_sUniformName, float a_fValue)
    {
        GLint nLocation = glGetUniformLocation(m_nRendererID, a_sUniformName.c_str());
        glUniform1f(nLocation, a_fValue);
    }

    void OpenGLShader::UploadUniformFloat2(const eastl::string& a_sUniformName, const glm::vec2& a_vecValues)
    {
        GLint nLocation = glGetUniformLocation(m_nRendererID, a_sUniformName.c_str());
        glUniform2f(nLocation, a_vecValues.x, a_vecValues.y);
    }

    void OpenGLShader::UploadUniformFloat3(const eastl::string& a_sUniformName, const glm::vec3& a_vecValues)
    {
        GLint nLocation = glGetUniformLocation(m_nRendererID, a_sUniformName.c_str());
        glUniform3f(nLocation, a_vecValues.x, a_vecValues.y, a_vecValues.z);
    }

    void OpenGLShader::UploadUniformFloat4(const eastl::string& a_sUniformName, const glm::vec4& a_vecValues)
    {
        GLint nLocation = glGetUniformLocation(m_nRendererID, a_sUniformName.c_str());
        glUniform4f(nLocation, a_vecValues.x, a_vecValues.y, a_vecValues.z, a_vecValues.w);
    }

    void OpenGLShader::UploadUniformMat3(const eastl::string& a_sUniformName, const glm::mat3& a_mtxMatrix)
    {
        GLint nLocation = glGetUniformLocation(m_nRendererID, a_sUniformName.c_str());
        glUniformMatrix3fv(nLocation, 1, GL_FALSE, glm::value_ptr(a_mtxMatrix));
    }

    void OpenGLShader::UploadUniformMat4(const eastl::string& a_sUniformName, const glm::mat4& a_mtxMatrix)
    {
        GLint nLocation = glGetUniformLocation(m_nRendererID, a_sUniformName.c_str());
        glUniformMatrix4fv(nLocation, 1, GL_FALSE, glm::value_ptr(a_mtxMatrix));
    }
}
