#ifndef PHYSIC_OBJECT_H
#define PHYSIC_OBJECT_H

#include "vector.h"
#include "collision.h"


/**
 * Dynamic point: system whose motion is subject to the laws of point mechanics.
 */
typedef struct
{
    vector acceleration;
    vector speed;
    vector position;
    double mass;
    sphere collision_sphere;
} dynpoint;

dynpoint *dynpoint__new(
    vector initial_position,
    vector initial_speed,
    double radius,
    double mass
);
void dynpoint__delete(dynpoint *system);

void dynpoint__apply_forces(dynpoint *m, vector const *f, double dt);
void dynpoint__print(dynpoint *system);

/**
 * Static system: System motion is not subject to the laws of mechanics.
 */
typedef struct
{
    double bounce_coeff;
    vector position;
    geometric_shape
        *shape; // shape used to perform collision detection on the system
} statsys;

statsys *bouncer__new(vector position, double radius);
statsys *wall__new(vector position, vector normal);
void statsys__delete(statsys *system);

void statsys__print(statsys *system);

#endif
