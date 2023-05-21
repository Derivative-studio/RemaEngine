#include "remapch.h"
#include "RemaEngine/Graphics/Shader.h"
#include "RemaEngine/Graphics/Renderer.h"
#include "RemaEngine/Graphics/OpenGL/OpenGLShader.h"

#include <glad/glad.h>

namespace RemaEngine
{
    Shader* Shader::Create(const eastl::string& a_sVertexSrc, const eastl::string& a_sFragmentSrc)
    {
        switch (Renderer::GetAPI())
        {
        case RendererAPI::API::None: REMA_CORE_ASSERT(false, "This renderer api is not supported for now"); return nullptr;
        case RendererAPI::API::OpenGL: return new OpenGLShader(a_sVertexSrc, a_sFragmentSrc);
        case RendererAPI::API::DirectX: REMA_CORE_ASSERT(false, "DirectX renderer API is not supported for now");
        }

        REMA_CORE_ASSERT(false, "Unknown renderer API");
        return nullptr;
    }

}
