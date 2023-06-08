/**
 * @file RemaEngine/Graphics/VertexArray.h
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
#ifndef REMA_VERTEXARRAY_H
#define REMA_VERTEXARRAY_H

#include "RemaEngine/Graphics/IndexBuffer.h"
#include "RemaEngine/Graphics/BufferLayout.h"
#include "RemaEngine/Graphics/VertexBuffer.h"

#include "EASTL/shared_ptr.h"
#include "EASTL/vector.h"

namespace RemaEngine
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual void AddVertexBuffer(const ref<VertexBuffer>& a_pVertexBuffer) = 0;
        virtual void SetIndexBuffer(const ref<IndexBuffer>& a_pIndexBuffer) = 0;

        virtual const eastl::vector<ref<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const ref<IndexBuffer>& GetIndexBuffer() const = 0;

        static ref<VertexArray> Create();

    };
}

#endif // !REMA_VERTEXARRAY_H
