#include <remapch.h>
#include <RemaEngine/RemaEngine.h>

class ExampleLayer : public RemaEngine::Layer
{
public:
    ExampleLayer()
        : Layer("Example")
    {
    }

    void OnUpdate() override
    {
      
    }

    void OnEvent(RemaEngine::Event& a_stEvent) override
    {
        //REMA_APP_TRACE("{0}", a_stEvent);
        if (a_stEvent.GetEventType() == RemaEngine::EventType::KeyPressed) {
            RemaEngine::KeyPressedEvent& e = (RemaEngine::KeyPressedEvent&)a_stEvent;
            REMA_APP_TRACE("{0}", (char)e.GetKeyCode());
        }
    }
};

class Game : public RemaEngine::Engine
{
public:
    Game()
    {
        PushLayer(new ExampleLayer());
    }

    ~Game()
    {

    }
};

RemaEngine::Engine* RemaEngine::CreateApplication()
{
    return new Game();
}

