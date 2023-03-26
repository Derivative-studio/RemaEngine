#ifndef REMA_INDEXBUFFER_H
#define REMA_INDEXBUFFER_H

namespace RemaEngine
{
    class IndexBuffer
    {
    private:


    public:
        virtual ~IndexBuffer() {}

        static IndexBuffer* Create(uint32_t* a_npIndices, uint32_t a_nSize);

        virtual uint32_t GetCount() const = 0;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
    };
};

#endif // !REMA_INDEXBUFFER_H
