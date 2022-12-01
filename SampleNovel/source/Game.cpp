#include <remapch.h>
#include <RemaEngine/RemaEngine.h>

class Game : public RemaEngine::Engine
{
public:
    Game()
    {

    }

    ~Game()
    {

    }
};

RemaEngine::Engine* RemaEngine::CreateApplication()
{
    return new Game();
}

