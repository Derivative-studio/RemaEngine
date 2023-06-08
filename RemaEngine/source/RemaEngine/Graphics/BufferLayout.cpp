/**
 * @file RemaEngine/Graphics/IndexBuffer.cpp
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
#include "remapch.h"
#include "BufferLayout.h"


namespace RemaEngine
{
    void BufferLayout::CalculateOffsetsAndStride()
    {
        uint32_t offset = 0;
        m_unStride = 0;

        for (auto& iElement : m_arrElements) {
            iElement.m_unOffset = offset;
            offset += iElement.m_unSize;
            m_unStride += iElement.m_unSize;
        }
    }

    uint32_t BufferElement::GetComponentCount() const
    {
        switch (m_stShaderDataType)
        {
            case ShaderDataType::Float:     return 1;
            case ShaderDataType::Float2:    return 2;
            case ShaderDataType::Float3:    return 3;
            case ShaderDataType::Float4:    return 4;
            case ShaderDataType::Mat3:      return 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4;
            case ShaderDataType::Int:       return 1;
            case ShaderDataType::Int2:      return 2;
            case ShaderDataType::Int3:      return 3;
            case ShaderDataType::Int4:      return 4;
            case ShaderDataType::Bool:      return 1;
        }

        REMA_CORE_ASSERT(false, "Illigal shader data type");
        return 0;
    }
}
