// renderer.hpp
#ifndef RENDERER_HPP
#define RENDERER_HPP

#define STANDARD_WIDTH 640
#define STANDARD_HEIGHT 480
#include <SDL.h>
#include "body.hpp"

SDL_Renderer* create_renderer(SDL_Window* window);
SDL_Window* create_window(char* window_name, int width = STANDARD_WIDTH, int height = STANDARD_HEIGHT);
void render_body(SDL_Renderer* renderer, Body body, int radius);
int clean(SDL_Window* window, SDL_Renderer* renderer);


#endif
