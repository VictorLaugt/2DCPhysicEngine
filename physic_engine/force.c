#include "force.h"

#define UNUSED(x) ((void)x)

vector gravity_force(world const *w, dynpoint const *m) {
    vector gravity = {.x = 0, .y = -(m->mass * w->gravity_coeff)};
    return gravity;
}

vector friction_force(world const *w, dynpoint const *m) {
    return vector__mul(&m->speed, w->friction_coeff);
}

vector statsys_bounce_force(
    statsys const *s,
    dynpoint const *m,
    vector const *contact_normal,
    float dt
) {
    return vector__mul(
        contact_normal,
        ((-2 * s->bounce_coeff * m->mass / dt) *
         vector__dot_product(&m->speed, contact_normal))
    );
}

vector dynpoint_bounce_force(
    dynpoint const *m1,
    dynpoint const *m2,
    vector const *contact_normal,
    float dt
) {
    UNUSED(m1);
    UNUSED(m2);
    UNUSED(contact_normal);
    UNUSED(dt);
    return ZERO;
}