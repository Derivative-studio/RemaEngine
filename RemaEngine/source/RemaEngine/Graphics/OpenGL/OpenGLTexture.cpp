/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLTexture.cpp
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
#include "RemaEngine/Graphics/OpenGL/OpenGLTexture.h"

#include <stb/graphics/stb_image.h>

namespace RemaEngine
{
    OpenGLTexture2D::OpenGLTexture2D(uint32_t a_unWidth, uint32_t a_unHeight)
        : m_unWidth(a_unWidth), m_unHeight(a_unHeight)
    {
        REMA_PROFILE_FUNCTION();

        m_eInternalFormat = GL_RGBA8, m_eDataFormat = GL_RGBA;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_unRendererID);
        glTextureStorage2D(m_unRendererID, 1, m_eInternalFormat, m_unWidth, m_unHeight);

        glTextureParameteri(m_unRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_unRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_unRendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_unRendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);
    }

    OpenGLTexture2D::OpenGLTexture2D(const eastl::string& a_sPath)
        : m_sPath(a_sPath)
    {
        REMA_PROFILE_FUNCTION();

        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(a_sPath.c_str(), &width, &height, &channels, 0);
        REMA_CORE_ASSERT(data, "Failed to load image");

        m_unWidth = static_cast<uint32_t>(width);
        m_unHeight = static_cast<uint32_t>(height);

        GLenum internalFormat = 0, dataFormat = 0;
        if (channels == 4)
        {
            internalFormat = GL_RGBA8;
            dataFormat = GL_RGBA;
        }
        else if (channels == 3)
        {
            internalFormat = GL_RGB8;
            dataFormat = GL_RGB;
        }

        m_eInternalFormat = internalFormat;
        m_eDataFormat = dataFormat;

        REMA_CORE_ASSERT(internalFormat & dataFormat, "Format not supported now");

        glCreateTextures(GL_TEXTURE_2D, 1, &m_unRendererID);
        glTextureStorage2D(m_unRendererID, 1, internalFormat, m_unWidth, m_unHeight);

        glTextureParameteri(m_unRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_unRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureParameteri(m_unRendererID, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_unRendererID, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_unRendererID, 0, 0, 0, m_unWidth, m_unHeight, dataFormat, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        REMA_PROFILE_FUNCTION();

        glDeleteTextures(1, &m_unRendererID);
    }

    void OpenGLTexture2D::SetData(void* a_Data, uint32_t a_unSize)
    {
        REMA_PROFILE_FUNCTION();

        uint32_t bpp = m_eDataFormat == GL_RGBA ? 4 : 3;
        REMA_CORE_ASSERT(a_unSize == m_unWidth * m_unHeight * bpp, "Data mus be entire texture");
        glTextureSubImage2D(
            m_unRendererID, 0, 0, 0, 
            m_unWidth, m_unHeight,
            m_eDataFormat, GL_UNSIGNED_BYTE,
            a_Data);
    }

    void OpenGLTexture2D::Bind(uint32_t a_unSlot) const
    {
        REMA_PROFILE_FUNCTION();

        glBindTextureUnit(a_unSlot, m_unRendererID);
    }

    void OpenGLTexture2D::Unbind(uint32_t a_unSlot) const
    {
        REMA_PROFILE_FUNCTION();

        glBindTextureUnit(a_unSlot, 0);
    }
}
