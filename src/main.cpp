// main.cpp
#include "body.hpp"
#include "vec3.hpp"
#include "renderer.hpp"
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600


int main(void) {

    // Window to be rendered to
    SDL_Window* window = create_window("Three body problem", WIDTH, HEIGHT);
    SDL_Renderer* renderer = create_renderer(window);


    Body planet(5.972e24, Vec3(50.0, 100.0, 0.0), Vec3(50.0, 1.3, 1.0));
    while(true) {
        SDL_Event event;
        if(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                break;
            }
        }

        Uint8 red = 255;
        Uint8 green = 255;
        Uint8 blue = 255;

        SDL_SetRenderDrawColor(renderer, red, green, blue, 255);
        SDL_RenderClear(renderer);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        render_body(renderer, planet, 20);
        SDL_RenderPresent(renderer);
        sleep(1);
    }

    Body earth(5.972e24, Vec3(1.4, 0.0, 0.0), Vec3(2.0, 1.3, 1.0));
    std::cout << "Initial Earth: ";
    earth.get_pos().print();

    earth.update_pos(1.0);

    std::cout << "New earth after 1 second: ";
    earth.get_pos().print();


    clean(window, renderer);
    return 0;
}
