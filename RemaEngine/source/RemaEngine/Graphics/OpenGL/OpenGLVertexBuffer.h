/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLVertexBuffer.h
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
#ifndef REMA_OPENGLVERTEXBUFFER_H
#define REMA_OPENGLVERTEXBUFFER_H

#include <RemaEngine/Graphics/VertexBuffer.h>

namespace RemaEngine
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    private:
        uint32_t m_unRendererID;
        BufferLayout m_stBufferLayout;

    public:
        OpenGLVertexBuffer(float* a_fpVertices, uint32_t a_nSize);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void SetLayout(const BufferLayout& a_stLayout) override { m_stBufferLayout = a_stLayout; }
        virtual const BufferLayout& GetLayout() const override { return m_stBufferLayout; }

    };
}

#endif // !REMA_OPENGLVERTEXBUFFER_H
