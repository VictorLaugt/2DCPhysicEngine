#ifndef WORLD_H
#define WORLD_H

#include "physic_object.h"

typedef struct world world;

typedef vector (*permanent_force)(world const *, dynpoint const *);

struct world {
    // array which stores every static system
    statsys **statsys_array;
    int statsys_nb;

    // array which stores every dynamic point
    dynpoint **dynpoint_array;
    vector *external_forces_array;
    int dynpoint_nb;

    // symmetrical matrix of size "dynpoint_nb * dynpoint_nb" which stores
    // collisions between every pair of dynamic points
    vector *dynpoint_coll_mtrx;

    // matrix of size "dynpoint_nb * statsys_nb" which stores collisions between
    // every (dynamic point, static system) couple
    vector *statsys_coll_mtrx;

    // array which stores every permanent force
    permanent_force *perm_force_array;
    int perm_force_nb;

    // physical parameters
    double gravity_coeff;
    double friction_coeff;

    // time step of the simulation
    double const time_step;
};


void world__init(world *w);
void world__free(world *w);

vector world__get_dynpoint_collision(world *w, int i, int j);
vector world__get_statsys_collision(world *w, int i, int j);

void world__set_dynpoint_collision(world *w, int i, int j, vector const *normal);
void world__set_statsys_collision(world *w, int i, int j, vector const *normal);

void world__next_step(world *w);

#endif