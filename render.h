#ifndef RENDER_H
#define RENDER_H

#include <SDL2/SDL.h>
#include "p_math.h"

#define CIRCLE_ITERATIONS 100
#define METERS_IN_WINDOW 20


int get_pixels_per_meter(SDL_Window* win);
void draw_circle(SDL_Window* win, SDL_Renderer* r, struct vec3 pos, real radius);


#endif