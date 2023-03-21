#include <remapch.h>
#include <RemaEngine/Graphics/OpenGL/OpenGLContext.h>

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace RemaEngine
{
    OpenGLContext::OpenGLContext(GLFWwindow* a_stHWindow)
        : m_stHWindow(a_stHWindow)
    {
        REMA_CORE_ASSERT(a_stHWindow, "Window handle is NULL!");
    }

    void OpenGLContext::Init()
    {
        glfwMakeContextCurrent(m_stHWindow);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        REMA_CORE_ASSERT(status, "Failed to initialize GLAD");

        REMA_ENGINE_INFO("OpenGL version: {0}", glGetString(GL_VERSION));
        REMA_ENGINE_INFO("OpenGL render device: {0}", glGetString(GL_RENDERER));
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(m_stHWindow);
    }
}