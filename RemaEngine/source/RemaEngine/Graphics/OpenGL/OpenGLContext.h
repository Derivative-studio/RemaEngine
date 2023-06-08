/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLContext.h
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
#ifndef REMA_OPENGLCONTEXT_H
#define REMA_OPENGLCONTEXT_H

#include <RemaEngine/Graphics/RenderContext.h>

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

