#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "force.h"

#define UNUSED(x) ((void)x)

double myabs(double x) { return (x >= 0 ? x : -x); }

int main(int argc, char *argv[]) {

    int max_step = -1;
    if (argc == 2) {
        max_step = atoi(argv[1]);
    }

    // clang-format off
    // static systems
    vector floor_normal = {0.0, 1.0};
    vector floor_position = {0.0, 0.0};
    statsys *floor = wall__new(floor_position, floor_normal);

    statsys *static_systems[1] = {floor};
    int static_system_nb = 1;
    

    // dynamic points
    // vector ball_initial_position = {0.0, 10.0};
    vector ball_initial_position = {0.0, 50.0};
    vector ball_initial_speed = {0.0, 0.0};
    dynpoint *ball = dynpoint__new(ball_initial_position, ball_initial_speed, 10.0, 1.0);

    dynpoint *dynamic_points[1] = {ball};
    vector external_forces[1] = {ZERO};
    int dynamic_point_nb = 1;


    // permanent forces
    permanent_force perm_forces[1] = {gravity_force};
    int perm_force_nb = 1;
    

    // world build
    world w = {
        .statsys_array = static_systems,
        .statsys_nb = static_system_nb,
        
        .dynpoint_array = dynamic_points,
        .external_forces_array = external_forces,
        .dynpoint_nb = dynamic_point_nb,

        .perm_force_array = perm_forces,
        .perm_force_nb = perm_force_nb,

        .gravity_coeff = 0.2,
        .friction_coeff = 0.0,

        .time_step = 2.0,
        // .time_step = 1.0,
    };
    // clang-format on

    world__init(&w);
    dynpoint__print(ball);
    printf("\n");

    long unsigned int step = 0;
    while (step != max_step) {
        world__next_step(&w);
        step += 1;
    }

    statsys__delete(floor);
    dynpoint__delete(ball);
    world__free(&w);

    return EXIT_SUCCESS;
}