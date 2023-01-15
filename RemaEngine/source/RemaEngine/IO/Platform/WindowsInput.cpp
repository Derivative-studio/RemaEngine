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
