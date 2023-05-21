/**
 * @file RemaEngine/Graphics/RenderCommand.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-03-21
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
#include "RemaEngine/Graphics/Renderer.h"
#include "RemaEngine/Graphics/RenderCommand.h"
#include "RemaEngine/Graphics/OpenGL/OpenGLShader.h"
#include "RemaEngine/Utils/MemoryUtils.h"

namespace RemaEngine
{
    Renderer::SceneData* Renderer::m_stSceneData = new Renderer::SceneData;

    void Renderer::BeginScene(OrthographicCamera& a_stCamera)
    {
        m_stSceneData->m_mtxViewProjectionMatrix = a_stCamera.GetViewProjectionMatrix();
    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const ref<Shader>& a_stShader,
        const ref<VertexArray>& a_arrVertexArray,
        const glm::mat4& a_mtxTransofrmMatrix)
    {
        a_stShader->Bind();

        eastl_dynamic_pointer_cast<OpenGLShader>(a_stShader)->UploadUniformMat4("u_ViewProjection", m_stSceneData->m_mtxViewProjectionMatrix);
        eastl_dynamic_pointer_cast<OpenGLShader>(a_stShader)->UploadUniformMat4("u_TransformMatrix", a_mtxTransofrmMatrix);

        a_arrVertexArray->Bind();
        RenderCommand::DrawIndexed(a_arrVertexArray);
    }
}
