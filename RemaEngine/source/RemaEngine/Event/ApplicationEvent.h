/**
 * @file RemaEngine/Event/ApplicationEvent.h
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
#ifndef REMA_APPLICATIONEVENT_H
#define REMA_APPLICATIONEVENT_H

#include <RemaEngine/Event/Event.h>

namespace RemaEngine
{
    /**
    * @class RemaEngine::WindowResizedEvent
    * @extends RemaEngine::Event
    * @brief The class that defines the resizing event of the 
    * renderable window.
    * @details The class associated with the event system
    * defines the resize callback for the renderable window.
    **/
    class REMA_API WindowResizedEvent : public Event
    {
    private:
        unsigned int m_unWidth = NULL;
        unsigned int m_unHeight = NULL;

    public:
        WindowResizedEvent(unsigned int a_unWidth, unsigned int a_unHeight)
            : m_unWidth(a_unWidth), m_unHeight(a_unHeight)
        {
        }

        /**
        * @brief Returns renderable window width in pixels.
        * @returns The renderable window width.
        **/
        unsigned int GetWidth() const { return m_unWidth; }
        /**
        * @brief Returns renderable window height in pixels.
        * @returns The renderable window height.
        **/
        unsigned int GetHeight() const { return m_unHeight; }

        /**
        * @brief Returns string based info about current state of window.
        * @example "WindowResizedEvent: wdth: 1920 hght: 1080"
        * @returns The string width window info.
        **/
        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizedEvent: " << "wdth: " << m_unWidth << " hght: " << m_unHeight;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResized)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)

    };

    /**
    * @class RemaEngine::WindowClosedEvent
    * @extends RemaEngine::Event
    * @brief The class that defines the closing event of the
    * renderable window.
    * @details The class associated with the event system
    * defines the close callback for the renderable window.
    **/
    class REMA_API WindowClosedEvent : public Event
    {
    public:
        WindowClosedEvent() {}

        EVENT_CLASS_TYPE(WindowClosed)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
    };

    class REMA_API AppTickEvent : public Event
    {
    public:
        AppTickEvent() {}

        EVENT_CLASS_TYPE(AppTick)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
    };

    class REMA_API AppUpdateEvent : public Event
    {
        AppUpdateEvent() {}

        EVENT_CLASS_TYPE(AppUpdate)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
    };

    class REMA_API AppRenderEvent : public Event
    {
    public:
        AppRenderEvent() {}

        EVENT_CLASS_TYPE(AppRender)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
    };

}

#endif // !REMA_APPLICATIONEVENT_H
