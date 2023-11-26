#include "physic_object.h"

#include <stdlib.h>


dynpoint *dynpoint__new(vector initial_position, float radius, float mass) {
    dynpoint *system = (dynpoint *)malloc(sizeof(dynpoint));
    system->acceleration = ZERO;
    system->speed = ZERO;
    system->position = initial_position;
    system->mass = mass;
    system->collision_sphere.center = &system->position;
    system->collision_sphere.radius = radius;
    return system;
}

void dynpoint__delete(dynpoint *system) {
    free(system);
}

void dynpoint__apply_forces(dynpoint *m, vector const *f, float dt) {
    // acceleration = 1/m * f
    m->acceleration = vector__div(f, m->mass);

    // speed += acceleration * dt
    vector acceleration_dt = vector__mul(&m->acceleration, dt);
    vector__iadd(&m->speed, &acceleration_dt);

    // position += speed * dt
    vector speed_dt = vector__mul(&m->speed, dt);
    vector__iadd(&m->position, &speed_dt);
}


statsys *wall__new(vector position, vector normal) {
    statsys *system = (statsys *)malloc(sizeof(statsys));
    system->bounce_coeff = 1.0f;
    system->position = position;
    system->shape = surface__new(&system->position, normal);
    return system;
}

statsys *bouncer__new(vector position, float radius) {
    statsys *system = (statsys *)malloc(sizeof(statsys));
    system->bounce_coeff = 1.5f;
    system->position = position;
    system->shape = sphere__new(&system->position, radius);
    return system;
}

void statsys__delete(statsys *system) {
    geometric_shape__delete(system->shape);
    free(system);
}
