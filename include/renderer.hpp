// renderer.hpp
#ifndef RENDERER_HPP
#define RENDERER_HPP

#define STANDARD_WIDTH 640
#define STANDARD_HEIGHT 480
#include <SDL.h>


SDL_Renderer* create_renderer(SDL_Window* window);
SDL_Window* create_window(char* window_name, int width = STANDARD_WIDTH, int height = STANDARD_HEIGHT);
int clean(SDL_Window* window, SDL_Renderer* renderer);


#endif
