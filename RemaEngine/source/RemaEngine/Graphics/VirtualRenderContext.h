#ifndef REMA_RENDERCONTEXT_H
#define REMA_RENDERCONTEXT_H

namespace RemaEngine
{
    class VirtualRenderContext
    {
    private:


    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

    };
}

#endif // !REMA_RENDERCONTEXT_H

