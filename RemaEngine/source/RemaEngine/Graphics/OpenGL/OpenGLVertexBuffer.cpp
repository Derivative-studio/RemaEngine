/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLVertexBuffer.cpp
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
#include <RemaEngine/Graphics/OpenGL/OpenGLVertexBuffer.h>

#include <glad/glad.h>


namespace RemaEngine
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* a_fpVertices, uint32_t a_nSize)
    {
        REMA_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_unRendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_unRendererID);
        glBufferData(GL_ARRAY_BUFFER, a_nSize, a_fpVertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        REMA_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_unRendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_unRendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
