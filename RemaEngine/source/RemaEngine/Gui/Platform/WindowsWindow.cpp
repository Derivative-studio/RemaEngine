#include "remapch.h"
#include "WindowsWindow.h"

namespace RemaEngine
{
    static bool s_GLFWInitialized = false;

    Window* Window::Create(const WindowProps& a_stWndwProps)
    {
        return new WindowsWindow(a_stWndwProps);
    }

    WindowsWindow::WindowsWindow(const WindowProps& a_stWndwProps)
    {
        Init(a_stWndwProps);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& a_stWndwProps)
    {
        m_stWndwData.m_sTitle = a_stWndwProps.m_sTitle;
        m_stWndwData.m_u32Width = a_stWndwProps.m_u32Width;
        m_stWndwData.m_u32Height = a_stWndwProps.m_u32Height;

        REMA_LOG_CORE_INFO("Creating window {0} ({1}x{2})",
            m_stWndwData.m_sTitle, m_stWndwData.m_u32Width, m_stWndwData.m_u32Height);

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            REMA_CORE_ASSERT(success, "Could not intialize GLFW");
            s_GLFWInitialized = true;
        }

        m_stGLFWWindow = glfwCreateWindow(
            (int)m_stWndwData.m_u32Width,
            (int)m_stWndwData.m_u32Height,
            m_stWndwData.m_sTitle.c_str(),
            nullptr, nullptr
        );

        glfwMakeContextCurrent(m_stGLFWWindow);
        glfwSetWindowUserPointer(m_stGLFWWindow, &m_stWndwData);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_stGLFWWindow);
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        glfwSwapBuffers(m_stGLFWWindow);
    }

    void WindowsWindow::SetVSync(bool a_bEnabled)
    {
        if (a_bEnabled)
        {
            glfwSwapInterval(1);
        }
        else
        {
            glfwSwapInterval(0);
        }

        m_stWndwData.VSync = a_bEnabled;
    }

    bool WindowsWindow::IsVSync() const
    {
        return m_stWndwData.VSync;
    }
}