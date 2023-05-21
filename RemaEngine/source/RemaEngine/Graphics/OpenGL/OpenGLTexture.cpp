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
#include <glad/glad.h>

namespace RemaEngine
{
    OpenGLTexture2D::OpenGLTexture2D(const eastl::string& a_sPath)
        : m_sPath(a_sPath)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(1);
        stbi_uc* data = stbi_load(a_sPath.c_str(), &width, &height, &channels, 0);
        REMA_CORE_ASSERT(data, "Failed to load image");

        m_unWidth = static_cast<uint32_t>(width);
        m_unHeight = static_cast<uint32_t>(height);

        glCreateTextures(GL_TEXTURE_2D, 1, &m_unRendererID);
        glTextureStorage2D(m_unRendererID, 1, GL_SRGB8, m_unWidth, m_unHeight);

        glTextureParameteri(m_unRendererID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_unRendererID, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

        glTextureSubImage2D(m_unRendererID, 0, 0, 0, m_unWidth, m_unHeight, GL_RGB, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_unRendererID);
    }

    void OpenGLTexture2D::Bind(uint32_t m_unSlot) const
    {
        glBindTextureUnit(m_unSlot, m_unRendererID);
    }
}