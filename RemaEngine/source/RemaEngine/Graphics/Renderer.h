/**
 * @file RemaEngine/Graphics/RenderCommand.h
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
 **/
#ifndef REMA_RENDERER_H
#define REMA_RENDERER_H

#include "RemaEngine/Scene/Camera.h"
#include "RemaEngine/Graphics/RenderCommand.h"
#include "RemaEngine/Graphics/RendererAPI.h"
#include "RemaEngine/Graphics/Shader.h"

#include <EASTL/shared_ptr.h>

namespace RemaEngine
{
    /**
    * @class RemaEngine::Renderer
    * @brief RemaEngine virtual renderer class
    **/
    class Renderer
    {
    private:
        struct SceneData
        {
            glm::mat4 m_mtxViewProjectionMatrix;
        };
        static SceneData* m_stSceneData;

    public:
        static void Init();
        static void Shutdown();

        static void BeginScene(OrthographicCamera& a_stCamera);
        static void EndScene();
        /**
        * @brief Submits different object data to render.
        * @param[in] a_stShader - the object shader.
        * @param[in] a_arrVertexArray - the object vertecies.
        * @param[in] a_mtxTransfromMatrix - object tarnsofrm matrix (1.0f by default).
        **/
        static void Submit(const ref<Shader>& a_stShader,
            const ref<VertexArray>& a_arrVertexArray,
            const glm::mat4& a_mtxTransofrmMatrix = glm::mat4(1.0f));

        static void OnWindowResized(uint32_t a_unWidth, uint32_t a_unHeight);

        /**
        * @returns returns currently used graphics API
        * @return object of RemaEngine::RendererAPI::API class
        **/
        inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }

    };
}

#endif // !REMA_RENDERER_H
