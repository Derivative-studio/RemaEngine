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
        REMA_LOG_APP_INFO("ExampleLayer::Update");
    }

    void OnEvent(RemaEngine::Event& a_stEvent) override
    {
        REMA_LOG_APP_TRACE("{0}", a_stEvent);
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

