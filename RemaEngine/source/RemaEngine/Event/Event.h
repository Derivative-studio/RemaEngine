#ifndef REMA_EVENT_H
#define REMA_EVENT_H

#include <RemaEngine/Engine/EnginePlatformSetup.h>
#include <string>
#include <functional>

namespace RemaEngine
{
    enum class EventType
    {
        None = 0,
        WindowClosed, WindowResized, WindowFocused, WindowLostFocus, WindowMoved,
        AppTick, AppUpdate, AppRender,
        KeyPressed, KeyReleased,
        MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
    };

    enum EventCategory
    {
        None = 0,
        ApplicationEventCategory    = BIT(0),
        InputEventCategory          = BIT(1),
        KeyboardEventCategory       = BIT(2),
        FloatMouseEventCategory     = BIT(3),
        MouseButtonEventCatefory    = BIT(4)
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticEventType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticEventType(); }\
                               virtual const char* GetEventName() const override { return #type; }
#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

    class REMA_API Event
    {
        friend class EventDispatcher;

    protected:
        bool m_bHandled = false;

    public:
        virtual EventType GetEventType() const = 0;
        virtual const char* GetEventName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetEventName(); }

        bool IsInCategory(EventCategory a_fCategory)
        {
            return GetCategoryFlags() & a_fCategory;
        }
    };

    class EventDispatcher
    {
        template<typename T>
        using fnEvent = std::function<bool(T&)>;

    private:
        Event& m_stEvent;

    public:
        EventDispatcher(Event& a_stEvent)
            :m_stEvent(a_stEvent)
        {
        }

        template<typename T>
        bool Dispatch(fnEvent<T> a_fnEventFunc)
        {
            if (m_stEvent.GetEventType() == T::GetStaticEventType())
            {
                m_stEvent.m_bHandled |= a_fnEventFunc(static_cast<T&>(m_stEvent));
                return true;
            }
            return false;
        }
    };

    inline std::ostream& operator<< (std::ostream& os, const Event& e)
    {
        return os << e.ToString();
    }

}

#endif // !REMA_EVENT_H
