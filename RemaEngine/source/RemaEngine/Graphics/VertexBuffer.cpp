#include <remapch.h>
#include <RemaEngine/Graphics/VertexBuffer.h>

#include <RemaEngine/Graphics/Renderer.h>
#include <RemaEngine/Graphics/OpenGL/OpenGLVertexBuffer.h>

namespace RemaEngine
{
    VertexBuffer* VertexBuffer::Create(float* a_fpVertices, uint32_t a_nSize)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: REMA_CORE_ASSERT(false, "Not supported for now"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLVertexBuffer(a_fpVertices, a_nSize);
            case RendererAPI::API::DirectX: REMA_CORE_ASSERT(false, "DirectX currently not supported"); return nullptr;
        }

        REMA_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
};
