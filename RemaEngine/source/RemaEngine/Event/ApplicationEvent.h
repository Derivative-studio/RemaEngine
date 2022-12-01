#ifndef REMA_APPLICATIONEVENT_H
#define REMA_APPLICATIONEVENT_H

#include <RemaEngine/Event/Event.h>

namespace RemaEngine
{
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

        unsigned int GetWidth() const { return m_unWidth; }
        unsigned int GetHeight() const { return m_unHeight; }

        std::string ToString() const override
        {
            std::stringstream ss;
            ss << "WindowResizedEvent: " << "wdth: " << m_unWidth << " hght: " << m_unHeight;
            return ss.str();
        }

        EVENT_CLASS_TYPE(WindowResized)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)

    };

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
