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

        m_pVertexArray.reset(VertexArray::Create());

        float vertices[3 * 7] = {
            -0.5f, -0.5f, 0.0f, 0.3f, 0.4f, 0.2f, 1.0f,
             0.5f, -0.5f, 0.0f, 0.2f, 0.3f, 1.0f, 1.0f,
             0.0f,  0.5f, 0.0f, 1.0f, 0.2f, 0.5f, 1.0f
        };

        eastl::shared_ptr<VertexBuffer> m_pVertexBuffer;
        m_pVertexBuffer.reset(VertexBuffer::Create(vertices, sizeof(vertices)));
        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color" }
        };

        m_pVertexBuffer->SetLayout(layout);
        m_pVertexArray->AddVertexBuffer(m_pVertexBuffer); 

        uint32_t indices[3] = { 0, 1, 2 };
        eastl::shared_ptr<IndexBuffer> m_pIndexBuffer;
        m_pIndexBuffer.reset(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
        m_pVertexArray->SetIndexBuffer(m_pIndexBuffer);

        m_pSquareVertexArray.reset(VertexArray::Create());

        float squareVertices[3 * 4] = {
           -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f,  0.75f, 0.0f,
           -0.75f,  0.75f, 0.0f
        };

        eastl::shared_ptr<VertexBuffer> suqreVB;
        suqreVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

        BufferLayout squareVBLayout = {
            { ShaderDataType::Float3, "a_Position" },
        };

        suqreVB->SetLayout(squareVBLayout);
        m_pSquareVertexArray->AddVertexBuffer(suqreVB);

        uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        eastl::shared_ptr<IndexBuffer> suqreIB;
        suqreIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
        m_pSquareVertexArray->SetIndexBuffer(suqreIB);

        std::string tmpVtxShader = R"(
            # version 330 core

            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            out vec3 v_Position;
            out vec4 v_Color;

            void main()
            {
                v_Position = a_Position;
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string tmpFragShader = R"(
            # version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;
            in vec4 v_Color;

            void main()
            {
                color = vec4(v_Position * 0.5f + 0.5f, 1.0f);
                color = v_Color;
            }
        )";

        m_stShader.reset(new Shader(tmpVtxShader, tmpFragShader));

        std::string tmpVtxShader_2 = R"(
            # version 330 core

            layout(location = 0) in vec3 a_Position;

            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string tmpFragShader_2 = R"(
            # version 330 core

            layout(location = 0) out vec4 color;

            in vec3 v_Position;

            void main()
            {
                color = vec4(0.2f, 0.3f, 0.8f, 1.0f);
            }
        )";

        m_stShader_2.reset(new Shader(tmpVtxShader_2, tmpFragShader_2));
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
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_stShader_2->Bind();
            Renderer::Submit(m_pSquareVertexArray);

            m_stShader->Bind();
            Renderer::Submit(m_pVertexArray);

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