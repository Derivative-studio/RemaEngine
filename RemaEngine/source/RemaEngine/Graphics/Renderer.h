#ifndef REMA_RENDERER_H
#define REMA_RENDERER_H

namespace RemaEngine
{
    enum class RendererAPI
    {
        None = 0,
        OpenGL = 1,
        DirectX = 2
    };

    class Renderer
    {
    private:
        static RendererAPI sm_enRendererAPI;

    public:
        inline static RendererAPI GetAPI() { return sm_enRendererAPI; }

    };

}

#endif // !REMA_RENDERER_H
