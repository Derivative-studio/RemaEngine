//#include <RemaEngine/RemaEngine.h>
//#include <RemaEngine/Graphics/OpenGL/OpenGLShader.h>
//#include <RemaEngine/Graphics/ShaderLibrary.h>
//#include <RemaEngine/Utils/MemoryUtils.h>
//#include <RemaEngine/Engine/EntryPoint.h>

#include "SampleNovel/GameLayer.h"

#include <RemaEngine/RemaEngine.h>
#include <RemaEngine/Engine/EntryPoint.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>

class Game : public RemaEngine::Engine
{
public:
    Game()
    {
        //PushLayer(new ExampleLayer());
        PushLayer(new GameLayer());
    }

    ~Game()
    {

    }
};

RemaEngine::Engine* RemaEngine::CreateApplication()
{
    return new Game();
}

