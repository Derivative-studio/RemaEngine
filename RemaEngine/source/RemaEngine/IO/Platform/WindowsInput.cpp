/**
 * @file RemaEngine/Utils/Platform/WindowsInput.cpp
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

#include <RemaEngine/Engine/Engine.h>
#include <RemaEngine/IO/Platform/WindowsInput.h>

#include <GLFW/glfw3.h>

namespace RemaEngine
{
    Input* Input::s_Instance = new WindowsInput();

    bool WindowsInput::IsKeyPressedImpl(int a_nKeyCode)
    {
        auto window = static_cast<GLFWwindow*>(Engine::GetInstance().GetWindow().GetNativeWindow());
        auto state = glfwGetKey(window, a_nKeyCode);
        return state == GLFW_PRESS || state == GLFW_REPEAT;
    }

    bool WindowsInput::IsMouseButtonPressedImpl(int a_nMouseButton)
    {
        auto window = static_cast<GLFWwindow*>(Engine::GetInstance().GetWindow().GetNativeWindow());
        auto state = glfwGetMouseButton(window, a_nMouseButton);
        return state == GLFW_PRESS;
    }

    std::pair<float, float> WindowsInput::GetMousePositionImpl()
    {
        auto window = static_cast<GLFWwindow*>(Engine::GetInstance().GetWindow().GetNativeWindow());

        double xpose = 0;
        double ypose = 0;
        glfwGetCursorPos(window, &xpose, &ypose);

        return { static_cast<float>(xpose), static_cast<float>(ypose) };
    }

    float WindowsInput::GetMouseXImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return x;
    }

    float WindowsInput::GetMouseYImpl()
    {
        auto [x, y] = GetMousePositionImpl();
        return y;
    }

}
