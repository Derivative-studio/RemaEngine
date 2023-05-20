/**
 * @file RemaEngine/Engine/Timestep.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-20
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
    * @brief Class that
    **/
    class Timestep
    {
    private:
        float m_fTime = 0.0f;

    public:
        Timestep(float a_fTime = 0.0f)
            :m_fTime(a_fTime)
        {
        }

        float GetSeconds() const { return m_fTime; }
        float GetMilliseconds() const { return m_fTime * 1000.0f; }
        
        operator float() const { return m_fTime; }

    };
}

#endif // !REMA_TIMESTEP_H
