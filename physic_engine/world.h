#ifndef WORLD_H
#define WORLD_H

#include "physic_object.h"

typedef vector (*permanent_force)(dynpoint const *);

typedef struct
{
    // array which stores every static system
    statsys **statsys_array;
    int statsys_nb;

    // array which stores every dynamic point
    dynpoint **dynpoint_array;
    vector *external_forces_array;
    int dynpoint_nb;

    // symmetrical matrix of size "dynpoint_nb * dynpoint_nb" which stores
    // collisions between every pair of dynamic points
    vector **dynpoint_coll;

    // matrix of size "dynpoint_nb * statsys_nb" which stores collisions between
    // every (dynamic point, static system) couple
    vector **statsys_coll;

    // array which stores every permanent force
    permanent_force *perm_force_array;
    int perm_force_nb;

    // physical parameters
    float gravity_coeff;
    float friction_coeff;

    // time step of the simulation
    float const time_step;
} world;


void world__init(world *w);

void world__next_step(world *w);

#endif