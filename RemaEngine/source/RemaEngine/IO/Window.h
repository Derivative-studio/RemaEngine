/**
 * @file RemaEngine/IO/Window.h
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
#ifndef REMA_WINDOW_H
#define REMA_WINDOW_H

#include <remapch.h>
#include <RemaEngine/Engine/Core.h>
#include <RemaEngine/Event/Event.h>

namespace RemaEngine
{
    struct WindowProps
    {
        std::string m_sTitle;

        uint32_t m_u32Width;
        uint32_t m_u32Height;

        WindowProps(
            const std::string& a_sTitle = "RemaEngine",
            uint32_t a_u32Width = 1280,
            uint32_t a_u32Height = 720)
            : m_sTitle(a_sTitle), m_u32Width(a_u32Width), m_u32Height(a_u32Height)
        {
        }

    };

    class REMA_API Window
    {
    public:
        using fnEventCallback = std::function<void(Event&)>;
        virtual ~Window() {}

        virtual void OnUpdate() = 0;
        virtual void SetEventCallback(const fnEventCallback& a_stCallback) = 0;
        virtual void SetVSync(bool a_bEnabled) = 0;
        virtual bool IsVSync() const = 0;

        virtual void* GetNativeWindow() const = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual std::string GetWindowTitle() const = 0;

        static Window* Create(const WindowProps& a_stWndwProps = WindowProps());
    };
}

#endif // !REMA_WINDOW_H
