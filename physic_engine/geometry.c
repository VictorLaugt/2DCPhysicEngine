#include <stdlib.h>

#include "geometry.h"

/**
 * geometric_shape data type polymorphism
 */

#define SHAPE_TYPE_NB 2

typedef enum
{
    SPHERE = 0,
    SURFACE = 1,
} shape_type;

struct geometric_shape
{
    shape_type type;
    void *data;
};


/**
 * Collision methods
 */
vector sphere__collision(sphere const *s1, sphere const *s2) {
    vector u = vector__sub(&s2->center, &s1->center);
    float r = s2->radius + s1->radius;
    if (vector__squared_norm(&u) <= (r * r)) {
        return vector__normalized(&u);
    }
    else {
        return ZERO;
    }
}

vector surface__collision(surface const *p, sphere const *s) {
    vector u = vector__sub(&s->center, &p->point);
    if (vector__dot_product(&p->normal, &u) <= s->radius) {
        return p->normal;
    }
    else {
        return ZERO;
    }
}

typedef vector (*collision_detector)(void const *shape_data, sphere const *s);
static collision_detector COLISION_METHODS[SHAPE_TYPE_NB] = {
    sphere__collision,
    surface__collision,
};


/**
 * geometric_shape interface implementation
 */

vector geometric_shape__collision(geometric_shape const *shape, sphere const *s) {
    return COLISION_METHODS[shape->type](shape->data, s);
}

geometric_shape *sphere__new(vector *position, float radius) {
    sphere *data = (sphere *)malloc(sizeof(sphere));
    data->center = position;
    data->radius = radius;

    geometric_shape *shape = (geometric_shape *)malloc(sizeof(geometric_shape));
    shape->data = (void *)data;
    shape->type = SPHERE;

    return shape;
}

geometric_shape *surface__new(vector *position, vector normal) {
    surface *data = (surface *)malloc(sizeof(surface));
    data->point = position;
    data->normal = vector__normalized(&normal);

    geometric_shape *shape = (geometric_shape *)malloc(sizeof(geometric_shape));
    shape->data = (void *)data;
    shape->type = SURFACE;

    return shape;
}

void geometric_shape__delete(geometric_shape *shape) {
    free(shape->data);
    free(shape);
}
