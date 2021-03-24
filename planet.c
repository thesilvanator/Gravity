#include "planet.h"
#include "p_math.h"


struct planet create_planet(real radius, real mass, struct vec3 pos, struct vec3 vel, struct vec3 accel) {
	struct planet p;
	p.radius = radius;
	p.mass = mass;
	p.position = pos;
	p.velocity = vel;
	p.acceleration = accel;

	return p;
}