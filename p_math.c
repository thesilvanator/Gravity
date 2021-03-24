#include "p_math.h"

#include <stdio.h>
#include <math.h>

struct vec3 create_vec(real x, real y, real z) {
	struct vec3 vec = {
		.x = x,
		.y = y,
		.z = z
	};
	return vec;
}

struct vec3 zero_vec() {
	struct vec3 vec = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 0.0f
	};
	return vec;
}
struct vec3 x_vec() {
	struct vec3 vec = {
		.x = 1.0f,
		.y = 0.0f,
		.z = 0.0f
	};
	return vec;
}
struct vec3 y_vec() {
	struct vec3 vec = {
		.x = 0.0f,
		.y = 1.0f,
		.z = 0.0f
	};
	return vec;
}
struct vec3 z_vec() {
	struct vec3 vec = {
		.x = 0.0f,
		.y = 0.0f,
		.z = 1.0f
	};
	return vec;
}

struct vec3 add_vectors(struct vec3 vec_1, struct vec3 vec_2) {
	vec_1.x += vec_2.x;
	vec_1.y += vec_2.y;
	vec_1.z += vec_2.z;

	return vec_1;
}
struct vec3 sub_vectors(struct vec3 vec_1, struct vec3 vec_2) {
	vec_1.x -= vec_2.x;
	vec_1.y -= vec_2.y;
	vec_1.z -= vec_2.z;

	return vec_1;
}

struct vec3 scalar_product(struct vec3 vec, real scalar) {
	vec.x *= scalar;
	vec.y *= scalar;
	vec.z *= scalar;

	return vec;
}
real dot_product(struct vec3 vec_1, struct vec3 vec_2) {
	return vec_1.x * vec_2.x + vec_1.y * vec_2.y + vec_1.z * vec_2.z;
}
struct vec3 cross_product(struct vec3 vec_1, struct vec3 vec_2) {
	struct vec3 new_vec = {
		.x = vec_1.y*vec_2.z - vec_1.z*vec_2.y,
		.y = vec_1.z*vec_2.x - vec_1.x*vec_2.z,
		.z = vec_1.x*vec_2.y - vec_1.y*vec_2.x
	};
	return new_vec;
}


real length(struct vec3 vec) {
	real d = vec.x * vec.x + vec.y * vec.y + vec.z * vec.z;
	return (real)sqrtf(d);
}

struct vec3 normalize(struct vec3 vec) {
	real l = length(vec);
	return scalar_product(vec, (real)1/l);
}


void print_vec(struct vec3 vec) {
	printf("x: %f, y: %f, z: %f\n", vec.x, vec.y, vec.z);
}