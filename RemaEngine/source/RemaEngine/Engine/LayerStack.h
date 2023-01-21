#ifndef REMA_LAYERSTACK_H
#define REMA_LAYERSTACK_H

#include <RemaEngine/Engine/Layer.h>

namespace RemaEngine
{
    class REMA_API LayerStack
    {
    private:
        std::vector<Layer*> m_stLayers;
        unsigned int m_stLayerInsertIndex = 0;

    public:
        LayerStack();
        ~LayerStack();

        void PushLayer(Layer* a_pLayer);
        void PushOverlay(Layer* a_pOverlay);
        void PopLayer(Layer* a_pLayer);
        void PopOverlay(Layer* a_pOverlay);

        std::vector<Layer*>::iterator begin() { return m_stLayers.begin(); }
        std::vector<Layer*>::iterator end() { return m_stLayers.end(); }

    };
}

#endif // !REMA_LAYERSTACK_H

