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

    void Renderer::Submit(const eastl::shared_ptr<Shader>& a_stShader, const eastl::shared_ptr<VertexArray>& a_arrVertexArray)
    {
        a_stShader->Bind();
        a_stShader->UploadUniformMat4("u_ViewProjection", m_stSceneData->m_mtxViewProjectionMatrix);

        a_arrVertexArray->Bind();
        RenderCommand::DrawIndexed(a_arrVertexArray);
    }
}
