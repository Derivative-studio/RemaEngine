/**
 * @file RemaEngine/Engine/LayerStack.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-04-02
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
#ifndef REMA_LAYERSTACK_H
#define REMA_LAYERSTACK_H

#include <RemaEngine/Engine/Layer.h>

namespace RemaEngine
{
    /**
    * @class RemaEngine::LayerStack
    * @brief A class that implements a layer stack structure.
    * @details A layer stack structure that allows you to store 
    * objects of the Layer class.
    * @note Note that the order of the layers in the stack matters!
    **/
    class REMA_API LayerStack
    {
    private:
        std::vector<Layer*> m_stLayers;
        unsigned int m_stLayerInsertIndex = 0;

    public:
        LayerStack();
        ~LayerStack();

        /**
        * @brief Pushes given layer on the current
        * index in stack and moves it.
        * @param[in] a_pLayer - pointer to the layer 
        * to push onto the stack.
        **/
        void PushLayer(Layer* a_pLayer);
        /**
        * @brief Pushes given layer at the end of the
        * layer stack.
        * @details Places the specified layer at the end 
        * of the layer stack. This layer will be rendered 
        * last and placed on top of the others.
        * @param[in] a_pOverlay - pointer to the layer that 
        * should be above the others.
        **/
        void PushOverlay(Layer* a_pOverlay);
        /**
        * @brief Erases the specified layer from the layer stack.
        * @param[in] a_pLayer - pointer to the layer to be 
        * removed from the layer stack.
        **/
        void PopLayer(Layer* a_pLayer);
        /**
        * 
        **/
        void PopOverlay(Layer* a_pOverlay);

        /**
        * @brief Begin iterator for layer stack.
        * @returns Begin iterator of vector with layers in it.
        **/
        std::vector<Layer*>::iterator begin() { return m_stLayers.begin(); }
        /**
        * @brief End iterator for layer stack.
        * @returns End iterator of vector with layers in it.
        **/
        std::vector<Layer*>::iterator end() { return m_stLayers.end(); }

    };
}

#endif // !REMA_LAYERSTACK_H

