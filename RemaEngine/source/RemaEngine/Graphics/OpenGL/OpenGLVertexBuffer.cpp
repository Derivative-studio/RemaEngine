#include <remapch.h>
#include <RemaEngine/Graphics/OpenGL/OpenGLVertexBuffer.h>

#include <glad/glad.h>


namespace RemaEngine
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(float* a_fpVertices, uint32_t a_nSize)
    {
        REMA_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_unRendererID);
        glBindBuffer(GL_ARRAY_BUFFER, m_unRendererID);
        glBufferData(GL_ARRAY_BUFFER, a_nSize, a_fpVertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        REMA_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_unRendererID);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, m_unRendererID);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
