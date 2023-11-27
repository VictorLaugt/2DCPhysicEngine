#ifndef COLLISION_H
#define COLLISION_H

#include <stdbool.h>

#include "vector.h"


/**
 * Sphere shape
 */
typedef struct
{
    vector *center;
    float radius;
} sphere;

vector sphere__collision(sphere const *s1, sphere const *s2);


/**
 * Surface shape
 */
typedef struct
{
    vector *point; // point in the surface
    vector normal; // unitary normal vector of the surface
} surface;

vector surface__collision(surface const *p, sphere const *s);


/**
 * Polymorphic geometric shape (sphere or surface)
 */
typedef struct geometric_shape geometric_shape;

vector geometric_shape__collision(geometric_shape const *shape, sphere const *s);

geometric_shape *surface__new(vector *position, vector normal);
geometric_shape *sphere__new(vector *position, float radius);

void geometric_shape__delete(geometric_shape *shape);

#endif