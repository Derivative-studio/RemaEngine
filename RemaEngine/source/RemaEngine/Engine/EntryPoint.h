#ifndef REMA_ENTRY_POINT_H
#define REMA_ENTRY_POINT_H

#ifdef REMA_WIN

extern RemaEngine::Engine* RemaEngine::CreateApplication();

int main(int argc, char** argv)
{
    RemaEngine::Logger::Init();
    REMA_ENGINE_INFO("Init Engine");
    REMA_APP_TRACE("Init Client");

    auto app = RemaEngine::CreateApplication();
    app->Run();
    delete app;
}

#endif // REMA_WIN

#endif // !REMA_ENTRY_POINT_H

