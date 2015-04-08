#pragma once

#include <GL/glew.h>
#include <SDL2/SDL.h>
#include <functional>

namespace Boilerplate {
    
    struct App {
        // User
        bool exitOnEsc = true;
        std::function<void (SDL_Keycode)> onKeyDown = nullptr;
        std::function<void (SDL_Keycode)> onKeyUp = nullptr;
        std::function<void (void)> render = nullptr;
        std::function<void (float dt)> tick = nullptr;
        
        // Internal
        SDL_Window *window;
        SDL_GLContext context;
        float totalTime = 0.0f;
    };
    
    App start(int w, int h, const char *title);
    void loop(const App& app);
    void stop(const App& app);
}
