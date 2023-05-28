/**
 * @file RemaEngine/Engine/Engine.cpp
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
#include "remapch.h"

#include "RemaEngine/IO/Input.h"
#include "RemaEngine/Engine/Engine.h"
#include "RemaEngine/System/Logger.h"
#include "RemaEngine/Event/ApplicationEvent.h"

#include "RemaEngine/Graphics/BufferLayout.h"
#include "RemaEngine/Graphics/Renderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace RemaEngine
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Engine* Engine::s_Instance = nullptr;

    Engine::Engine()
    {
        REMA_PROFILE_FUNCTION();

        REMA_CORE_ASSERT(s_Instance, "Engine instance already exists");
        s_Instance = this;

        m_stWindow = std::unique_ptr<Window>(Window::Create());
        m_stWindow->SetEventCallback(BIND_EVENT_FN(Engine::OnEvent));

        Renderer::Init();

        m_stpImGuiLayer = new ImGuiLayer();
        PushOverlay(m_stpImGuiLayer);

        m_stFPSCounter = eastl::make_shared<FPSCounter>();

    }

    Engine::~Engine()
    {
        REMA_PROFILE_FUNCTION();

        Renderer::Shutdown();
    }

    void Engine::PushLayer(Layer* a_stLayer)
    {
        REMA_PROFILE_FUNCTION();

        m_stLayerStack.PushLayer(a_stLayer);
        a_stLayer->OnAttach();
    }

    void Engine::PushOverlay(Layer* a_stOverlay)
    {
        REMA_PROFILE_FUNCTION();

        m_stLayerStack.PushOverlay(a_stOverlay);
        a_stOverlay->OnAttach();
    }

    void Engine::OnEvent(Event& a_stEvent)
    {
        REMA_PROFILE_FUNCTION();

        EventDispatcher dispatcher(a_stEvent);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Engine::CloseWindow));
        dispatcher.Dispatch<WindowResizedEvent>(BIND_EVENT_FN(Engine::ResizeWindow));

        for (auto it = m_stLayerStack.end(); it != m_stLayerStack.begin();){
            (*--it)->OnEvent(a_stEvent);
            if (a_stEvent.m_bHandled) {
                break;
            }
        }
    }

    void Engine::Run()
    {
        REMA_PROFILE_FUNCTION();

        while (m_bRunning)
        {
            REMA_SET_PROFILE_SCOPE("EngineRunLoop");

            //float l_glTime = static_cast<float>(glfwGetTime());
            //Timestep timestep = l_glTime - m_fLastFrameTime;
            //m_fLastFrameTime = l_glTime;
            m_stFPSCounter->AddFrame();

            if (m_bWindowMinimized == false) 
            {
                {
                    REMA_SET_PROFILE_SCOPE("Layer::OnUpdate");

                    for (Layer* layer : m_stLayerStack) {
                        layer->OnUpdate(m_stFPSCounter->GetTimestep());
                    }
                }

                m_stpImGuiLayer->Begin();
                {
                    REMA_SET_PROFILE_SCOPE("ImGuiLayer::OnUpdate");

                    for (Layer* layer : m_stLayerStack) {
                        layer->OnImGuiRender();
                    }
                }

                m_stpImGuiLayer->End();
            }

            m_stWindow->OnUpdate();
        }
    }

    bool Engine::CloseWindow(WindowClosedEvent& a_stEvent)
    {
        m_bRunning = false;
        return true;
    }

    bool Engine::ResizeWindow(WindowResizedEvent& a_stEvent)
    {
        REMA_PROFILE_FUNCTION();

        if (a_stEvent.GetHeight() == 0 || a_stEvent.GetWidth() == 0) {
            m_bWindowMinimized = true;
            return false;
        }

        m_bWindowMinimized = false;
        Renderer::OnWindowResized(a_stEvent.GetWidth(), a_stEvent.GetHeight());

        return false;
    }

    //////////////////////
    // FPS Counter
    //////////////////////

    FPSCounter::FPSCounter()
    {
        m_nFrameCounter = 0;

        m_fFPS = 60.0f;
        m_fUpdateRate = 1.0f;
        m_fLastFrameTime = 0.0f;

        m_fGLTime = static_cast<float>(glfwGetTime());
        m_stCurrTimestep = m_fGLTime - m_fLastFrameTime;
        m_fLastFrameTime = m_fGLTime;
    }

    void FPSCounter::AddFrame()
    {
        m_fGLTime = static_cast<float>(glfwGetTime());
        m_stCurrTimestep = m_fGLTime - m_fLastFrameTime;
        m_fLastFrameTime = m_fGLTime;

        m_nFrameCounter++;

        if (m_fLastFrameTime >= m_fUpdateRate) {
            m_fFPS = static_cast<float>(m_nFrameCounter / m_stCurrTimestep.GetSeconds());
            m_nFrameCounter = 0;
        }
    }


}