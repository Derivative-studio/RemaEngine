#include "remapch.h"
#include <RemaEngine/Graphics/IndexBuffer.h>

#include <RemaEngine/Graphics/Renderer.h>
#include <RemaEngine/Graphics/OpenGL/OpenGLIndexBuffer.h>


namespace RemaEngine
{
    IndexBuffer* IndexBuffer::Create(uint32_t* a_npIndices, uint32_t a_nSize)
    {
        switch (Renderer::GetAPI())
        {
            case RendererAPI::API::None: REMA_CORE_ASSERT(false, "Not supported for now"); return nullptr;
            case RendererAPI::API::OpenGL: return new OpenGLIndexBuffer(a_npIndices, a_nSize);
            case RendererAPI::API::DirectX: REMA_CORE_ASSERT(false, "DirectX currently not supported"); return nullptr;
        }

        REMA_CORE_ASSERT(false, "Unknown RendererAPI");
        return nullptr;
    }
};
