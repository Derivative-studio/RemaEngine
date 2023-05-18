#ifndef REMA_SHADER_H
#define REMA_SHADER_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <EASTL/string.h>

namespace RemaEngine
{
    class Shader
    {
    private:
        uint32_t m_nRendererID;

    public:
        Shader(const std::string& a_sVertexSrc, const std::string& a_sFragmentSrc);
        ~Shader();

        void Bind() const;
        void Unbind() const;

        void UploadUniformMat4(const eastl::string& a_sUniformName, const glm::mat4& a_mtxMatrix);
    };
}

#endif // !REMA_SHADER_H
