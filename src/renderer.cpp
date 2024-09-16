// renderer.cpp

#include "renderer.hpp"
#include <SDL.h>
#include <unistd.h>


SDL_Renderer* create_renderer(SDL_Window* window) {
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(renderer == nullptr) {
        SDL_Log("Could not create a renderer: %s", SDL_GetError());\
        exit(1);
    }
    return renderer;

}

int clean(SDL_Window* window, SDL_Renderer* renderer) {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


SDL_Window* create_window(char* window_name, int width, int height) {
    // Window to be rendered to
    SDL_Window* window = NULL;

    if(SDL_Init(SDL_INIT_VIDEO) <0) {
        printf("[ERROR]: SDL could not initialize. SDL_Error %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow(window_name,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            width, height,
            SDL_WINDOW_OPENGL);
    return window;
}




    
