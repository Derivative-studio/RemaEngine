#ifndef REMA_OPENGLINDEXBUFFER_H
#define REMA_OPENGLINDEXBUFFER_H

#include <RemaEngine/Graphics/VirtualIndexBuffer.h>

namespace RemaEngine
{
    class OpenGLIndexBuffer : public VirtualIndexBuffer
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
