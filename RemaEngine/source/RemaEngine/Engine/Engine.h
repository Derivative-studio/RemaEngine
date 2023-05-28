/**
 * @file RemaEngine/Engine/Engine.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-03-29
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
#ifndef REMA_ENGINE_H
#define REMA_ENGINE_H

#include "RemaEngine/IO/Window.h"
#include "RemaEngine/Gui/ImGuiLayer.h"
#include "RemaEngine/Scene/Camera.h"

#include "RemaEngine/Engine/LayerStack.h"
#include "RemaEngine/Engine/Core.h"
#include "RemaEngine/Engine/Timestep.h"

#include "RemaEngine/Event/Event.h"
#include "RemaEngine/Event/ApplicationEvent.h"

#include "RemaEngine/Graphics/Shader.h"
#include "RemaEngine/Graphics/VertexBuffer.h"
#include "RemaEngine/Graphics/IndexBuffer.h"
#include "RemaEngine/Graphics/VertexArray.h"

#include <EASTL/shared_ptr.h>
#include <EASTL/unique_ptr.h>

namespace RemaEngine
{
    class REMA_API FPSCounter
    {
    private:
        int m_nFrameCounter;

        float m_fFPS;
        float m_fUpdateRate;
        float m_fLastFrameTime;
        float m_fGLTime;

        Timestep m_stCurrTimestep;

    public:
        FPSCounter();
        ~FPSCounter() = default;

        void AddFrame();

        Timestep GetTimestep() const { return m_stCurrTimestep; }
        float GetLastFrameTime() const { return m_fLastFrameTime; }
        float GetFPSFLoat() const { return m_fFPS; }
        int GetFPSInt() const { return static_cast<int>(m_fFPS); }

    };

    /**
     * @class RemaEngine::Engine
     * @brief A class which implements main engine singleton class.
     **/
    class REMA_API Engine
    {
    private:
        std::unique_ptr<Window> m_stWindow;
        ImGuiLayer* m_stpImGuiLayer;
        LayerStack m_stLayerStack;
        float m_fLastFrameTime = 0.0f;

        bool m_bRunning = true;
        bool m_bWindowMinimized = false;
        static Engine* s_Instance;

        ref<FPSCounter> m_stFPSCounter;


    private:
        /**
        * @brief Stops the engine game loop if the application window has been closed.
        * @param[in] a_stEvent - reference to WindowClosedEvent function.
        * @returns True
        **/
        bool CloseWindow(WindowClosedEvent& a_stEvent);
        bool ResizeWindow(WindowResizedEvent& a_stEvent);

    public:
        Engine();
        virtual ~Engine();

        /**
         * @brief Starts the game engine loop.
         * @details Starts the game loop for current instance of engine.
         **/
        void Run();

        /**
        * @brief Creates an event dispatcher to handle given event callback.
        * @param[in] a_stEvent - reference to Event object which needs to handle.
        **/
        void OnEvent(Event& a_stEvent);
        /**
        * @brief Pushes the given layer onto the layer stack of the engine instance.
        * @param[in] a_stLayer - pointer to the Layer object.
        **/
        void PushLayer(Layer* a_stLayer);
        /**
        * @brief Places the given layer at the top of the engine instance layer stack.
        * @param[in] a_stOverlay - pointer to the Layer object.
        **/
        void PushOverlay(Layer* a_stOverlay);

        /**
        * @brief Method that returns the application window of the engine.
        * @returns The pointer to application window.
        **/
        inline Window& GetWindow() { return *m_stWindow; }
        /**
        * @brief A static method that returns an instance of the engine.
        * @returns The pointer to engine instance.
        **/
        inline static Engine& GetInstance() { return *s_Instance; }
    };

    /**
    * @brief Creates a RemaEngine application.
    * @details Creates a new RemaEngine application instance via default countructor.
    * @returns The RemaEngine application object.
    * @warning Function must be implemented on application side!
    **/
    Engine* CreateApplication();
}

#endif REMA_ENGINE_H // !REMA_ENGINE_H
