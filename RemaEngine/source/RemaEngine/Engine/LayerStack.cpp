#include <remapch.h>
#include <RemaEngine/Engine/LayerStack.h>

namespace RemaEngine
{
    LayerStack::LayerStack()
    {
        m_stLayerInsert = m_stLayers.begin();
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_stLayers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* a_pLayer)
    {
        m_stLayerInsert = m_stLayers.emplace(m_stLayerInsert, a_pLayer);
    }

    void LayerStack::PushOverlay(Layer* a_pOverlay)
    {
        m_stLayers.emplace_back(a_pOverlay);
    }

    void LayerStack::PopLayer(Layer* a_pLayer)
    {
        auto it = std::find(m_stLayers.begin(), m_stLayers.end(), a_pLayer);
        if (it != m_stLayers.end()) {
            m_stLayers.erase(it);
            m_stLayerInsert--;
        }
    }

    void LayerStack::PopOverlay(Layer* a_pOverlay)
    {
        auto it = std::find(m_stLayers.begin(), m_stLayers.end(), a_pOverlay);
        if (it != m_stLayers.end()) {
            m_stLayers.erase(it);
        }
    }
}

