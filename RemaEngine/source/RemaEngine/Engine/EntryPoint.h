/**
 * @file RemaEngine/Engine/EntryPoint.h
 * @author Nikita Kozlov (nyarstot@yandex.ru)
 * @date 2023-04-02
 * @copyright Copyright (c) 2023
 *
 * This file is part of RemaEngine.
 *
 * RemaEngine is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * RemaEngine is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 **/
#ifndef REMA_ENTRY_POINT_H
#define REMA_ENTRY_POINT_H

/**
 * The entry point impl header for RemaEngine applications.
 * Before start work with any other system, it's entry point
 * should be implemented here under relevant #ifdef directive.
 **/

#ifdef REMA_WIN

extern RemaEngine::Engine* RemaEngine::CreateApplication();

int main(int argc, char** argv)
{
    RemaEngine::Logger::Init();
    REMA_ENGINE_INFO("Initializing engine...");

    REMA_BEGIN_PROFILE_SESSION("Startup", "ProfileRemaProfile-Startup.json");
    auto app = RemaEngine::CreateApplication();
    REMA_END_PROFILE_SESSION();

    REMA_BEGIN_PROFILE_SESSION("Runtime", "RemaProfile-Runtime.json");
    app->Run();
    REMA_END_PROFILE_SESSION();

    REMA_BEGIN_PROFILE_SESSION("Shutdown", "RemaProfile-Shutdown.json");
    delete app;
    REMA_END_PROFILE_SESSION();
}

#endif // REMA_WIN

#endif // !REMA_ENTRY_POINT_H

