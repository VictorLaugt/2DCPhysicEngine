#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "force.h"


/**
 * Sets to `ZERO` the external forces resultant of every dynamic point of the
 * world `w`.
 */
static void reset_external_forces(world *w) {
    for (int i = 0; i < w->dynpoint_nb; i += 1) {
        w->external_forces_array[i] = ZERO;
    }
}


void world__init(world *w) {
    reset_external_forces(w);

    w->dynpoint_coll_mtrx =
        (vector *)malloc(sizeof(vector) * w->dynpoint_nb * w->dynpoint_nb);
    for (int i = 0; i < w->dynpoint_nb; i += 1) {
        for (int j = 0; j < w->dynpoint_nb; j += 1) {
            *(w->dynpoint_coll_mtrx + i * w->dynpoint_nb + j) = ZERO;
        }
    }

    w->statsys_coll_mtrx =
        (vector *)malloc(sizeof(vector) * w->dynpoint_nb * w->statsys_nb);
    for (int i = 0; i < w->dynpoint_nb; i += 1) {
        for (int j = 0; j < w->statsys_nb; j += 1) {
            *(w->statsys_coll_mtrx + i * w->statsys_nb + j) = ZERO;
        }
    }
}

void world__free(world *w) {
    free(w->dynpoint_coll_mtrx);
    free(w->statsys_coll_mtrx);
}

vector world__get_dynpoint_collision(world *w, int i, int j) {
    return *(w->dynpoint_coll_mtrx + i * w->dynpoint_nb + j);
}

vector world__get_statsys_collision(world *w, int i, int j) {
    return *(w->statsys_coll_mtrx + i * w->statsys_nb + j);
}

void world__set_dynpoint_collision(world *w, int i, int j, vector const *normal) {
    *(w->dynpoint_coll_mtrx + i * w->dynpoint_nb + j) = *normal;
}

void world__set_statsys_collision(world *w, int i, int j, vector const *normal) {
    *(w->statsys_coll_mtrx + i * w->statsys_nb + j) = *normal;
}


/**
 * Compute every possible collisions in the world `w`.
 */
static void refresh_collisions(world *w) {
    // collisions between a dynamic point and a static system
    for (int i = 0; i < w->dynpoint_nb; i += 1) {
        sphere *sphere_i = &w->dynpoint_array[i]->collision_sphere;

        for (int j = 0; j < w->statsys_nb; j += 1) {
            geometric_shape *shape_j = w->statsys_array[j]->shape;
            vector coll_normal_vector =
                geometric_shape__collision(shape_j, sphere_i);
            world__set_statsys_collision(w, i, j, &coll_normal_vector);
        }
    }

    // collisions between two dynamic points
    for (int i = 0; i < w->dynpoint_nb; i += 1) {
        sphere *sphere_i = &w->dynpoint_array[i]->collision_sphere;
        world__set_dynpoint_collision(w, i, i, &ZERO);

        for (int j = 0; j < i; j += 1) {
            sphere *sphere_j = &w->dynpoint_array[j]->collision_sphere;
            vector coll_normal_vector = sphere__collision(sphere_i, sphere_j);
            world__set_dynpoint_collision(w, i, j, &coll_normal_vector);
            world__set_dynpoint_collision(w, j, i, &coll_normal_vector);
        }
    }
}


/**
 * Adds to the external forces resultant of the dynamic point `b` the forces
 * exerted by the other dynamic point `a`.
 */
static void dynpoint_interaction(world *w, int a, int b) {
    vector contact_normal = world__get_dynpoint_collision(w, b, a);
    if (!vector__is_zero(&contact_normal)) {
        vector force = dynpoint_bounce_force(
            w->dynpoint_array[a],
            w->dynpoint_array[b],
            &contact_normal,
            w->time_step
        );
        vector__iadd(&w->external_forces_array[b], &force);
    }
}

/**
 * Adds to the external forces resultant of the dynamic point `b` the forces
 * exerted by the static system `a`.
 */
static void statsys_interaction(world *w, int a, int b) {
    vector contact_normal = world__get_statsys_collision(w, b, a);
    if (!vector__is_zero(&contact_normal)) {
        printf("collision : ");
        statsys__print(w->statsys_array[a]);
        printf("  ");
        dynpoint__print(w->dynpoint_array[b]);
        printf("\ncollision normal : ");
        vector__print(&contact_normal);
        printf("\n");

        vector force = statsys_bounce_force(
            w->statsys_array[a],
            w->dynpoint_array[b],
            &contact_normal,
            w->time_step
        );

        printf("bounce force : ");
        vector__print(&force);
        printf("\n");

        vector__iadd(&w->external_forces_array[b], &force);
    }
}

/**
 * For each dynamic point in the world `w`, adds to its external forces
 * resultant every forces exerted by other dynamic points.
 */
static void sum_dynpoint_forces(world *w) {
    for (int i = 0; i < w->dynpoint_nb; i += 1) {
        for (int j = 0; j < w->dynpoint_nb; j += 1) {
            if (i == j) {
                continue;  // a dynamic point cannot exert a force on itself.
            }
            dynpoint_interaction(w, j, i);
        }
    }
}

/**
 * For each dynamic point in the world `w`, adds to its external forces
 * resultant every forces exerted by static systems.
 */
static void sum_statsys_forces(world *w) {
    for (int i = 0; i < w->dynpoint_nb; i += 1) {
        for (int j = 0; j < w->statsys_nb; j += 1) { statsys_interaction(w, j, i); }
    }
}

/**
 * For each dynamic point in the world `w`, adds to its external forces
 * resultant every forces exerted by force fields.
 */
static void sum_perm_forces(world *w) {
    for (int i = 0; i < w->dynpoint_nb; i += 1) {
        for (int j = 0; j < w->perm_force_nb; j += 1) {
            vector perm_force = w->perm_force_array[j](w, w->dynpoint_array[i]);
            vector__iadd(&w->external_forces_array[i], &perm_force);
        }
    }
}


/**
 * Applies the Newton's second law of motion to every dynamic point in the world
 * `w`.
 */
static void apply_external_forces(world *w) {
    for (int i = 0; i < w->dynpoint_nb; i += 1) {
        dynpoint__apply_forces(
            w->dynpoint_array[i],
            &w->external_forces_array[i],
            w->time_step
        );
    }
}


void world__next_step(world *w) {
    static long unsigned int step = 0;
    step += 1;

    printf("===== step = %lu =====\n", step);

    // non collision forces
    reset_external_forces(w);
    sum_perm_forces(w);
    apply_external_forces(w);
    dynpoint__print(w->dynpoint_array[0]);
    printf("\n\n");

    // collision forces
    reset_external_forces(w);
    refresh_collisions(w);
    sum_statsys_forces(w);
    sum_dynpoint_forces(w);
    apply_external_forces(w);
    dynpoint__print(w->dynpoint_array[0]);
    printf("\n\n");
}
