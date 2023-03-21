#ifndef REMA_VIRTUALINDEXBUFFER_H
#define REMA_VIRTUALINDEXBUFFER_H

namespace RemaEngine
{
    class VirtualIndexBuffer
    {
    private:


    public:
        virtual ~VirtualIndexBuffer() {}

        static VirtualIndexBuffer* Create(uint32_t* a_npIndices, uint32_t a_nSize);

        virtual uint32_t GetCount() const = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
};

#endif // !REMA_VIRTUALINDEXBUFFER_H
