// main.cpp
#include "body.hpp"
#include "vec3.hpp"
#include "collision.hpp"
#include "renderer.hpp"
#include <iostream>
#include <SDL.h>
#include <stdio.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600
const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;


float random_float(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int main(void) {

    // Window to be rendered to
    SDL_Window* window = create_window("Three body problem", WIDTH, HEIGHT);
    SDL_Renderer* renderer = create_renderer(window);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);


    Body planet1(5.972e24, Vec3(random_float(0, WIDTH), random_float(0, HEIGHT), 0.0), Vec3(random_float(0, 10), random_float(0, 10), 0.0));
    Body planet2(5.972e24, Vec3(random_float(0, WIDTH), random_float(0, HEIGHT), 0.0), Vec3(random_float(0, 10), random_float(0, 10), 0.0));
    Body planet3(5.972e24, Vec3(random_float(0, WIDTH), random_float(0, HEIGHT), 0.0), Vec3(random_float(0, 10), random_float(0, 10), 0.0));

    // Create sphere
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    render_body(renderer, planet1, 20);
    render_body(renderer, planet2, 20);
    render_body(renderer, planet3, 20);


    bool is_running = true;
    SDL_Event event;
    while(is_running) {
        Uint32 frame_start = SDL_GetTicks();


        while(SDL_PollEvent(&event)) {
            if(event.type == SDL_QUIT) {
                is_running = false;
                break;
            }
            // Handle keypresses
            if (event.type == SDL_KEYDOWN) {
                switch (event.key.keysym.sym) {
                    case SDLK_ESCAPE:  // Press ESC to close the window
                        is_running = false;
                        break;
                    default:
                        break;
                }
            }
        }

        // Clear render
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Re-render object
        planet1.update_pos(1.0);
        planet2.update_pos(1.0);
        planet3.update_pos(1.0);
        check_collision(planet1, WIDTH, HEIGHT, 20, 20);
        check_collision(planet2, WIDTH, HEIGHT, 20, 20);
        check_collision(planet3, WIDTH, HEIGHT, 20, 20);
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        render_body(renderer, planet1, 20);
        render_body(renderer, planet2, 20);
        render_body(renderer, planet3, 20);
        SDL_RenderPresent(renderer);



        Uint32 frame_time = SDL_GetTicks() - frame_start;

        // If the frame finished too fast, delay the remainder to hit target frame rate
        if (FRAME_DELAY > frame_time) {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }


    clean(window, renderer);
    return 0;
}
