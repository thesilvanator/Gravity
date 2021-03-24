#ifndef P_MATH_H
#define P_MATH_H

typedef double real;

// #define GRAV_CONST 6.67408f*10e-11
#define GRAV_CONST 6.67408f*10e-3


struct vec3 {
	real x;
	real y;
	real z;
};

struct vec3 create_vec(real x, real y, real z);
struct vec3 zero_vec();
struct vec3 x_vec();
struct vec3 y_vec();
struct vec3 z_vec();


struct vec3 add_vectors(struct vec3 vec_1, struct vec3 vec_2);
struct vec3 sub_vectors(struct vec3 vec_1, struct vec3 vec_2);

struct vec3 scalar_product(struct vec3 vec_1, real scalar);
real dot_product(struct vec3 vec_1, struct vec3 vec_2);
struct vec3 cross_product(struct vec3 vec_1, struct vec3 vec_2);

real length(struct vec3 vec);
struct vec3 normalize(struct vec3 vec);

void print_vec(struct vec3 vec);

#endif