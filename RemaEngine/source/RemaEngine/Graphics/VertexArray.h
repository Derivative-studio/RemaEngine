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

        virtual void AddVertexBuffer(const eastl::shared_ptr<VertexBuffer>& a_pVertexBuffer) = 0;
        virtual void SetIndexBuffer(const eastl::shared_ptr<IndexBuffer>& a_pIndexBuffer) = 0;

        virtual const eastl::vector<eastl::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const eastl::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

        static VertexArray* Create();

    };
}

#endif // !REMA_VERTEXARRAY_H
