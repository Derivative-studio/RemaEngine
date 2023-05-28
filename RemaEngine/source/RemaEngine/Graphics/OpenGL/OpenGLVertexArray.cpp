#include "remapch.h"
#include "RemaEngine/Graphics/OpenGL/OpenGLVertexArray.h"

#include <glad/glad.h>

namespace RemaEngine
{
    static GLenum ShaderDataType2OGLBaseType(ShaderDataType m_stDataType)
    {
        switch (m_stDataType)
        {
        case RemaEngine::ShaderDataType::Float:     return GL_FLOAT;
        case RemaEngine::ShaderDataType::Float2:    return GL_FLOAT;
        case RemaEngine::ShaderDataType::Float3:    return GL_FLOAT;
        case RemaEngine::ShaderDataType::Float4:    return GL_FLOAT;
        case RemaEngine::ShaderDataType::Mat3:      return GL_FLOAT;
        case RemaEngine::ShaderDataType::Mat4:      return GL_FLOAT;
        case RemaEngine::ShaderDataType::Int:       return GL_INT;
        case RemaEngine::ShaderDataType::Int2:      return GL_INT;
        case RemaEngine::ShaderDataType::Int3:      return GL_INT;
        case RemaEngine::ShaderDataType::Int4:      return GL_INT;
        case RemaEngine::ShaderDataType::Bool:      return GL_BOOL;
        }

        REMA_CORE_ASSERT(false, "Illigal shader data type");
        return 0;
    }

    OpenGLVertexArray::OpenGLVertexArray()
    {
        REMA_PROFILE_FUNCTION();

        glCreateVertexArrays(1, &m_unRendererID);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        REMA_PROFILE_FUNCTION();

        glDeleteVertexArrays(1, &m_unRendererID);
    }

    void OpenGLVertexArray::Bind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindVertexArray(m_unRendererID);
    }

    void OpenGLVertexArray::Unbind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindVertexArray(0);
    }

    void OpenGLVertexArray::AddVertexBuffer(const eastl::shared_ptr<VertexBuffer>& a_pVertexBuffer)
    {
        REMA_CORE_ASSERT(a_pVertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout");

        glBindVertexArray(m_unRendererID);
        a_pVertexBuffer->Bind();

        uint32_t index = 0;
        const auto& layout = a_pVertexBuffer->GetLayout();
        for (const auto& element : layout) {
            glEnableVertexAttribArray(index);
            glVertexAttribPointer(index,
                element.GetComponentCount(),
                ShaderDataType2OGLBaseType(element.m_stShaderDataType),
                element.m_bNormolized ? GL_TRUE : GL_FALSE,
                layout.GetStride(),
                (const void*)element.m_unOffset);
            index++;
        }

        m_arrVertexBuffers.push_back(a_pVertexBuffer);
    }

    void OpenGLVertexArray::SetIndexBuffer(const eastl::shared_ptr<IndexBuffer>& a_pIndexBuffer)
    {
        glBindVertexArray(m_unRendererID);
        a_pIndexBuffer->Bind();
        m_pIndexBuffer = a_pIndexBuffer;
    }
}
