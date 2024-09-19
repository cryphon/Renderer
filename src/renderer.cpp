// renderer.cpp

#include "renderer.hpp"
#include "body.hpp"
#include <SDL.h>
#include <unistd.h>
#include <GL/gl.h>
#include <iostream>


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
    glColor3f(0.0f, 0.0f, 0.0f);  // Set color to black
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(cx, cy);  // Center of the circle
    for (int i = 0; i <= num_segments; i++) {
        float theta = 2.0f * 3.1415926f * float(i) / float(num_segments);  // Current angle
        float x = r * cosf(theta);  // X component
        float y = r * sinf(theta);  // Y component
        glVertex2f(x + cx, y + cy);  // Position vertex
    }
    printf("cx: %f, cy: %f, r: %f, segments: %d\n", cx, cy, r, num_segments);
    glEnd();
}

void render_body(Body body) {
    Vec3 pos = body.get_pos();
    drawFilledCircleGL(pos.x, pos.y, body.width / 2, 50);
}




