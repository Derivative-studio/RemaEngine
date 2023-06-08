/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLIndexBuffer.h
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
#ifndef REMA_OPENGLINDEXBUFFER_H
#define REMA_OPENGLINDEXBUFFER_H

#include <RemaEngine/Graphics/IndexBuffer.h>

namespace RemaEngine
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    private:
        uint32_t m_unRendererID;
        uint32_t m_unCount;

    public:
        OpenGLIndexBuffer(uint32_t* a_unpIndices, uint32_t a_unCount);
        virtual ~OpenGLIndexBuffer();

        virtual uint32_t GetCount() const { return m_unCount; }

        virtual void Bind() const;
        virtual void Unbind() const;

    };
}

#endif // !REMA_OPENGLINDEXBUFFER_H
