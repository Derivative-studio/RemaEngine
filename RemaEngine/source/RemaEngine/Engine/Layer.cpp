/**
 * @file RemaEngine/Engine/Layer.cpp
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-04-02
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
#include <remapch.h>
#include <RemaEngine/Engine/Layer.h>

namespace RemaEngine
{
    Layer::Layer(const std::string& a_sLayerName)
        : m_sLayerName(a_sLayerName)
    {

    }

    Layer::~Layer()
    {

    }
}
