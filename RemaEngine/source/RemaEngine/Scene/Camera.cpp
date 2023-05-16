/**
 * @file RemaEngine/Scene/Camera.cpp
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-16
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
#include "RemaEngine/Scene/Camera.h"

#include <glm/gtc/matrix_transform.hpp>

namespace RemaEngine
{
    OrthographicCamera::OrthographicCamera(float a_fLeft, float a_fRight, float a_fBottom, float a_fTop)
        : m_mtxProjectionMatrix(glm::ortho(a_fLeft, a_fRight, a_fBottom, a_fTop, -1.0f, 1.0f)), m_mtxViewMatrix(1.0f)
    {
        m_mtxVievProjectionMatrix = m_mtxProjectionMatrix * m_mtxViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        glm::mat4 mtxTransform = glm::translate(glm::mat4(1.0f), m_vecPosition)
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_fRotation), glm::vec3(0, 0, 1));

        m_mtxViewMatrix = glm::inverse(mtxTransform);
        m_mtxVievProjectionMatrix = m_mtxProjectionMatrix * m_mtxViewMatrix;
    }
}
