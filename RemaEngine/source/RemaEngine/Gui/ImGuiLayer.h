/**
 * @file RemaEngine/Gui/ImGuiLayer.h
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
#ifndef REMA_IMGUILAYER_H
#define REMA_IMGUILAYER_H

#include <RemaEngine/Engine/Layer.h>
#include <RemaEngine/Event/MouseEvent.h>
#include <RemaEngine/Event/KeyboardEvent.h>
#include <RemaEngine/Event/ApplicationEvent.h>

namespace RemaEngine
{
    class REMA_API ImGuiLayer : public Layer
    {
    private:
        float m_fTime = 0.0f;

    public:
        ImGuiLayer();
        ~ImGuiLayer();

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        //virtual void OnImGuiRender() override;

        void Begin();
        void End();

    };
}

#endif // !REMA_IMGUILAYER_H

