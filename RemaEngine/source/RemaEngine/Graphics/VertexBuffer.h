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
