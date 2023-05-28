#include <remapch.h>
#include <RemaEngine/Graphics/OpenGL/OpenGLIndexBuffer.h>

#include <glad/glad.h>


namespace RemaEngine
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(uint32_t* a_unpIndices, uint32_t a_unCount)
        :m_unCount(a_unCount)
    {
        REMA_PROFILE_FUNCTION();

        glCreateBuffers(1, &m_unRendererID);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_unRendererID);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, a_unCount * sizeof(uint32_t), a_unpIndices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        REMA_PROFILE_FUNCTION();

        glDeleteBuffers(1, &m_unRendererID);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_unRendererID);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        REMA_PROFILE_FUNCTION();

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
