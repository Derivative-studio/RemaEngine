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

    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        //virtual void OnImGuiRender() override;

        void Begin();
        void End();

    };
}

#endif // !REMA_IMGUILAYER_H

