/**
 * @file RemaEngine/IO/Input.h
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
#ifndef REMA_INPUT_H
#define REMA_INPUT_H

#include <RemaEngine/Engine/Core.h>

namespace RemaEngine
{
    class REMA_API Input
    {
    private:
        static Input* s_Instance;

    protected:
        virtual bool IsKeyPressedImpl(int a_nKeyCode) = 0;

        virtual bool IsMouseButtonPressedImpl(int a_nMouseButton) = 0;
        virtual std::pair<float, float> GetMousePositionImpl() = 0;
        virtual float GetMouseXImpl() = 0;
        virtual float GetMouseYImpl() = 0;

    public:
        static bool IsKeyPressed(int a_nKeyCode) { return s_Instance->IsKeyPressedImpl(a_nKeyCode); }

        static bool IsMouseButtonPressed(int a_nMouseButton) { return s_Instance->IsMouseButtonPressedImpl(a_nMouseButton); }
        static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
        static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
        static float GetMouseY() { return s_Instance->GetMouseYImpl(); }

    };
}

#endif // !REMA_INPUT_H
