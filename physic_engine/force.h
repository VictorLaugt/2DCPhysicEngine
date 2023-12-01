#ifndef FORCE_H
#define FORCE_H

#include "world.h"

vector gravity_force(world const *w, dynpoint const *m);
vector friction_force(world const *w, dynpoint const *m);

vector statsys_bounce_force(
    statsys const *s,
    dynpoint const *m,
    vector const *contact_normal,
    double dt
);

vector dynpoint_bounce_force(
    dynpoint const *m1,
    dynpoint const *m2,
    vector const *contact_normal,
    double dt
);

#endif