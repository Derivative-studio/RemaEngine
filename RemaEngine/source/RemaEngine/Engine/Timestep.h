/**
 * @file RemaEngine/Engine/Timestep.h
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
#ifndef REMA_TIMESTEP_H
#define REMA_TIMESTEP_H

namespace RemaEngine
{
    /**
    * @class RemaEngine::Timestep
    * @brief Class that prevents dependency between 
    * movement speed and render time.
    **/
    class Timestep
    {
    private:
        float m_fTime = 0.0f;

    public:
        /**
        * @brief Constructor of the Timestep class.
        * @param[in] a_fTime - the delta time in seconds.
        **/
        Timestep(float a_fTime = 0.0f)
            :m_fTime(a_fTime)
        {
        }

        /**
        * @brief Returns the delta time in seconds.
        * @returns The delta time in seconds.
        * @return float
        **/
        float GetSeconds() const { return m_fTime; }
        /**
        * @brief Returns the delta time in miliseconds.
        * @returns The delta time in miliseconds.
        * @return float
        **/
        float GetMilliseconds() const { return m_fTime * 1000.0f; }

        /**
        * @brief Overloads float() cast for Timestep class.
        * @returns The delta time in seconds.
        * @return float
        **/
        operator float() const { return m_fTime; }

    };
}

#endif // !REMA_TIMESTEP_H
