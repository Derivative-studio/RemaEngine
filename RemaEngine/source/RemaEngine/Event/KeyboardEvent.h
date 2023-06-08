/**
 * @file RemaEngine/Engine/EnginePlatformSetup.h
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
#ifndef REMA_KEYBOARD_EVENT
#define REMA_KEYBOARD_EVENT

#include <RemaEngine/Event/Event.h>

namespace RemaEngine
{
    class REMA_API KeyEvent : public Event
    {
    protected:
        KeyEvent(int a_nKeyCode)
            : m_nKeyCode(a_nKeyCode)
        {
        }

        int m_nKeyCode;

    public:
        int GetKeyCode() const { return m_nKeyCode; }

        EVENT_CLASS_CATEGORY(KeyboardEventCategory | InputEventCategory)

    };

    class REMA_API KeyPressedEvent : public KeyEvent
    {
    private:
        int m_nRepeatCount;

    public:
        KeyPressedEvent(int a_nKeyCode, int a_nRepeatCount)
            : KeyEvent(a_nKeyCode), m_nRepeatCount(a_nRepeatCount)
        {
        }

        inline int GetRepeatCount() const { return m_nRepeatCount; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyPressedEvent: " << m_nKeyCode << " pressed " << m_nRepeatCount << " times";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyPressed)
    };

    class REMA_API KeyReleasedEvent : public KeyEvent
    {
    public:
        KeyReleasedEvent(int a_nKeyCode)
            : KeyEvent(a_nKeyCode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyReleasedEvent: " << m_nKeyCode << " released";
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class REMA_API KeyTypedEvent : public KeyEvent
    {
    public:
        KeyTypedEvent(int a_nKeyCode)
            : KeyEvent(a_nKeyCode)
        {
        }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "KeyTypedEvent: " << m_nKeyCode;
            return ss.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };

}

#endif // !REMA_KEYBOARD_EVENT
