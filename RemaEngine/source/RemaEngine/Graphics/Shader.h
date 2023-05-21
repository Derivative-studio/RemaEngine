#ifndef REMA_SHADER_H
#define REMA_SHADER_H

#include <EASTL/string.h>

namespace RemaEngine
{
    class Shader
    {
    public:
        virtual ~Shader() = default;

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static Shader* Create(const eastl::string& a_sVertexSrc, const eastl::string& a_sFragmentSrc);
    };
}

#endif // !REMA_SHADER_H
