/**
 * @file RemaEngine/Utils/Platform/WindowsWindow.cpp
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @copyright Copyright (c) 2023
 *
 * This file is part of RemaEngine.
 *
 * RemaEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RemaEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 **/
#include <remapch.h>

#include <RemaEngine/Event/MouseEvent.h>
#include <RemaEngine/Event/KeyboardEvent.h>
#include <RemaEngine/Event/ApplicationEvent.h>
#include <RemaEngine/IO/Platform/WindowsWindow.h>
#include <RemaEngine/Graphics/OpenGL/OpenGLContext.h>

namespace RemaEngine
{
    static bool s_GLFWInitialized = false;

    static void GLFWErrorCallback(int a_nError, const char* a_pcDescription)
    {
        REMA_ENGINE_ERROR("GLFW Error ({0}): {1}", a_nError, a_pcDescription);
    }

    Window* Window::Create(const WindowProps& a_stWndwProps)
    {
        return new WindowsWindow(a_stWndwProps);
    }

    WindowsWindow::WindowsWindow(const WindowProps& a_stWndwProps)
    {
        REMA_PROFILE_FUNCTION();

        Init(a_stWndwProps);
    }

    WindowsWindow::~WindowsWindow()
    {
        REMA_PROFILE_FUNCTION();

        Shutdown();
    }

    void WindowsWindow::Init(const WindowProps& a_stWndwProps)
    {
        REMA_PROFILE_FUNCTION();

        m_stWndwData.m_sTitle = a_stWndwProps.m_sTitle;
        m_stWndwData.m_u32Width = a_stWndwProps.m_u32Width;
        m_stWndwData.m_u32Height = a_stWndwProps.m_u32Height;

        if (!s_GLFWInitialized)
        {
            int success = glfwInit();
            REMA_CORE_ASSERT(success, "Could not intialize GLFW");
            glfwSetErrorCallback(GLFWErrorCallback);
            s_GLFWInitialized = true;
        }

        {
            REMA_SET_PROFILE_SCOPE("glfwCreateWindow");

            m_stGLFWWindow = glfwCreateWindow(
                (int)m_stWndwData.m_u32Width,
                (int)m_stWndwData.m_u32Height,
                m_stWndwData.m_sTitle.c_str(),
                nullptr, nullptr
            );
        }

        m_stRenderContext = new OpenGLContext(m_stGLFWWindow);
        m_stRenderContext->Init();

        glfwSetWindowUserPointer(m_stGLFWWindow, &m_stWndwData);
        SetVSync(true);

        // Set GLFW callbacks

        glfwSetWindowSizeCallback(m_stGLFWWindow, [](GLFWwindow* window, int width, int height)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                data.m_u32Width = width;
                data.m_u32Height = height;

                WindowResizedEvent resizeEvent(width, height);
                data.m_fnEventCallback(resizeEvent);
            });

        glfwSetWindowCloseCallback(m_stGLFWWindow, [](GLFWwindow* window)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                WindowClosedEvent closeEvent;
                data.m_fnEventCallback(closeEvent);
            });

        glfwSetKeyCallback(m_stGLFWWindow, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS:
                {
                    KeyPressedEvent event(key, 0);
                    data.m_fnEventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent event(key);
                    data.m_fnEventCallback(event);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent event(key, true);
                    data.m_fnEventCallback(event);
                    break;
                }
                }
            });

        glfwSetCharCallback(m_stGLFWWindow, [](GLFWwindow* window, unsigned int keycode)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                KeyTypedEvent event(keycode);
                data.m_fnEventCallback(event);
            });

        glfwSetMouseButtonCallback (m_stGLFWWindow, [](GLFWwindow* window, int button, int action, int mods)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

                switch (action)
                {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent event(button);
                    data.m_fnEventCallback(event);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent event(button);
                    data.m_fnEventCallback(event);
                    break;
                }
                }
            });

        glfwSetScrollCallback(m_stGLFWWindow, [](GLFWwindow* window, double xOffset, double yOffset)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
                data.m_fnEventCallback(event);
            });

        glfwSetCursorPosCallback(m_stGLFWWindow, [](GLFWwindow* window, double xPos, double yPos)
            {
                WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
                MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
                data.m_fnEventCallback(event);
            });

    }

    void WindowsWindow::Shutdown()
    {
        REMA_PROFILE_FUNCTION();

        glfwDestroyWindow(m_stGLFWWindow);
    }

    void WindowsWindow::OnUpdate()
    {
        REMA_PROFILE_FUNCTION();

        glfwPollEvents();
        m_stRenderContext->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool a_bEnabled)
    {
        REMA_PROFILE_FUNCTION();

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