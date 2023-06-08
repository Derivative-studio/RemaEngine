/**
 * @file RemaEngine/Utils/Platform/WindowsInput.h
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
#ifndef REMA_WINDOWSINPUT_H
#define REMA_WINDOWSINPUT_H

#include <RemaEngine/IO/Input.h>

namespace RemaEngine
{
    class WindowsInput : public Input
    {
    protected:
        virtual bool IsKeyPressedImpl(int a_nKeyCode) override;

        virtual bool IsMouseButtonPressedImpl(int a_nMouseButton) override;
        virtual std::pair<float, float> GetMousePositionImpl() override;
        virtual float GetMouseXImpl() override;
        virtual float GetMouseYImpl() override;
    };
}

#endif // !REMA_WINDOWSINPUT_H
