#ifndef REMA_SHADER_H
#define REMA_SHADER_H

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

    };
}

#endif // !REMA_SHADER_H
