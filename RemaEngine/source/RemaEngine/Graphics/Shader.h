/**
 * @file RemaEngine/Graphics/Shader.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-05-22
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
#ifndef REMA_SHADER_H
#define REMA_SHADER_H

namespace RemaEngine
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        virtual const eastl::string& GetName() const = 0;

        static ref<Shader> Create(const eastl::string& a_sFilepath);
        static ref<Shader> Create(const eastl::string& a_sName, const eastl::string& a_sVertexSrc, const eastl::string& a_sFragmentSrc);

    };
}

#endif // !REMA_SHADER_H
