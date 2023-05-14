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
    void Renderer::BeginScene()
    {

    }

    void Renderer::EndScene()
    {

    }

    void Renderer::Submit(const eastl::shared_ptr<VertexArray>& a_arrVertexArray)
    {
        a_arrVertexArray->Bind();
        RenderCommand::DrawIndexed(a_arrVertexArray);
    }
}
