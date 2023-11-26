#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

vector const ZERO = {0.0f, 0.0f};

bool vector__is_zero(vector const *u) {
    return u->x == 0.0f && u->y == 0.0f;
}

static float fast_inverse_square_root(float number) {
    long i;
    float x2, y;
    const float threehalfs = 1.5F;

    x2 = number * 0.5F;
    y = number;
    i = *(long *)&y;           // evil floating point bit level hacking
    i = 0x5f3759df - (i >> 1); // what the fuck?
    y = *(float *)&i;
    y = y * (threehalfs - (x2 * y * y));
    return y;
}

vector vector__add(vector const *u, vector const *v) {
    vector result = {u->x + v->x, u->y + v->y};
    return result;
}

vector vector__sub(vector const *u, vector const *v) {
    vector result = {u->x - v->x, u->y - v->y};
    return result;
}

vector vector__mul(vector const *u, float s) {
    vector result = {s * u->x, s * u->y};
    return result;
}

vector vector__div(vector const *u, float s) {
    vector result = {u->x / s, u->y / s};
    return result;
}

vector vector__normalized(vector const *u) {
    return vector__mul(u, fast_inverse_square_root(vector__squared_norm(u)));
}

float vector__dot_product(vector const *u, vector const *v) {
    return (u->x * v->x) + (u->y * v->y);
}

float vector__squared_norm(vector const *u) {
    return u->x * u->x + u->y * u->y;
}

void vector__iadd(vector *u, vector const *v) {
    u->x += v->x;
    u->y += v->y;
}

void vector__isub(vector *u, vector const *v) {
    u->x -= v->x;
    u->y -= v->y;
}

void vector__imul(vector *u, float s) {
    u->x *= s;
    u->y *= s;
}

void vector__idiv(vector *u, float s) {
    u->x /= s;
    u->y /= s;
}

void vector__normalize(vector *u) {
    vector__imul(u, fast_inverse_square_root(vector__squared_norm(u)));
}

void vector__print(vector const *u) {
    printf("vector(x = %f, y = %f)\n", u->x, u->y);
}
