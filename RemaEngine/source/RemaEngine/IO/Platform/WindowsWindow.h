#ifndef REMA_WINDOWSWINDOW_H
#define REMA_WINDOWSWINDOW_H

#include <RemaEngine/IO/Window.h>
#include <GLFW/glfw3.h>

namespace RemaEngine
{
    class WindowsWindow : public Window
    {
        struct WindowData
        {
            std::string m_sTitle;

            uint32_t m_u32Width;
            uint32_t m_u32Height;

            bool VSync;
            fnEventCallback m_fnEventCallback;
        };

        GLFWwindow* m_stGLFWWindow;
        WindowData m_stWndwData;

    private:
        virtual void Init(const WindowProps& a_stWndwProps);
        virtual void Shutdown();

    public:
        WindowsWindow(const WindowProps& a_stWndwProps);
        virtual ~WindowsWindow();

        void OnUpdate() override;
        void SetEventCallback(const fnEventCallback& a_stCallback) override { m_stWndwData.m_fnEventCallback = a_stCallback; }
        void SetVSync(bool a_bEnabled) override;
        bool IsVSync() const override;

        inline virtual void* GetNativeWindow() const { return m_stGLFWWindow; }

        uint32_t GetWidth() const override { return m_stWndwData.m_u32Width; }
        uint32_t GetHeight() const override { return m_stWndwData.m_u32Height; }

    };
}

#endif // !REMA_WINDOWSWINDOW_H

