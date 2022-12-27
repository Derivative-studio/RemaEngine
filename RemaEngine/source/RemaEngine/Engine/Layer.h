#ifndef REMA_LAYER_H
#define REMA_LAYER_H

#include <RemaEngine/Event/Event.h>

namespace RemaEngine
{
    class REMA_API Layer
    {
    protected:
        std::string m_sLayerName;

    public:
        Layer(const std::string& a_sLayerName = "Layer");
        virtual ~Layer();

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnEvent(Event& a_stEvent) {}

        const std::string& GetName() const { return m_sLayerName; }
    };
}

#endif // !REMA_LAYER_H
