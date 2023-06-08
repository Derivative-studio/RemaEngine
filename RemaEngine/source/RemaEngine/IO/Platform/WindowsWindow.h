/**
 * @file RemaEngine/Utils/Platform/WindowsWindow.h
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
#ifndef REMA_WINDOWSWINDOW_H
#define REMA_WINDOWSWINDOW_H

#include <RemaEngine/IO/Window.h>
#include <RemaEngine/Graphics/RenderContext.h>

#include <GLFW/glfw3.h>

namespace RemaEngine
{
    class WindowsWindow : public Window
    {
        struct WindowData
        {
            std::string m_sTitle;

            uint32_t m_u32Width;
            uint32_t m_u32Height;

            bool VSync;
            fnEventCallback m_fnEventCallback;
        };

        GLFWwindow* m_stGLFWWindow;
        RenderContext* m_stRenderContext;

        WindowData m_stWndwData;

    private:
        virtual void Init(const WindowProps& a_stWndwProps);
        virtual void Shutdown();

    public:
        WindowsWindow(const WindowProps& a_stWndwProps);
        virtual ~WindowsWindow();

        void OnUpdate() override;
        void SetEventCallback(const fnEventCallback& a_stCallback) override { m_stWndwData.m_fnEventCallback = a_stCallback; }
        void SetVSync(bool a_bEnabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return m_stGLFWWindow; }

        uint32_t GetWidth() const override { return m_stWndwData.m_u32Width; }
        uint32_t GetHeight() const override { return m_stWndwData.m_u32Height; }
        std::string GetWindowTitle() const override { return m_stWndwData.m_sTitle; }

    };
}

#endif // !REMA_WINDOWSWINDOW_H

