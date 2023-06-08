/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLVertexArray.h
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
#ifndef REMA_OPENGLVERTEXARRAY_H
#define REMA_OPENGLVERTEXARRAY_H

#include "RemaEngine/Graphics/VertexArray.h"
#include "RemaEngine/Graphics/VertexBuffer.h"
#include "RemaEngine/Graphics/IndexBuffer.h"

#include "EASTL/vector.h"
#include "EASTL/shared_ptr.h"

namespace RemaEngine
{
    class OpenGLVertexArray : public VertexArray
    {
    private:
        eastl::vector<eastl::shared_ptr<VertexBuffer>> m_arrVertexBuffers;
        eastl::shared_ptr<IndexBuffer> m_pIndexBuffer;
        uint32_t m_unRendererID;

    public:
        OpenGLVertexArray();
        virtual ~OpenGLVertexArray();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual void AddVertexBuffer(const eastl::shared_ptr<VertexBuffer>& a_pVertexBuffer) override;
        virtual void SetIndexBuffer(const eastl::shared_ptr<IndexBuffer>& a_pIndexBuffer) override;

        virtual const eastl::vector<eastl::shared_ptr<VertexBuffer>>& GetVertexBuffers() const { return m_arrVertexBuffers; }
        virtual const eastl::shared_ptr<IndexBuffer>& GetIndexBuffer() const { return m_pIndexBuffer; }

    };
}

#endif // !REMA_OPENGLVERTEXARRAY_H
