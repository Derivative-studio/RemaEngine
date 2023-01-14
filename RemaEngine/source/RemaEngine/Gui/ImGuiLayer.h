#ifndef REMA_IMGUILAYER_H
#define REMA_IMGUILAYER_H

#include <RemaEngine/Engine/Layer.h>
#include <RemaEngine/Event/MouseEvent.h>
#include <RemaEngine/Event/KeyboardEvent.h>
#include <RemaEngine/Event/ApplicationEvent.h>

namespace RemaEngine
{
    class REMA_API ImGuiLayer : public Layer
    {
    private:
        float m_fTime = 0.0f;

        bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& a_stEvent);
        bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& a_stEvent);
        bool OnMouseMovedEvent(MouseMovedEvent& a_stEvent);
        bool OnMouseScrolledEvent(MouseScrolledEvent& a_stEvent);
        bool OnWindowResizedEvent(WindowResizedEvent& a_stEvent);
        bool OnKeyPressedEvent(KeyPressedEvent& a_stEvent);
        bool OnKeyReleasedEvent(KeyReleasedEvent& a_stEvent);
        bool OnKeyTypedEvent(KeyTypedEvent& a_stEvent);

    public:
        ImGuiLayer();
        ~ImGuiLayer();

        void OnAttach();
        void OnDetach();
        void OnUpdate();
        void OnEvent(Event& a_stEvent);

    };
}

#endif // !REMA_IMGUILAYER_H

