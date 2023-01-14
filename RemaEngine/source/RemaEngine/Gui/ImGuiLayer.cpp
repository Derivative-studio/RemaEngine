#include <remapch.h>
#include <RemaEngine/Gui/ImGuiLayer.h>
#include <RemaEngine/Engine/Engine.h>
#include <RemaEngine/Engine/EngineDefinitions.h>
#include <RemaEngine/Platform/OpenGL/imgui_impl_opengl3.h>

#include <imgui.h>

// Temp
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace RemaEngine
{

    ImGuiLayer::ImGuiLayer()
        : Layer("ImGuiLayer")
    {
    }

    ImGuiLayer::~ImGuiLayer()
    {
    }

    void ImGuiLayer::OnAttach()
    {
        ImGui::CreateContext();
        ImGui::StyleColorsDark();

        ImGuiIO& io = ImGui::GetIO();
        io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
        io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

        // TEMPORARY: should eventually use Hazel key codes
        io.KeyMap[ImGuiKey_Tab] = GLFW_KEY_TAB;
        io.KeyMap[ImGuiKey_LeftArrow] = GLFW_KEY_LEFT;
        io.KeyMap[ImGuiKey_RightArrow] = GLFW_KEY_RIGHT;
        io.KeyMap[ImGuiKey_UpArrow] = GLFW_KEY_UP;
        io.KeyMap[ImGuiKey_DownArrow] = GLFW_KEY_DOWN;
        io.KeyMap[ImGuiKey_PageUp] = GLFW_KEY_PAGE_UP;
        io.KeyMap[ImGuiKey_PageDown] = GLFW_KEY_PAGE_DOWN;
        io.KeyMap[ImGuiKey_Home] = GLFW_KEY_HOME;
        io.KeyMap[ImGuiKey_End] = GLFW_KEY_END;
        io.KeyMap[ImGuiKey_Insert] = GLFW_KEY_INSERT;
        io.KeyMap[ImGuiKey_Delete] = GLFW_KEY_DELETE;
        io.KeyMap[ImGuiKey_Backspace] = GLFW_KEY_BACKSPACE;
        io.KeyMap[ImGuiKey_Space] = GLFW_KEY_SPACE;
        io.KeyMap[ImGuiKey_Enter] = GLFW_KEY_ENTER;
        io.KeyMap[ImGuiKey_Escape] = GLFW_KEY_ESCAPE;
        io.KeyMap[ImGuiKey_A] = GLFW_KEY_A;
        io.KeyMap[ImGuiKey_C] = GLFW_KEY_C;
        io.KeyMap[ImGuiKey_V] = GLFW_KEY_V;
        io.KeyMap[ImGuiKey_X] = GLFW_KEY_X;
        io.KeyMap[ImGuiKey_Y] = GLFW_KEY_Y;
        io.KeyMap[ImGuiKey_Z] = GLFW_KEY_Z;

        ImGui_ImplOpenGL3_Init("#version 410");
    }

    void ImGuiLayer::OnDetach()
    {

    }

    void ImGuiLayer::OnUpdate()
    {
        ImGuiIO& io = ImGui::GetIO();
        Engine& app = Engine::GetInstance();
        io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

        float time = (float)glfwGetTime();
        io.DeltaTime = m_fTime > 0.0f ? (time - m_fTime) : (1.0f / 60.0f);
        m_fTime = time;

        ImGui_ImplOpenGL3_NewFrame();
        ImGui::NewFrame();

        static bool show = true;
        ImGui::ShowDemoWindow(&show);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }

    void ImGuiLayer::OnEvent(Event& a_stEvent)
    {
        EventDispatcher dispatcher(a_stEvent);

        dispatcher.Dispatch<MouseButtonPressedEvent>(REMA_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
        dispatcher.Dispatch<MouseButtonReleasedEvent>(REMA_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
        dispatcher.Dispatch<MouseMovedEvent>(REMA_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
        dispatcher.Dispatch<MouseScrolledEvent>(REMA_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
        dispatcher.Dispatch<KeyPressedEvent>(REMA_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
        dispatcher.Dispatch<KeyReleasedEvent>(REMA_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
        dispatcher.Dispatch<KeyTypedEvent>(REMA_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
        dispatcher.Dispatch<WindowResizedEvent>(REMA_BIND_EVENT_FN(ImGuiLayer::OnWindowResizedEvent));
    }

    bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& a_stEvent)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[a_stEvent.GetMouseKeyCode()] = true;

        return false;
    }

    bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& a_stEvent)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseDown[a_stEvent.GetMouseKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& a_stEvent)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MousePos = ImVec2(a_stEvent.GetX(), a_stEvent.GetY());

        return false;
    }

    bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& a_stEvent)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.MouseWheelH += a_stEvent.GetXOffset();
        io.MouseWheel += a_stEvent.GetYOffset();

        return false;
    }

    bool ImGuiLayer::OnWindowResizedEvent(WindowResizedEvent& a_stEvent)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.DisplaySize = ImVec2(a_stEvent.GetWidth(), a_stEvent.GetHeight());
        io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
        glViewport(0, 0, a_stEvent.GetWidth(), a_stEvent.GetHeight());

        return false;
    }

    bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& a_stEvent)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[a_stEvent.GetKeyCode()] = true;

        io.KeyCtrl = io.KeysDown[GLFW_KEY_LEFT_CONTROL || GLFW_KEY_RIGHT_CONTROL];
        io.KeyShift = io.KeysDown[GLFW_KEY_LEFT_SHIFT || GLFW_KEY_RIGHT_SHIFT];
        io.KeyAlt = io.KeysDown[GLFW_KEY_LEFT_ALT || GLFW_KEY_RIGHT_ALT];
        io.KeySuper = io.KeysDown[GLFW_KEY_LEFT_SUPER || GLFW_KEY_RIGHT_SUPER];

        return false;
    }

    bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& a_stEvent)
    {
        ImGuiIO& io = ImGui::GetIO();
        io.KeysDown[a_stEvent.GetKeyCode()] = false;

        return false;
    }

    bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& a_stEvent)
    {
        ImGuiIO& io = ImGui::GetIO();

        int keycode = a_stEvent.GetKeyCode();
        if (keycode > 0 && keycode < 0x10000) {
            io.AddInputCharacter((unsigned short)keycode);
        }

        return false;
    }

}

