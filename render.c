#include "render.h"

#include <SDL2/SDL.h>
#include <math.h>

int get_pixels_per_meter(SDL_Window *win) {
	int w, h;
	SDL_GL_GetDrawableSize(win, &w, &h);

	w /= 2 * METERS_IN_WINDOW;
	return w;
}


void draw_circle(SDL_Window* win, SDL_Renderer* r, struct vec3 pos, real radius) {
	int w, h;
	int x, y;
	int ratio = get_pixels_per_meter(win);

	SDL_GL_GetDrawableSize(win, &w, &h);

	x = (pos.x * ratio) + w/2;
	y =  h/2 - (pos.y * ratio);


	double last_x = x + radius*ratio;
	double last_y = y;

	
	for(int i = 0; i <= CIRCLE_ITERATIONS; i++) {
		double theta = (double)i * (double)(2*M_PI/CIRCLE_ITERATIONS);
		double this_x, this_y;

		this_x = cos(theta)*radius*ratio + x;
		this_y = sin(theta)*radius*ratio + y;

		SDL_RenderDrawLine(r, (int)last_x, (int)last_y, (int)this_x, (int)this_y);

		last_x = this_x;
		last_y = this_y;
	}
}