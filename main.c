#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "force.h"

#define UNUSED(x) ((void)x)

double myabs(double x) {
    return (x >= 0 ? x : -x);
}

void print_ball_stats(dynpoint *ball) {
    printf("acceleration = ");
    vector__print(&ball->acceleration);
    printf("\nspeed = ");
    vector__print(&ball->speed);
    printf("\nposition = ");
    vector__print(&ball->position);
    printf("\n");
}

int main(int argc, char *argv[]) {

    int max_step = -1;
    if (argc == 2) {
        max_step = atoi(argv[1]);
    }

    // clang-format off
    // static systems
    vector ground_normal = {0.0, 1.0};
    vector ground_position = {0.0, 0.0};
    statsys *ground = wall__new(ground_position, ground_normal);

    statsys *static_systems[1] = {ground};


    // dynamic points
    vector ball_initial_position = {0.0, 40.0};
    vector ball_initial_speed = {0.0, 0.0};
    dynpoint *ball = dynpoint__new(ball_initial_position, ball_initial_speed, 10.0, 1.0);

    dynpoint *dynamic_points[1] = {ball};
    vector external_forces[1] = {ZERO};


    // permanent forces
    permanent_force perm_forces[1] = {gravity_force};


    // world build
    world w = {
        .statsys_array = static_systems,
        .statsys_nb = 1,
        
        .dynpoint_array = dynamic_points,
        .external_forces_array = external_forces,
        .dynpoint_nb = 1,

        .perm_force_array = perm_forces,
        .perm_force_nb = 1,

        .gravity_coeff = 0.2,
        .friction_coeff = 0.0,

        .time_step = 2.0,
        // .time_step = 1.0,
    };
    // clang-format on

    // vector__print(&ZERO);
    // printf("sizeof(vector) = %ld\n", sizeof(vector));

    world__init(&w);
    print_ball_stats(ball);

    long unsigned int step = 0;
    while (true) {
        world__next_step(&w);
        step += 1;

        printf("\n===== step = %lu =====\n", step);
        print_ball_stats(ball);

        if (myabs(ball->position.x) >= 50 || myabs(ball->position.y) >= 50) {
            exit(EXIT_SUCCESS);
        }

        if (myabs(ball->speed.x) >= 100 || myabs(ball->speed.y) >= 100) {
            exit(EXIT_SUCCESS);
        }

        if (step == max_step) {
            exit(EXIT_SUCCESS);
        }
    }

    statsys__delete(ground);
    dynpoint__delete(ball);
    world__free(&w);

    return EXIT_SUCCESS;
}