#include "body.hpp"
#include "vec3.hpp"
#include "collision.hpp"
#include "renderer.hpp"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <GL/gl.h>  // Include OpenGL header for GL functions
#include <stdio.h>
#include <unistd.h>

#define WIDTH 800
#define HEIGHT 600
const int FRAME_RATE = 60;
const int FRAME_DELAY = 1000 / FRAME_RATE;
float gravity = 9.8f;  // Gravity value

float random_float(float a, float b) {
    float random = ((float) rand()) / (float) RAND_MAX;
    float diff = b - a;
    float r = random * diff;
    return a + r;
}

int main(void) {
    // Create SDL Window
    SDL_Window* window = create_window("Three body problem", WIDTH, HEIGHT);
    SDL_Renderer* renderer = create_renderer(window);

    // Initialize OpenGL context for rendering
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        printf("SDL could not create OpenGL context! SDL Error: %s\n", SDL_GetError());
        return -1;
    }

    // Set up the viewport for OpenGL
    glViewport(0, 0, WIDTH, HEIGHT);

    // Set the background color (white in this case)
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);  // White background

    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);  // Map window coordinates to OpenGL coordinates
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Create body
    Body planet1(5.972e24, Vec3(random_float(0.0, WIDTH), HEIGHT / 2 + random_float(0.0, -200.0), 0), Vec3(random_float(0.0, 15.0), 0.0, 0.0), 50, 20);
    Body planet2(5.972e24, Vec3(random_float(0.0, WIDTH), HEIGHT / 2 + random_float(0.0, -400.0), 0), Vec3(random_float(0.0, 15.0), 0.0, 0.0), 50, 20);
    Body planet3(5.972e24, Vec3(random_float(0.0, WIDTH), HEIGHT / 2 + random_float(0.0, -300.0), 0), Vec3(random_float(0.0, 15.0), 0.0, 0.0), 50, 20);
    planet1.set_gravity(gravity);
    planet2.set_gravity(gravity);
    planet3.set_gravity(gravity);

    bool is_running = true;
    SDL_Event event;
    Uint32 last_frame_time = SDL_GetTicks();

    while (is_running) {
        Uint32 frame_start = SDL_GetTicks();
        Uint32 current_frame_time = SDL_GetTicks();
        float time_scale = 6.0f;
        float delta_time = (current_frame_time - last_frame_time) / 1000.0f * time_scale;
        last_frame_time = current_frame_time;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                is_running = false;
            } else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE) {
                is_running = false;
            }
        }

        // Clear OpenGL buffers for rendering
        glClear(GL_COLOR_BUFFER_BIT);

        // Update the position of the planet
        planet1.update_pos(delta_time);
        planet2.update_pos(delta_time);
        planet3.update_pos(delta_time);

        check_collision(planet1, WIDTH, HEIGHT, 20, 20);
        check_collision(planet2, WIDTH, HEIGHT, 20, 20);
        check_collision(planet3, WIDTH, HEIGHT, 20, 20);

        // Render the planet using OpenGL
        render_body(renderer, planet1, 20);
        render_body(renderer, planet2, 20);
        render_body(renderer, planet3, 20);

        // Swap OpenGL buffers to display the result
        SDL_GL_SwapWindow(window);

        // Frame delay to maintain consistent FPS
        Uint32 frame_time = SDL_GetTicks() - frame_start;
        if (FRAME_DELAY > frame_time) {
            SDL_Delay(FRAME_DELAY - frame_time);
        }
    }

    // Clean up OpenGL context and SDL
    SDL_GL_DeleteContext(glContext);
    clean(window, renderer);
    return 0;
}

