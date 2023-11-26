#include <stdlib.h>
#include <stdio.h>

#include <world.h>
#include <force.h>

#define UNUSED(x) ((void)x)


void mainloop(world *w) {
    while (true) {
        world__next_step(w);
    }
}


int main(int argc, char *argv[]) {
    UNUSED(argc);
    UNUSED(argv);
    /**
    ball b = {{50.f, 40.f}, {0.f, 0.f}, 10.f};
    float delta_time = 2.f; // Doesn't work as intended :(
    vector gravity = {0.f * delta_time, -0.1f * delta_time};
    float friction = .990f;

    int surface_amount = 3;
    surface_shape surfaces[] = {
        {{-60.f, 30.f}, {-30.f, 0.f}, {1.f, 1.f}},
        {{-30.f, 0.f}, {30.f, 0.f}, {0.f, 1.f}},
        {{30.f, 0.f}, {60.f, 30.f}, {-1.f, 1.f}},
    };

    int bouncer_amount = 3;
    bouncer bouncers[] = {
        {{-60.f, 30.f}, 7.f, 2.8f},
        {{0.f, 0.f}, 7.f, 2.8f},
        {{60.f, 30.f}, 7.f, 2.8f}};

    world world = {
        .b = &b,
        .surface_amount = surface_amount,
        .surfaces = surfaces,
        .bouncer_amount = bouncer_amount,
        .bouncers = bouncers,
        .gravity = &gravity, // only physic
        .friction = friction // only physic
    };

    world__init(&world);

    init_display(&world);

    bool run = true;
    while (run) {

        loop_start_display(&world);
        run = handle_events(&world);

        world__update(&world, delta_time); // physic engine

        loop_end_display(&world);
        loop_wait(50);
    }

    terminate_display(&world);
    */

    // clang-format off

    // static systems
    vector wall_1_normal = {1.0f, 1.0f};
    vector wall_1_position = {-60.0f, 30.0f};
    statsys *wall_1 = wall__new(wall_1_position, wall_1_normal);

    vector wall_2_normal = {-1.0f, 1.0f};
    vector wall_2_position = {30.0f, 0.0f};
    statsys *wall_2 = wall__new(wall_2_position, wall_2_normal);

    vector ground_normal = {0.0f, 1.0f};
    vector ground_position = {-30.0f, 0.0f};
    statsys *ground = wall__new(wall_1_position, ground_normal);

    vector bouncer_1_position = {-60.0f, 30.0f};
    vector bouncer_2_position = {60.0f, 30.0f};
    vector bouncer_3_position = {0.0f, 0.0f};
    statsys *bouncer_1 = bouncer__new(bouncer_1_position, 7.0f);
    statsys *bouncer_2 = bouncer__new(bouncer_2_position, 7.0f);
    statsys *bouncer_3 = bouncer__new(bouncer_3_position, 7.0f);

    statsys *static_systems[6] = {wall_1, wall_2, ground, bouncer_1, bouncer_2, bouncer_3};


    // dynamic points
    vector ball_initial_position = {50.f, 40.f};
    vector ball_initial_speed = {0.0f, 0.0f};
    dynpoint *ball = dynpoint__new(ball_initial_position, ball_initial_speed, 10.f, 1.0f);

    dynpoint *dynamic_points[1] = {ball};
    vector external_forces[1] = {ZERO};


    // permanent forces
    permanent_force perm_forces[1] = {gravity_force};


    // world build
    world w = {
        .statsys_array = static_systems,
        .statsys_nb = 6,
        
        .dynpoint_array = dynamic_points,
        .external_forces_array = external_forces,
        .dynpoint_nb = 1,

        .perm_force_array = perm_forces,
        .perm_force_nb = 1,

        .gravity_coeff = -0.2f,
        .friction_coeff = 0.0f,

        .time_step = 2.f,
    };
    // clang-format on

    // vector__print(&ZERO);
    // printf("sizeof(vector) = %ld\n", sizeof(vector));

    world__init(&w);
    mainloop(&w);

    // memory free
    statsys__delete(wall_1);
    statsys__delete(wall_2);
    statsys__delete(ground);

    statsys__delete(bouncer_1);
    statsys__delete(bouncer_2);
    statsys__delete(bouncer_3);

    dynpoint__delete(ball);

    world__free(&w);

    return EXIT_SUCCESS;
}