#include "remapch.h"
#include "RemaEngine/Graphics/VertexArray.h"
#include "RemaEngine/Graphics/Renderer.h"
#include "RemaEngine/Graphics/OpenGL/OpenGLVertexArray.h"

namespace RemaEngine
{
    ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: REMA_CORE_ASSERT(false, "This renderer api is not supported for now"); return nullptr;
            case RendererAPI::API::OpenGL: return eastl::make_shared<OpenGLVertexArray>();
            case RendererAPI::API::DirectX: REMA_CORE_ASSERT(false, "DirectX renderer API is not supported for now");
        }

        REMA_CORE_ASSERT(false, "Unknown renderer API");
        return nullptr;
    }

}