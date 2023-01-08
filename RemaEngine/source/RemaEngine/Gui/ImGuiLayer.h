#ifndef REMA_IMGUILAYER_H
#define REMA_IMGUILAYER_H

#include <RemaEngine/Engine/Layer.h>

namespace RemaEngine
{
    class REMA_API ImGuiLayer : public Layer
    {
    private:
        float m_fTime = 0.0f;

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

