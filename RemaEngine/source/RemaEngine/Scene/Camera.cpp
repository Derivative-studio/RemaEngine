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
#include "RemaEngine/IO/Input.h"
#include "RemaEngine/IO/KeyCodeDefinitions.h"

#include <glm/gtc/matrix_transform.hpp>

namespace RemaEngine
{
    OrthographicCamera::OrthographicCamera(float a_fLeft, float a_fRight, float a_fBottom, float a_fTop)
        : m_mtxProjectionMatrix(glm::ortho(a_fLeft, a_fRight, a_fBottom, a_fTop, -1.0f, 1.0f)), m_mtxViewMatrix(1.0f)
    {
        REMA_PROFILE_FUNCTION();

        m_mtxVievProjectionMatrix = m_mtxProjectionMatrix * m_mtxViewMatrix;
    }

    void OrthographicCamera::SetProjection(float a_fLeft, float a_fRight, float a_fBottom, float a_fTop)
    {
        REMA_PROFILE_FUNCTION();

        m_mtxProjectionMatrix = glm::ortho(a_fLeft, a_fRight, a_fBottom, a_fTop, -1.0f, 1.0f);
        m_mtxVievProjectionMatrix = m_mtxProjectionMatrix * m_mtxViewMatrix;
    }

    void OrthographicCamera::RecalculateViewMatrix()
    {
        REMA_PROFILE_FUNCTION();

        glm::mat4 mtxTransform = glm::translate(glm::mat4(1.0f), m_vecPosition)
            * glm::rotate(glm::mat4(1.0f), glm::radians(m_fRotation), glm::vec3(0, 0, 1));

        m_mtxViewMatrix = glm::inverse(mtxTransform);
        m_mtxVievProjectionMatrix = m_mtxProjectionMatrix * m_mtxViewMatrix;
    }

    ///////////////////////////////////
    // Orthographic camera controller
    //////////////////////////////////

    OrthographicCameraController::OrthographicCameraController(float a_fAspectRatio, bool a_bLockRotation)
        :m_fAspectRatio(a_fAspectRatio), m_bLockRotation(a_bLockRotation),
        m_stCamera(-m_fAspectRatio * m_fZoomLevel, m_fAspectRatio* m_fZoomLevel, -m_fZoomLevel, m_fZoomLevel)
    {

    }

    bool OrthographicCameraController::OnMouseScrolled(MouseScrolledEvent& a_stEvent)
    {
        REMA_PROFILE_FUNCTION();

        m_fZoomLevel -= a_stEvent.GetYOffset() * 0.25;
        m_fZoomLevel = eastl::max(m_fZoomLevel, 0.25f);
        m_stCamera.SetProjection(-m_fAspectRatio * m_fZoomLevel, m_fAspectRatio * m_fZoomLevel, -m_fZoomLevel, m_fZoomLevel);
        return false;
    }

    bool OrthographicCameraController::OnWindowResized(WindowResizedEvent& a_stEvent)
    {
        REMA_PROFILE_FUNCTION();

        m_fAspectRatio = static_cast<float>(a_stEvent.GetWidth()) / static_cast<float>(a_stEvent.GetHeight());
        m_stCamera.SetProjection(-m_fAspectRatio * m_fZoomLevel, m_fAspectRatio * m_fZoomLevel, -m_fZoomLevel, m_fZoomLevel);
        return false;
    }

    void OrthographicCameraController::OnUpdate(Timestep a_stTimestep)
    {
        REMA_PROFILE_FUNCTION();

        if (Input::IsKeyPressed(REMA_KEY_A)) {
            m_vecCameraPosition.x -= cos(glm::radians(m_fCameraRotation)) * m_fCameraTranslationSpeed * a_stTimestep;
            m_vecCameraPosition.y -= sin(glm::radians(m_fCameraRotation)) * m_fCameraTranslationSpeed * a_stTimestep;
        }
        else if (Input::IsKeyPressed(REMA_KEY_D)) {
            m_vecCameraPosition.x += cos(glm::radians(m_fCameraRotation)) * m_fCameraTranslationSpeed * a_stTimestep;
            m_vecCameraPosition.y += sin(glm::radians(m_fCameraRotation)) * m_fCameraTranslationSpeed * a_stTimestep;
        }

        if (Input::IsKeyPressed(REMA_KEY_S)) {
            m_vecCameraPosition.x -= -sin(glm::radians(m_fCameraRotation)) * m_fCameraTranslationSpeed * a_stTimestep;
            m_vecCameraPosition.y -= cos(glm::radians(m_fCameraRotation)) * m_fCameraTranslationSpeed * a_stTimestep;
        }
        else if (Input::IsKeyPressed(REMA_KEY_W)) {
            m_vecCameraPosition.x += -sin(glm::radians(m_fCameraRotation)) * m_fCameraTranslationSpeed * a_stTimestep;
            m_vecCameraPosition.y += cos(glm::radians(m_fCameraRotation)) * m_fCameraTranslationSpeed * a_stTimestep;
        }

        if (m_bLockRotation == false) {
            if (Input::IsKeyPressed(REMA_KEY_Q)) {
                m_fCameraRotation -= m_fCameraRotationSpeed * a_stTimestep;
            }
            else if (Input::IsKeyPressed(REMA_KEY_E)) {
                m_fCameraRotation += m_fCameraRotationSpeed * a_stTimestep;
            }

            if (m_fCameraRotation > 180.0f) {
                m_fCameraRotation -= 360.0f;
            }
            else if (m_fCameraRotation <= -180.0f) {
                m_fCameraRotation += 360.0f;
            }

            m_stCamera.SetRotation(m_fCameraRotation);
        }

        m_stCamera.SetPosition(m_vecCameraPosition);
    }

    void OrthographicCameraController::OnEvent(Event& a_stEvent)
    {
        REMA_PROFILE_FUNCTION();

        EventDispatcher dispatcher(a_stEvent);
        dispatcher.Dispatch<MouseScrolledEvent>(REMA_BIND_EVENT_FN(OrthographicCameraController::OnMouseScrolled));
        dispatcher.Dispatch<WindowResizedEvent>(REMA_BIND_EVENT_FN(OrthographicCameraController::OnWindowResized));
    }
}
