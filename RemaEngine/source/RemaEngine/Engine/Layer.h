/**
 * @file RemaEngine/Engine/Layer.cpp
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
#ifndef REMA_LAYER_H
#define REMA_LAYER_H

#include <RemaEngine/Event/Event.h>

namespace RemaEngine
{
    /**
    * @class RemaEngine::Layer
    * @brief A class that implements the layer system of the engine.
    * @details The layer system allows the engine to perform different 
    * functions on different layers, which can be disabled or completely 
    * removed.
    **/
    class REMA_API Layer
    {
    protected:
        std::string m_sLayerName;

    public:
        /**
        * @brief The constructor of the Layer object with the given name.
        * @details Creates a Layer object with the given name.
        * @param[in] a_sLayerName - reference to a string with the name of the layer.
        **/
        Layer(const std::string& a_sLayerName = "Layer");
        virtual ~Layer();

        /**
        * @brief A virtual method that represents the attachment behavior.
        * @details Represents a callback for a layer that appears when a 
        * layer has been attached.
        **/
        virtual void OnAttach() {}
        /**
        * @brief A virtual method that represents detach behavior.
        * @details Represents a callback for a layer that appears when a 
        * layer has been detached.
        **/
        virtual void OnDetach() {}
        /**
        * @brief A virtual method that represents update behaviour.
        * @details Represents a callback for a layer that appears when a 
        * layer has been updated.
        **/
        virtual void OnUpdate() {}
        /**
        * @brief A virtual method that represents layer behaviour on imgui rendering.
        * @details Represents a callback for a layer that appears when a
        * imgui widget has been rendered.
        **/
        virtual void OnImGuiRender() {}
        /**
        * @brief A virtual method that represents layer behaviour after specific callback.
        * @details Represents a callback for a layer that appears when a particular 
        * callback occurs.
        **/
        virtual void OnEvent(Event& a_stEvent) {}

        /**
        * @brief Returns the layer name.
        * @returns A reference to string with layer name.
        **/
        const std::string& GetName() const { return m_sLayerName; }
    };
}

#endif // !REMA_LAYER_H
