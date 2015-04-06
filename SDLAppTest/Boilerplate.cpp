#include "Boilerplate.h"

#include <stdio.h>
#include <GL/glew.h>

using namespace Boilerplate;

App Boilerplate::start(int w, int h, const char *title) {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    
    App app;
    
    app.window = SDL_CreateWindow(title,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  SDL_WINDOWPOS_UNDEFINED,
                                  w,
                                  h,
                                  SDL_WINDOW_OPENGL);
    
    if (!app.window) {
        printf("Could not create window: %s\n", SDL_GetError());
        exit(1);
    }
    
    Uint32 rendererFlags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
    
    app.renderer = SDL_CreateRenderer(app.window,
                                      -1,
                                      rendererFlags);
    
    GLenum glew_status = glewInit();
    if (glew_status != GLEW_OK) {
        fprintf(stderr, "Error: %s\n", glewGetErrorString(glew_status));
        exit(1);
    }
    
    return app;
}

void Boilerplate::stop(const App& app) {
    SDL_DestroyWindow(app.window);
    SDL_Quit();
}

float now() {
    uint ticks = SDL_GetTicks();
    return ticks / 1000.0f;
}

void Boilerplate::loop(const App& app) {
    
    float lastT = now();
    
    while(true) {
        SDL_Event e;
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                return;
            }
            else if(e.type == SDL_KEYDOWN) {
                if(e.key.keysym.sym == SDLK_ESCAPE && app.exitOnEsc) {
                    return;
                }
                else if(app.onKeyDown) {
                    app.onKeyDown(e.key.keysym.sym);
                }
            }
            else if(e.type == SDL_KEYUP && app.onKeyUp) {
                app.onKeyUp(e.key.keysym.sym);
            }
        }
        
        float t = now();
        float deltaTime = t - lastT;
        lastT = t;
        
        if(app.tick) {
            app.tick(deltaTime);
        }
        
        if(app.render) {
            app.render();
        }
        
        SDL_RenderPresent(app.renderer);
        SDL_Delay(10);
    }
}
