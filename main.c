#include <stdlib.h>
#include <stdio.h>

#include "world.h"
#include "force.h"

#define UNUSED(x) ((void)x)

float myabs(float x) {
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
    UNUSED(argc);
    UNUSED(argv);

    // clang-format off

    // // static systems
    // vector wall_1_normal = {1.0f, 1.0f};
    // vector wall_1_position = {-60.0f, 30.0f};
    // statsys *wall_1 = wall__new(wall_1_position, wall_1_normal);

    // vector wall_2_normal = {-1.0f, 1.0f};
    // vector wall_2_position = {30.0f, 0.0f};
    // statsys *wall_2 = wall__new(wall_2_position, wall_2_normal);

    // vector ground_normal = {0.0f, 1.0f};
    // vector ground_position = {-30.0f, 0.0f};
    // statsys *ground = wall__new(ground_position, ground_normal);

    // vector bouncer_1_position = {-60.0f, 30.0f};
    // vector bouncer_2_position = {60.0f, 30.0f};
    // vector bouncer_3_position = {0.0f, 0.0f};
    // statsys *bouncer_1 = bouncer__new(bouncer_1_position, 7.0f);
    // statsys *bouncer_2 = bouncer__new(bouncer_2_position, 7.0f);
    // statsys *bouncer_3 = bouncer__new(bouncer_3_position, 7.0f);

    // statsys *static_systems[6] = {wall_1, wall_2, ground, bouncer_1, bouncer_2, bouncer_3};


    // // dynamic points
    // vector ball_initial_position = {50.f, 40.f};
    // vector ball_initial_speed = {0.0f, 0.0f};
    // dynpoint *ball = dynpoint__new(ball_initial_position, ball_initial_speed, 10.f, 1.0f);

    // dynpoint *dynamic_points[1] = {ball};
    // vector external_forces[1] = {ZERO};


    // // permanent forces
    // permanent_force perm_forces[1] = {gravity_force};


    // // world build
    // world w = {
    //     .statsys_array = static_systems,
    //     .statsys_nb = 6,
        
    //     .dynpoint_array = dynamic_points,
    //     .external_forces_array = external_forces,
    //     .dynpoint_nb = 1,

    //     .perm_force_array = perm_forces,
    //     .perm_force_nb = 1,

    //     .gravity_coeff = 0.2f,
    //     .friction_coeff = 0.0f,

    //     .time_step = 2.f,
    // };

    // static systems
    vector ground_normal = {0.0f, 1.0f};
    vector ground_position = {0.0f, 0.0f};
    statsys *ground = wall__new(ground_position, ground_normal);

    statsys *static_systems[1] = {ground};


    // dynamic points
    vector ball_initial_position = {0.0f, 40.0f};
    vector ball_initial_speed = {0.0f, 0.0f};
    dynpoint *ball = dynpoint__new(ball_initial_position, ball_initial_speed, 10.f, 1.0f);

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

        .gravity_coeff = 0.2f,
        .friction_coeff = 0.0f,

        .time_step = 2.f,
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

        if (myabs(ball->position.x) >= 100 || myabs(ball->position.y) >= 100) {
            exit(EXIT_SUCCESS);
        }

        if (myabs(ball->speed.x) >= 100 || myabs(ball->speed.y) >= 100) {
            exit(EXIT_SUCCESS);
        }
    }

    // memory free
    // statsys__delete(wall_1);
    // statsys__delete(wall_2);
    // statsys__delete(ground);

    // statsys__delete(bouncer_1);
    // statsys__delete(bouncer_2);
    // statsys__delete(bouncer_3);

    statsys__delete(ground);

    dynpoint__delete(ball);

    world__free(&w);

    return EXIT_SUCCESS;
}