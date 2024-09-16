// renderer.cpp

#include "renderer.hpp"
#include "body.hpp"
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



void draw_circle(SDL_Renderer* renderer, int32_t centreX, int32_t centreY, int32_t radius) {
    const int32_t diameter = (radius * 2);

    int32_t x = (radius - 1);
    int32_t y = 0;
    int32_t tx = 1;
    int32_t ty = 1;
    int32_t error = (tx - diameter);

    while (x >= y)
    {
        // Each of the following renders an octant of the circle
        SDL_RenderDrawPoint(renderer, centreX + x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX + x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY - y);
        SDL_RenderDrawPoint(renderer, centreX - x, centreY + y);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX + y, centreY + x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY - x);
        SDL_RenderDrawPoint(renderer, centreX - y, centreY + x);

        if (error <= 0)
        {
            ++y;
            error += ty;
            ty += 2;
        }

        if (error > 0)
        {
            --x;
            tx += 2;
            error += (tx - diameter);
        }

    }
}


void render_body(SDL_Renderer* renderer, Body body, int radius) {
    Vec3 pos = body.get_pos();
    draw_circle(renderer, pos[0], pos[1], radius);
}




