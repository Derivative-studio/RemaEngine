#ifndef REMA_VIRTUALVERTEXBUFFER_H
#define REMA_VIRTUALVERTEXBUFFER_H

namespace RemaEngine
{
    class VirtualVertexBuffer
    {
    private:


    public:
        virtual ~VirtualVertexBuffer() {}

        static VirtualVertexBuffer* Create(float* a_fpVertices, uint32_t a_nSize);

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
};

#endif // !REMA_VIRTUALVERTEXBUFFER_H
