#ifndef REMA_BUFFERLAYOUT_H
#define REMA_BUFFERLAYOUT_H

namespace RemaEngine
{

    enum class ShaderDataType
    {
        None = 0,
        Float, Float2, Float3, Float4,
        Mat3, Mat4,
        Int, Int2, Int3, Int4,
        Bool
    };

    static uint32_t ShaderDataTypeSize(ShaderDataType a_stShaderDataType)
    {
        switch (a_stShaderDataType)
        {
            case ShaderDataType::Float:     return 4;
            case ShaderDataType::Float2:    return 4 * 2;
            case ShaderDataType::Float3:    return 4 * 3;
            case ShaderDataType::Float4:    return 4 * 4;
            case ShaderDataType::Mat3:      return 4 * 3 * 3;
            case ShaderDataType::Mat4:      return 4 * 4 * 4;
            case ShaderDataType::Int:       return 4;
            case ShaderDataType::Int2:      return 4 * 2;
            case ShaderDataType::Int3:      return 4 * 3;
            case ShaderDataType::Int4:      return 4 * 4;
            case ShaderDataType::Bool:      return 1;
        }

        REMA_CORE_ASSERT(false, "Illigal shader data type");
        return 0;
    }

    struct BufferElement
    {
        std::string m_sName;
        ShaderDataType m_stShaderDataType;

        uint32_t m_unOffset;
        uint32_t m_unSize;

        bool m_bNormolized;

        BufferElement() {}
        BufferElement(ShaderDataType a_stShaderDataType, const std::string& a_sName, bool a_bNormolized=false)
            : m_sName(a_sName), m_stShaderDataType(a_stShaderDataType),
            m_unOffset(0), m_unSize(ShaderDataTypeSize(a_stShaderDataType)), m_bNormolized(a_bNormolized)
        {
        }

        uint32_t GetComponentCount() const;

    };

    class BufferLayout
    {
    private:
        std::vector<BufferElement> m_arrElements;
        uint32_t m_unStride = 0;

    private:
        void CalculateOffsetsAndStride();

    public:
        BufferLayout() {}
        BufferLayout(const std::initializer_list<BufferElement>& a_arrElements) 
            : m_arrElements(a_arrElements)
        {
            CalculateOffsetsAndStride();
        }

        inline uint32_t GetStride() const { return m_unStride; }
        const std::vector<BufferElement>& GetElements() const { return m_arrElements; }

        std::vector<BufferElement>::iterator begin() { return m_arrElements.begin(); }
        std::vector<BufferElement>::iterator end() { return m_arrElements.end(); }
        std::vector<BufferElement>::const_iterator begin() const { return m_arrElements.begin(); }
        std::vector<BufferElement>::const_iterator end() const { return m_arrElements.end(); }
    };
}

#endif // !REMA_BUFFERLAYOUT_H
