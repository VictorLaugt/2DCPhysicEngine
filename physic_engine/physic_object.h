#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

#include "vector.h"
#include "geometry.h"


/**
 * Dynamic point: system whose motion is subject to the laws of point mechanics.
 */
typedef struct
{
    vector acceleration;
    vector speed;
    vector position;
    float mass;
    sphere collision_sphere;
} dynpoint;

dynpoint *dynpoint__new(
    vector initial_position,
    vector initial_speed,
    float radius,
    float mass
);
void dynpoint__delete(dynpoint *system);

void dynpoint__apply_forces(dynpoint *m, vector const *f, float dt);

/**
 * Static system: System motion is not subject to the laws of mechanics.
 */
typedef struct
{
    float bounce_coeff;
    vector position;
    geometric_shape
        *shape; // shape used to perform collision detection on the system
} statsys;

statsys *bouncer__new(vector position, float radius);
statsys *wall__new(vector position, vector normal);
void statsys__delete(statsys *system);

#endif
