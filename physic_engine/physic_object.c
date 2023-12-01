#include "physic_object.h"

#include <stdlib.h>
#include <stdio.h>


dynpoint *dynpoint__new(
    vector initial_position,
    vector initial_speed,
    double radius,
    double mass
) {
    dynpoint *system = (dynpoint *)malloc(sizeof(dynpoint));
    system->acceleration = ZERO;
    system->speed = initial_speed;
    system->position = initial_position;
    system->mass = mass;
    system->collision_sphere.center = &system->position;
    system->collision_sphere.radius = radius;
    return system;
}

void dynpoint__delete(dynpoint *system) {
    free(system);
}

void dynpoint__apply_forces(dynpoint *m, vector const *f, double dt) {
    // acceleration = 1/m * f
    m->acceleration = vector__div(f, m->mass);

    // speed += acceleration * dt
    vector acceleration_dt = vector__mul(&m->acceleration, dt);
    vector__iadd(&m->speed, &acceleration_dt);

    // position += speed * dt
    vector speed_dt = vector__mul(&m->speed, dt);
    vector__iadd(&m->position, &speed_dt);
}

void dynpoint__print(dynpoint *system) {
    printf("dynpoint(a = ");
    vector__print(&system->acceleration);
    printf(", s = ");
    vector__print(&system->speed);
    printf(", p = ");
    vector__print(&system->position);
    printf(
        ", radius = %f, mass = %f)",
        system->collision_sphere.radius,
        system->mass
    );
}


statsys *wall__new(vector position, vector normal) {
    statsys *system = (statsys *)malloc(sizeof(statsys));
    system->bounce_coeff = 1.0;
    system->position = position;
    system->shape = surface__new(&system->position, normal);
    return system;
}

statsys *bouncer__new(vector position, double radius) {
    statsys *system = (statsys *)malloc(sizeof(statsys));
    system->bounce_coeff = 1.5;
    system->position = position;
    system->shape = sphere__new(&system->position, radius);
    return system;
}

void statsys__delete(statsys *system) {
    geometric_shape__delete(system->shape);
    free(system);
}

void statsys__print(statsys *system) {
    printf("statsys(p = ");
    vector__print(&system->position);
    printf(", bounce_coeff = %f)", system->bounce_coeff);
}
