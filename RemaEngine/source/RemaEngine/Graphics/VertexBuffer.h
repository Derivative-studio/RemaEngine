/**
 * @file RemaEngine/Graphics/VertexBuffer.h
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
#ifndef REMA_VERTEXBUFFER_H
#define REMA_VERTEXBUFFER_H

#include <RemaEngine/Graphics/BufferLayout.h>

namespace RemaEngine
{
    class VertexBuffer
    {
    private:


    public:
        virtual ~VertexBuffer() {}

        static VertexBuffer* Create(float* a_fpVertices, uint32_t a_nSize);

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void SetLayout(const BufferLayout& a_stLayout) = 0;
        virtual const BufferLayout& GetLayout() const = 0;
    };
};

#endif // !REMA_VERTEXBUFFER_H
