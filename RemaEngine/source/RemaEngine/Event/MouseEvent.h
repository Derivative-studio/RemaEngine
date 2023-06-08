/**
 * @file RemaEngine/Event/MouseEvent.h
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
#ifndef REMA_MOUSEEVENT_H
#define REMA_MOUSEEVENT_H

#include <RemaEngine/Event/Event.h>

namespace RemaEngine
{
    class REMA_API MouseMovedEvent : public Event
    {
    private:
        float m_fMouseX = NULL;
        float m_fMouseY = NULL;

    public:
        MouseMovedEvent(float a_fMouseX, float a_fMouseY)
            : m_fMouseX(a_fMouseX), m_fMouseY(a_fMouseY)
        {
        }

        float GetX() const { return m_fMouseX; }
        float GetY() const { return m_fMouseY; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseMovedEvent: " << "x: " << m_fMouseX << " y: " << m_fMouseY;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(FloatMouseEventCategory | InputEventCategory)
    };

    class MouseScrolledEvent : public Event
    {
    private:
        float m_fXOffset = NULL;
        float m_fYOffset = NULL;

    public:
        MouseScrolledEvent(float a_fXOffset, float a_fYOffset)
            : m_fXOffset(a_fXOffset), m_fYOffset(a_fYOffset)
        {
        }

        float GetXOffset() const { return m_fXOffset; }
        float GetYOffset() const { return m_fYOffset; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseScrolledEvent: " << "x: " << m_fXOffset << " y: " << m_fYOffset;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(FloatMouseEventCategory | InputEventCategory)
    };

    class MouseButtonEvent : public Event
    {
    protected:
        MouseButtonEvent(int a_nMouseKeyCode)
            :m_nMouseKeyCode(a_nMouseKeyCode)
        {
        }

        int m_nMouseKeyCode = NULL;

    public:
        int GetMouseKeyCode() const { return m_nMouseKeyCode; }
        EVENT_CLASS_CATEGORY(FloatMouseEventCategory | InputEventCategory)

    };

    class REMA_API MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(int a_nMouseKeyCode)
            : MouseButtonEvent(a_nMouseKeyCode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonPressedEvent: " << m_nMouseKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class REMA_API MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(int a_nMouseKeyCode)
            : MouseButtonEvent(a_nMouseKeyCode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "MouseButtonReleasedEvent: " << m_nMouseKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };
}

#endif // !REMA_MOUSEEVENT_H
