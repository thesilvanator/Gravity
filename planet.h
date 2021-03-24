#ifndef PLANET_H
#define PLANET_H

#include "p_math.h"

#define TOLERANCE 1.0f*10e-34

struct planet {
	real radius;
	real mass;

	struct vec3 position;
	struct vec3 velocity;
	struct vec3 acceleration;
};

struct planet create_planet(real radius, real mass, struct vec3 pos, struct vec3 vel, struct vec3 accel);


#endif