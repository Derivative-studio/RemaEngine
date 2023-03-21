#ifndef REMA_OPENGLCONTEXT_H
#define REMA_OPENGLCONTEXT_H

#include <RemaEngine/Graphics/VirtualRenderContext.h>

struct GLFWwindow;

namespace RemaEngine
{
    class OpenGLContext : public VirtualRenderContext
    {
    private:
        GLFWwindow* m_stHWindow;

    public:
        OpenGLContext(GLFWwindow* a_stHWindow);

        virtual void Init() override;
        virtual void SwapBuffers() override;

    };
}

#endif // !REMA_OPENGLCONTEXT_H

