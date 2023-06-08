/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLIndexBuffer.cpp
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
#include <remapch.h>
#include <RemaEngine/Graphics/OpenGL/OpenGLIndexBuffer.h>

#include <glad/glad.h>


namespace RemaEngine
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* a_unpIndices, uint32_t a_unCount)
        :m_unCount(a_unCount)
    {
        REMA_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_unRendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_unRendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_unCount * sizeof(uint32_t), a_unpIndices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        REMA_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_unRendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_unRendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
