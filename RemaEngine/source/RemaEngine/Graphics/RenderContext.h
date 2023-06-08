/**
 * @file RemaEngine/Graphics/RenderContext.h
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
#ifndef REMA_RENDERCONTEXT_H
#define REMA_RENDERCONTEXT_H

namespace RemaEngine
{
    class RenderContext
    {
    private:


    public:
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;

    };
}

#endif // !REMA_RENDERCONTEXT_H

