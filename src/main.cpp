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
const int FRAME_RATE = 120;
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
    SDL_Window* window = create_window((char*)"sim", WIDTH, HEIGHT);
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
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);  // White background

    // Set up orthographic projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, WIDTH, HEIGHT, 0.0, -1.0, 1.0);  // Maps window coordinates (top-left origin)
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    Body planet1(5.972e24, Vec3(random_float(0.0, WIDTH), HEIGHT / 2 + random_float(0.0, 100.0), 0), Vec3(random_float(0.0, 15.0), 0.0, 0.0), 100, 100);
    planet1.set_gravity(gravity);



    bool done = false;
    Uint64 NOW = SDL_GetPerformanceCounter();
    Uint64 LAST = 0;
    float deltaTime = 0;

    // Simulation loop
    while (!done) {
        // Time step calculation
        LAST = NOW;
        NOW = SDL_GetPerformanceCounter();
        deltaTime = (float)((NOW - LAST) * 1000 / (float)SDL_GetPerformanceFrequency()) / 1000.0f;  // Convert to seconds

        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);


        planet1.update_pos(deltaTime);
        check_collision(planet1, WIDTH, HEIGHT, planet1.width, planet1.height);
        render_body(planet1, 155, 155, 155); 

        // Swap buffers to display the rendered image
        SDL_GL_SwapWindow(window);

        // SDL Event handling (e.g., for closing the window)
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }
        }

        // Delay to maintain the frame rate
        SDL_Delay(1000 / FRAME_RATE);
    }

    // Cleanup
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
