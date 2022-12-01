#include "RemaEngine/Engine/Engine.h"
#include <RemaEngine/Event/ApplicationEvent.h>
#include <RemaEngine/System/Logger.h>

namespace RemaEngine
{
    Engine::Engine()
    {

    }

    Engine::~Engine()
    {

    }

    void Engine::Run()
    {
        WindowResizedEvent e(1280, 720);
        if (e.IsInCategory(ApplicationEventCategory))
        {
            REMA_LOG_CORE_TRACE(e);
        }
        if (e.IsInCategory(InputEventCategory))
        {
            REMA_LOG_CORE_TRACE(e);
        }
        while (true);
    }
}

