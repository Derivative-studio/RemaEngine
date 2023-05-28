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
