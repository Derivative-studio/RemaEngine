/**
 * @file RemaEngine/Graphics/Texture.h
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
#ifndef REMA_TEXTURE_H
#define REMA_TEXTURE_H

namespace RemaEngine
{
    class Texture
    {
    public:
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;
        virtual uint32_t GetRendererID() const = 0;

        virtual void SetData(void* a_Data, uint32_t a_unSize) = 0;

        virtual eastl::string GetPath() const = 0;

        virtual void Bind(uint32_t a_unSlot = 0) const = 0;
        virtual void Unbind(uint32_t a_unSlot = 0) const = 0;

    };

    class Texture2D : public Texture
    {
    public:
        static ref<Texture2D> Create(uint32_t a_unWidth, uint32_t a_unHeight);
        static ref<Texture2D> Create(const eastl::string& a_sPath);


    };
}

#endif // !REMA_TEXTURE_H
