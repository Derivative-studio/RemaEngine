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
