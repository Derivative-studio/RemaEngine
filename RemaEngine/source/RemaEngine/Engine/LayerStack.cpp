/**
 * @file RemaEngine/Engine/LayerStack.h
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
 **/ General Public License for more details.
 **/
#include <remapch.h>
#include <RemaEngine/Engine/LayerStack.h>

namespace RemaEngine
{
    LayerStack::LayerStack()
    {
    }

    LayerStack::~LayerStack()
    {
        for (Layer* layer : m_stLayers) {
            delete layer;
        }
    }

    void LayerStack::PushLayer(Layer* a_pLayer)
    {
        m_stLayers.emplace(m_stLayers.begin() + m_stLayerInsertIndex, a_pLayer);
        m_stLayerInsertIndex++;
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
            m_stLayerInsertIndex--;
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

