// renderer.cpp

#include "renderer.hpp"
#include "body.hpp"
#include <SDL.h>
#include <unistd.h>
#include <GL/gl.h>
#include <iostream>

const float SCALE_FACTOR = 1e6f;  // Example: 1 pixel = 1 million meters

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


// Render a filled circle in OpenGL
void drawFilledCircleGL(float cx, float cy, float r, int num_segments) {
    //glColor3f(1.0f, 1.0f, 1.0f);  // Set color to black
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);  // Center of the circle
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);  // Current angle
        float x = r * cosf(theta);  // X component
        float y = r * sinf(theta);  // Y component
        glVertex2f(x + cx, y + cy);  // Position vertex
    }
    // printf("cx: %f, cy: %f, r: %f, segments: %d\n", cx, cy, r, num_segments);
    glEnd();
}

void render_body(Body body, float red, float green, float blue) {
    Vec3 pos = body.get_pos();
    glColor3f(red, green, blue);
    drawFilledCircleGL(pos.x, pos.y, body.width / 2, 50);
}

void render_body_single(SDL_Renderer* renderer, Body body, int radius) {
    Vec3 pos = body.get_pos();
    // draw_circle(renderer, pos[0], pos[1], radius);
    drawFilledCircleGL(pos.x, pos.y, radius, 50);
    drawFilledCircleGL(pos.x, pos.y, body.width / 2, 50);
}


void render_bodies(Body& sun, Body& earth, Body& mars) {
    Vec3 pos_sun = sun.get_pos();
    Vec3 pos_earth = earth.get_pos();
    Vec3 pos_mars = mars.get_pos();

    // Apply scaling to positions
    Vec3 scaled_pos_sun = pos_sun.div(SCALE_FACTOR);
    Vec3 scaled_pos_earth = pos_earth.div(SCALE_FACTOR);
    Vec3 scaled_pos_mars = pos_mars.div(SCALE_FACTOR);
    

    printf("Sun position: %f, %f\n", scaled_pos_sun.x, scaled_pos_sun.y);
    printf("Earth position: %f, %f\n", scaled_pos_earth.x, scaled_pos_earth.y);
    printf("Mars position: %f, %f\n", scaled_pos_mars.x, scaled_pos_mars.y);


    // Draw the sun and planets with their respective sizes
    drawFilledCircleGL(scaled_pos_sun.x, scaled_pos_sun.y, 50.0f, 50);  // Sun with 50 pixels radius
    drawFilledCircleGL(scaled_pos_earth.x, scaled_pos_earth.y, 10.0f, 50);  // Earth with 10 pixels radius
    drawFilledCircleGL(scaled_pos_mars.x, scaled_pos_mars.y, 5.0f, 50);  // Mars with 5 pixels radius
}
