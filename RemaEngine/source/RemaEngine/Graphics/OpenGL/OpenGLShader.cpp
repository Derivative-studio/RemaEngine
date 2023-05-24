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

#include <fstream>
#include <glad/glad.h>
#include <glm/gtc/type_ptr.hpp>

namespace RemaEngine
{
    static GLenum ShaderTypeFromString(const eastl::string& a_sType)
    {
        if (a_sType == "vertex")
            return GL_VERTEX_SHADER;
        if (a_sType == "fragment" || a_sType == "pixel" || a_sType == "frag")
            return GL_FRAGMENT_SHADER;

        REMA_CORE_ASSERT(false, "Unknown shader type.");
        return 0;
    }

    OpenGLShader::OpenGLShader(const eastl::string& a_sFilepath)
    {
        eastl::string shaderSource = ReadFile(a_sFilepath);
        auto shaderSources = PreProcess(shaderSource);
        Compile(shaderSources);

        // Extract name from filepath
        auto lastSlash = a_sFilepath.find_last_of("/\\");
        lastSlash = lastSlash == eastl::string::npos ? 0 : lastSlash + 1;
        auto lastDot = a_sFilepath.rfind('.');
        auto count = lastDot == eastl::string::npos ? a_sFilepath.size() - lastSlash : lastDot - lastSlash;
        m_sName = a_sFilepath.substr(lastSlash, count);
    }

    OpenGLShader::OpenGLShader(const eastl::string& a_sName, const eastl::string& a_sVertexSrc, const eastl::string& a_sFragmentSrc)
        : m_sName(a_sName)
    {
        eastl::unordered_map<GLenum, eastl::string> sources;
        sources[GL_VERTEX_SHADER] = a_sVertexSrc;
        sources[GL_FRAGMENT_SHADER] = a_sFragmentSrc;
        Compile(sources);
    }

    OpenGLShader::~OpenGLShader()
    {
        glDeleteProgram(m_nRendererID);
    }

    void OpenGLShader::Compile(const eastl::unordered_map<GLenum, eastl::string>& shaderSources)
    {
        GLuint program = glCreateProgram();

        REMA_CORE_ASSERT(shaderSources.size() <= 2, "Only support 2 shaders");
        eastl::array<GLenum, 2> glShaderIDs;

        int glShaderIDsIndex = 0;
        for (auto& kv : shaderSources) {
            GLenum type = kv.first;
            const eastl::string& source = kv.second;

            GLuint shader = glCreateShader(type);

            const GLchar* sourceCStr = source.c_str();
            glShaderSource(shader, 1, &sourceCStr, 0);

            glCompileShader(shader);

            GLint isCompiled = 0;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
            if (isCompiled == GL_FALSE)
            {
                GLint maxLength = 0;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

                std::vector<GLchar> infoLog(maxLength);
                glGetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

                glDeleteShader(shader);

                REMA_ENGINE_ERROR("{0}", infoLog.data());
                REMA_CORE_ASSERT(false, "Shader compilation failure");
                break;
            }

            glAttachShader(program, shader);
            glShaderIDs[glShaderIDsIndex++] = shader;
        }

        glLinkProgram(program);

        GLint isLinked = 0;
        glGetProgramiv(program, GL_LINK_STATUS, (int*)&isLinked);
        if (isLinked == GL_FALSE)
        {
            GLint maxLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

            std::vector<GLchar> infoLog(maxLength);
            glGetProgramInfoLog(program, maxLength, &maxLength, &infoLog[0]);

            glDeleteProgram(program);

            for (auto id : glShaderIDs) {
                glDeleteShader(id);
            }

            REMA_ENGINE_ERROR("{0}", infoLog.data());
            REMA_CORE_ASSERT(false, "Shader linkage failure");
            return;
        }

        for (auto id : glShaderIDs) {
            glDetachShader(program, id);
        }

        m_nRendererID = program;
    }

    eastl::unordered_map<GLenum, eastl::string> OpenGLShader::PreProcess(const eastl::string& a_sSource)
    {
        eastl::unordered_map<GLenum, eastl::string> shaderSources;

        const char* typeToken = "#type";
        size_t typeTokenLength = strlen(typeToken);
        size_t pos = a_sSource.find(typeToken, 0);

        while (pos != eastl::string::npos)
        {
            size_t eol = a_sSource.find_first_of("\r\n", pos);
            REMA_CORE_ASSERT(eol != eastl::string::npos, "Syntax error.");
            size_t begin = pos + typeTokenLength + 1;
            eastl::string type = a_sSource.substr(begin, eol - begin);
            REMA_CORE_ASSERT(ShaderTypeFromString(type), "Invalid shader type.");

            size_t nextLinePos = a_sSource.find_first_not_of("\r\n", eol);
            pos = a_sSource.find(typeToken, nextLinePos);
            shaderSources[ShaderTypeFromString(type)] = a_sSource.substr(nextLinePos, 
                pos - (nextLinePos == eastl::string::npos ? a_sSource.size() - 1 : nextLinePos));
        }

        return shaderSources;
    }

    eastl::string OpenGLShader::ReadFile(const eastl::string& a_sFilepath)
    {
        //TODO: make abstract filesystem

        eastl::string result;
        std::ifstream in(a_sFilepath.c_str(), std::ios::in | std::ios::binary);
        if (in)
        {
            in.seekg(0, std::ios::end);
            result.resize(in.tellg());
            in.seekg(0, std::ios::beg);
            in.read(&result[0], result.size());
            in.close();
        }
        else
        {
            REMA_CORE_ASSERT("Could not open file '{0}'", a_sFilename.c_str());
        }

        return result;
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
