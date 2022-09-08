#ifndef REMA_ENTRY_POINT_H
#define REMA_ENTRY_POINT_H

#ifdef REMA_WIN

extern RemaEngine::Engine* RemaEngine::CreateApplication();

int main(int argc, char** argv)
{
    auto app = RemaEngine::CreateApplication();
    app->Run();
    delete app;
}

#endif // REMA_WIN

#endif // !REMA_ENTRY_POINT_H
