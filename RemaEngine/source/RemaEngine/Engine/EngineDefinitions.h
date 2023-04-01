/**
 * @file RemaEngine/Engine/EngineDefinitions.h
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
#ifndef REMA_ENGINEDEFINITIONS_H
#define REMA_ENGINEDEFINITIONS_H

#define REMA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

#endif // !REMA_ENGINEDEFINITIONS_H
