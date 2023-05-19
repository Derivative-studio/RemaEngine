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

namespace RemaEngine
{

#define BIND_EVENT_FN(x) std::bind(&x, this, std::placeholders::_1)

    Engine* Engine::s_Instance = nullptr;

    Engine::Engine()
    {
        REMA_CORE_ASSERT(s_Instance, "Engine instance already exists");
        s_Instance = this;

        m_stWindow = std::unique_ptr<Window>(Window::Create());
        m_stWindow->SetEventCallback(BIND_EVENT_FN(Engine::OnEvent));

        m_stpImGuiLayer = new ImGuiLayer();
        PushOverlay(m_stpImGuiLayer);

    }

    Engine::~Engine()
    {

    }

    void Engine::PushLayer(Layer* a_stLayer)
    {
        m_stLayerStack.PushLayer(a_stLayer);
        a_stLayer->OnAttach();
    }

    void Engine::PushOverlay(Layer* a_stOverlay)
    {
        m_stLayerStack.PushOverlay(a_stOverlay);
        a_stOverlay->OnAttach();
    }

    void Engine::OnEvent(Event& a_stEvent)
    {
        EventDispatcher dispatcher(a_stEvent);
        dispatcher.Dispatch<WindowClosedEvent>(BIND_EVENT_FN(Engine::CloseWindow));

        for (auto it = m_stLayerStack.end(); it != m_stLayerStack.begin();){
            (*--it)->OnEvent(a_stEvent);
            if (a_stEvent.m_bHandled) {
                break;
            }
        }
    }

    void Engine::Run()
    {
        while (m_bRunning)
        {
            for (Layer* layer : m_stLayerStack) {
                layer->OnUpdate();
            }

            m_stpImGuiLayer->Begin();

            for (Layer* layer : m_stLayerStack) {
                layer->OnImGuiRender();
            }

            m_stpImGuiLayer->End();
            m_stWindow->OnUpdate();
        }
    }

    bool Engine::CloseWindow(WindowClosedEvent& a_stEvent)
    {
        m_bRunning = false;
        return true;
    }
}