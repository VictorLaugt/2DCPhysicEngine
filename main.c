#include <stdlib.h>

#include <world.h>

#define UNUSED(x) ((void)x)

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

    vector wall_1_normal = {1.0f, 1.0f};
    vector wall_1_position = {-60.0f, 30.0f};
    statsys *wall_1 = wall__new(wall_1_position, wall_1_normal);

    vector wall_2_normal = {-1.0f, 1.0f};
    vector wall_2_position = {30.0f, 0.0f};
    statsys *wall_2 = wall__new(wall_2_position, wall_2_normal);

    vector ground_normal = {0.0f, 1.0f};
    vector ground_position = {-30.0f, 0.0f};
    statsys *ground = wall__new(wall_1_position, ground_normal);

    statsys *static_systems[3] = {wall_1, wall_2, ground};

    statsys__delete(wall_1);
    statsys__delete(wall_2);
    statsys__delete(ground);

    return EXIT_SUCCESS;
}