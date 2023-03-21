#ifndef REMA_OPENGLVERTEXBUFFER_H
#define REMA_OPENGLVERTEXBUFFER_H

#include <RemaEngine/Graphics/VirtualVertexBuffer.h>

namespace RemaEngine
{
    class OpenGLVertexBuffer : public VirtualVertexBuffer
    {
    private:
        uint32_t m_unRendererID;

    public:
        OpenGLVertexBuffer(float* a_fpVertices, uint32_t a_nSize);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const;
        virtual void Unbind() const;

    };
}

#endif // !REMA_OPENGLVERTEXBUFFER_H
