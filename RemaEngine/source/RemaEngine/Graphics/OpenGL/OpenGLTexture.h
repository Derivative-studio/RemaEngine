/**
 * @file RemaEngine/Graphics/OpenGL/OpenGLTexture.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-21
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
#ifndef REMA_OPENGLTEXTURE_H
#define REMA_OPENGLTEXTURE_H

#include "RemaEngine/Graphics/Texture.h"

namespace RemaEngine
{
    class OpenGLTexture2D : public Texture2D
    {
    private:
        eastl::string m_sPath;

        uint32_t m_unWidth;
        uint32_t m_unHeight;
        uint32_t m_unRendererID;

    public:
        OpenGLTexture2D(const eastl::string& a_sPath);
        ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return m_unWidth; }
        virtual uint32_t GetHeight() const override { return m_unHeight; }
        virtual uint32_t GetRendererID() const override { return m_unRendererID; }
        virtual eastl::string GetPath() const override { return m_sPath; }

        virtual void Bind(uint32_t m_unSlot) const override;

    };
}

#endif // !REMA_OPENGLTEXTURE_H
