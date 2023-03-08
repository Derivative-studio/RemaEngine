#ifndef REMA_OPENGLCONTEXT_H
#define REMA_OPENGLCONTEXT_H

#include <RemaEngine/Renderer/RenderContext.h>

struct GLFWwindow;

namespace RemaEngine
{
    class OpenGLContext : public RenderContext
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

