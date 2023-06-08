/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLContext.cpp
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
        REMA_PROFILE_FUNCTION();

        glfwMakeContextCurrent(m_stHWindow);
        int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
        REMA_CORE_ASSERT(status, "Failed to initialize GLAD");

        REMA_ENGINE_INFO("OpenGL version: {0}", glGetString(GL_VERSION));
        REMA_ENGINE_INFO("OpenGL render device: {0}", glGetString(GL_RENDERER));

    #ifdef REMA_ENABLE_ASSERT
        int glVersionMajor;
        int glVersionMinor;

        glGetIntegerv(GL_MAJOR_VERSION, &glVersionMajor);
        glGetIntegerv(GL_MINOR_VERSION, &glVersionMinor);

        REMA_CORE_ASSERT(glVersionMajor > 4 || (glVersionMajor == 4 && glVersionMinor >= 5), "RemaEngine requires at least OpenGL version of 4.5!");

    #endif // REMA_ENABLE_ASSERT

    }

    void OpenGLContext::SwapBuffers()
    {
        REMA_PROFILE_FUNCTION();

        glfwSwapBuffers(m_stHWindow);
    }
}
