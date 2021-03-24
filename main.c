#include <stdio.h>
#include <SDL2/SDL.h>

#include "p_math.h"
#include "planet.h"
#include "render.h"

#define PLANET_COUNT 3
#define TIME_RATIO 3


void update_forces(struct planet p[], int count) {
	for(int i = 0; i < count; i++) {
		struct vec3 forces = zero_vec();
		for(int j = 0; j < count; j++) {
			if(i == j)
				continue;
			// f = G*(m1*m2/r^2)
			struct vec3 direction = sub_vectors(p[j].position, p[i].position);
			real len = length(direction);

			// if planets too close, just don't add any force
			if(len < (real)(p[i].radius + p[j].radius)/2.0f)
				continue;

			real force = GRAV_CONST*((p[i].mass*p[j].mass)/(len*len));
			direction = normalize(direction);

			forces = add_vectors(forces, scalar_product(direction, force));
		}
		// a = f/m
		struct vec3 direction = normalize(forces);
		real accel = length(forces)/(real)p[i].mass;
		p[i].acceleration = scalar_product(direction, accel);
	}
}

void update_positions(struct planet p[], int count, double delta) {
	for(int i = 0; i < count; i++) {
		p[i].velocity = add_vectors(p[i].velocity, scalar_product(p[i].acceleration, (real)delta * TIME_RATIO));
		p[i].position = add_vectors(p[i].position, scalar_product(p[i].velocity, (real)delta * TIME_RATIO));
	}
}

void render(SDL_Window* win, SDL_Renderer* r, struct planet p[], int count) {
	SDL_SetRenderDrawColor(r, 255, 255, 255, SDL_ALPHA_OPAQUE);

	for(int i = 0; i < count; i++) {
		draw_circle(win, r, p[i].position, p[i].radius);
	}

	SDL_RenderPresent(r);

	// for(int i = 0; i < count; i++) {
	// 	printf("planet %d position x: %f, y: %f\n", i, p[i].position.x, p[i].position.y);
	// }

	// printf("planet distance: %f\n\n", length(sub_vectors(p[0].position, p[1].position)));

	// for(int i = 0; i < count; i++){
	// 	printf("planet %d acceleration:\n", i);
	// 	print_vec(p[i].acceleration);
	// }

	// printf("---------------------------------\n\n");
	// fflush(stdout);
}



int main(int argc, char const *argv[])
{
	struct planet p[PLANET_COUNT];
	//create_planet(size, mass, pos, vel, accel)
	p[0] = create_planet(.9, 50.0f, zero_vec(),zero_vec(),zero_vec());
	p[1] = create_planet(0.5, 25.0f, create_vec(5, -2, 0), create_vec(0, 0.5f,0), zero_vec());
	p[2] = create_planet(0.25, 10.0f, create_vec(-8, 5, 0), zero_vec(), zero_vec());


	// init SDL
	if(SDL_Init(SDL_INIT_EVERYTHING)) {
		fprintf(stderr,"error initing SDL");
		return 1;
	}

	SDL_Window* w;
	SDL_Renderer* r;

	if(SDL_CreateWindowAndRenderer(1280,720,SDL_WINDOW_OPENGL,&w,&r)) {
		fprintf(stderr,"error creating window or renderer");
		return 1;
	}

	SDL_SetRenderDrawColor(r,0,0,30,0);
	SDL_RenderClear(r);
	SDL_RenderPresent(r);


	int quit = 0;
	double total = 0;
	double delta_time = 0;
	uint32_t last_update = SDL_GetTicks();
	uint32_t now;
	while(!quit) {
		now = SDL_GetTicks();
		delta_time = (double)(now - last_update)/1000.0f;
		total += delta_time;
		last_update = now;
		
		// printf("\rdelta: %f, total: %f", delta_time, total);
		// fflush(stdout);

		update_forces(p,PLANET_COUNT);
		update_positions(p,PLANET_COUNT, delta_time);


		SDL_SetRenderDrawColor(r,0,0,30,0);
		SDL_RenderClear(r);
		SDL_Event event;
		while(SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT || (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE))
	    			quit = !quit;
		}
		render(w, r, p, PLANET_COUNT);
	}

	printf("Done.\n");
	SDL_DestroyWindow(w);
	SDL_Quit();
	return 0;
}



