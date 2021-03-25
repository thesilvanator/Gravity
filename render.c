#include "render.h"

#include <SDL2/SDL.h>
#include <math.h>
#include "planet.h"
#include "p_math.h"

int get_pixels_per_meter(SDL_Window *win) {
	int w, h;
	SDL_GL_GetDrawableSize(win, &w, &h);

	w /= 2 * METERS_IN_WINDOW;
	return w;
}

struct vec3 convert_vec_to_screen(SDL_Window* win, struct vec3 vec) {
	int w, h;
	int ratio = get_pixels_per_meter(win);
	SDL_GL_GetDrawableSize(win, &w, &h);

	struct vec3 new_vec = zero_vec();
	new_vec.x = (vec.x * ratio) + w/2;
	new_vec.y =  h/2 - (vec.y * ratio);
	new_vec.z = vec.z;


	return new_vec;
}

void draw_circle(SDL_Window* win, SDL_Renderer* r, struct vec3 pos, real radius) {
	int w, h;
	int x, y;
	int ratio = get_pixels_per_meter(win);

	SDL_GL_GetDrawableSize(win, &w, &h);

	x = (pos.x * ratio) + w/2;
	y =  h/2 - (pos.y * ratio);

	double last_x = (radius*ratio);
	double last_y = 0;

	
	for(int i = 0; i <= CIRCLE_ITERATIONS; i++) {
		double theta = (double)i * (double)(2*M_PI/CIRCLE_ITERATIONS);
		double this_x, this_y;

		this_x = (cos(theta)*radius*ratio);
		this_y = (sin(theta)*radius*ratio);

		SDL_RenderDrawLine(r, (int)last_x + x, (int)last_y + y, (int)this_x + x, (int)this_y + y);

		last_x = this_x;
		last_y = this_y;
	}
}

void draw_velocity_arrows(SDL_Window* win, SDL_Renderer* r, struct planet p[], unsigned int count) {
	int w, h;
	int ratio = get_pixels_per_meter(win);

	SDL_GL_GetDrawableSize(win, &w, &h);

	for(unsigned int i = 0; i < count; i++){

		struct vec3 arrow_dir = normalize(p[i].velocity);
		struct vec3 arrow_start = add_vectors(p[i].position, scalar_product(arrow_dir, p[i].radius));
		struct vec3 arrow_end = add_vectors(arrow_start, scalar_product(arrow_dir, length(p[i].velocity)));

		// draw line part
		struct vec3 start_vec = convert_vec_to_screen(win, arrow_start);
		struct vec3 end_vec = convert_vec_to_screen(win, arrow_end);

		SDL_RenderDrawLine(r, start_vec.x, start_vec.y, end_vec.x, end_vec.y);

		// draw left tip part
		arrow_start = arrow_end;

		real left_angle = 3*(real)M_PI_4;
		real right_angle = 5*(real)M_PI_4;

		real new_x, new_y;

		// x' = xcos - ysin
		// y' = xsin + ycos
		new_x = cos(left_angle)*arrow_dir.x - sin(left_angle)*arrow_dir.y;
		new_y = sin(left_angle)*arrow_dir.x + cos(left_angle)*arrow_dir.y;

		arrow_end = scalar_product(create_vec(new_x, new_y, 0), 0.25);
		arrow_end = add_vectors(arrow_start, arrow_end);

		start_vec = convert_vec_to_screen(win, arrow_start);
		end_vec = convert_vec_to_screen(win, arrow_end);
		SDL_RenderDrawLine(r, start_vec.x, start_vec.y, end_vec.x, end_vec.y);

		// draw right tip part
		new_x = cos(right_angle)*arrow_dir.x - sin(right_angle)*arrow_dir.y;
		new_y = sin(right_angle)*arrow_dir.x + cos(right_angle)*arrow_dir.y;

		arrow_end = scalar_product(create_vec(new_x, new_y, 0), 0.25);
		arrow_end = add_vectors(arrow_start, arrow_end);

		start_vec = convert_vec_to_screen(win, arrow_start);
		end_vec = convert_vec_to_screen(win, arrow_end);
		SDL_RenderDrawLine(r, start_vec.x, start_vec.y, end_vec.x, end_vec.y);

	}
}