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
