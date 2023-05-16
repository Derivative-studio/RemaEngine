/**
 * @file RemaEngine/Scene/Camera.h
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
#ifndef REMA_ORTHOGRAPHICCAMERA_H
#define REMA_ORTHOGRAPHICCAMERA_H

#include <glm/glm.hpp>

namespace RemaEngine
{
    /**
    * @class RemaEngine::OrthographicCamera
    * @brief The class provides orthographic camera impl
    ***/
    class OrthographicCamera
    {
    private:
        glm::mat4 m_mtxProjectionMatrix;
        glm::mat4 m_mtxVievProjectionMatrix;
        glm::mat4 m_mtxViewMatrix;

        glm::vec3 m_vecPosition = { 0.0f, 0.0f, 0.0f };
        // Since orthographic camera rotates only along z axis,
        // we doesn't bother about quaternion or this kind of stuff
        // and just use float value.
        float m_fRotation = 0.0f;
    
    private:
        /**
        * @brief recalculates camera view matrix
        **/
        void RecalculateViewMatrix();

    public:
        /**
        * @brief Orthographic camera constructor
        * @param[in] a_fLeft - left projection matrix bound
        * @param[in] a_fRight - right projection matrix bound
        * @param[in] a_fTop - top projection matrix bound
        * @param[in] a_fBottom - bottom projection matrix bound
        **/
        OrthographicCamera(float a_fLeft, float a_fRight, float a_fBottom, float a_fTop);
        ~OrthographicCamera(){}

        /**
        * @brief sets camera world position
        * @param[in] a_vecPosition - coordinate for camera placement
        **/
        void SetPosition(const glm::vec3& a_vecPosition) { m_vecPosition = a_vecPosition; RecalculateViewMatrix(); }
        /**
        * @brief sets camera rotation value in **degrees**
        * @param[in] a_fRotation - camera angle degree
        **/
        void SetRotation(float a_fRotation) { m_fRotation = a_fRotation; RecalculateViewMatrix(); }


        /**
        * @brief gets current position of the camera
        * @returns current position of the camera
        * @return glm::vec3&
        **/
        const glm::vec3& GetPosition() const { return m_vecPosition; }
        /**
        * @brief gets camera projection matrix
        * @returns camera projection matrix
        * @return glm::mat4&
        **/
        const glm::mat4& GetProjectionMatrix() const { return m_mtxProjectionMatrix; }
        /**
        * @brief gets camera view projection matrix
        * @returns camera view projection matrix
        * @return glm::mat4&
        **/
        const glm::mat4& GetViewProjectionMatrix() const { return m_mtxVievProjectionMatrix; }
        /**
        * @brief gets camera view matrix
        * @returns camera view matrix
        * @return glm::mat4&
        **/
        const glm::mat4& GetViewMatrix() const { return m_mtxViewMatrix; }
        /**
        * @brief gets current camera rotation value
        * @returns current camera rotation value
        * @return float
        **/
        float GetRotation() const { return m_fRotation; }

    };
}

#endif // !REMA_ORTHOGRAPHICCAMERA_H
