/**
 * @file RemaEngine/Graphics/Renderer2D.cpp
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-23
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
#include "RemaEngine/Graphics/Renderer2D.h"
#include "RemaEngine/Graphics/VertexArray.h"
#include "RemaEngine/Graphics/VertexBuffer.h"
#include "RemaEngine/Graphics/IndexBuffer.h"
#include "RemaEngine/Graphics/Shader.h"
#include "RemaEngine/Graphics/RenderCommand.h"

#include <glm/gtc/matrix_transform.hpp>

namespace RemaEngine
{
    struct Renderer2DStorage
    {
        ref<VertexArray> QuadVertexArray;
        ref<Shader> FlatColorShader;
    };

    static Renderer2DStorage* s_stRenderData;

    void Renderer2D::Init()
    {
        s_stRenderData = new Renderer2DStorage();
        s_stRenderData->QuadVertexArray = VertexArray::Create();

        float SquareVertices[3 * 4] = {
           -0.75f, -0.75f, 0.0f,
            0.75f, -0.75f, 0.0f,
            0.75f,  0.75f, 0.0f,
           -0.75f,  0.75f, 0.0f
        };

        ref<VertexBuffer> m_pSquareVertexBuffer;
        m_pSquareVertexBuffer.reset(VertexBuffer::Create(SquareVertices, sizeof(SquareVertices)));

        BufferLayout SquareVBLayout = {
            { ShaderDataType::Float3, "a_Position" }
        };

        m_pSquareVertexBuffer->SetLayout(SquareVBLayout);
        s_stRenderData->QuadVertexArray->AddVertexBuffer(m_pSquareVertexBuffer);

        uint32_t SquareIndices[6] = { 0, 1, 2, 2, 3, 0 };
        ref<IndexBuffer> m_pSquareIndexBuffer;
        m_pSquareIndexBuffer.reset(IndexBuffer::Create(SquareIndices, sizeof(SquareIndices) / sizeof(uint32_t)));
        s_stRenderData->QuadVertexArray->SetIndexBuffer(m_pSquareIndexBuffer);

        s_stRenderData->FlatColorShader = Shader::Create("assets/shaders/FlatColorShader.glsl");
    }

    void Renderer2D::Shutdown()
    {
        delete s_stRenderData;
    }

    void Renderer2D::BeginScene(const OrthographicCamera& m_stOrthoCamera)
    {
        s_stRenderData->FlatColorShader->Bind();
        s_stRenderData->FlatColorShader->SetMat4("u_ViewProjection",m_stOrthoCamera.GetViewProjectionMatrix());
    }

    void Renderer2D::EndScene()
    {

    }

    void Renderer2D::DrawQuad(const glm::vec2& a_vecPosition, const glm::vec2& a_vecSize, const glm::vec4& a_vecColor)
    {
        DrawQuad({ a_vecPosition.x, a_vecPosition.y, 0.0f }, a_vecSize, a_vecColor);
    }

    void Renderer2D::DrawQuad(const glm::vec3& a_vecPosition, const glm::vec2& a_vecSize, const glm::vec4& a_vecColor)
    {
        s_stRenderData->FlatColorShader->Bind();
        s_stRenderData->FlatColorShader->SetFloat4("u_Color", a_vecColor);

        glm::mat4 transform = glm::translate(glm::mat4(1.0f), a_vecPosition) *
            glm::scale(glm::mat4(1.0f), {a_vecSize.x, a_vecSize.y, 1.0f});
        s_stRenderData->FlatColorShader->SetMat4("u_TransformMatrix", transform);

        s_stRenderData->QuadVertexArray->Bind();
        RenderCommand::DrawIndexed(s_stRenderData->QuadVertexArray);
    }

    void Renderer2D::DrawTriangle(const glm::vec3& a_vecPosition, const glm::vec2& a_vecSize, const glm::vec4& a_vecColor)
    {

    }

    void Renderer2D::DrawCircle(const glm::vec3& a_vecPosition, const glm::vec2& a_vecSize, const glm::vec4& a_vecColor)
    {

    }
}
