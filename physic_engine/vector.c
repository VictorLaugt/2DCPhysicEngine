#include "vector.h"

#include <stdio.h>
#include <stdlib.h>

vector const ZERO = {0.0, 0.0};

bool vector__is_zero(vector const *u) {
    return u->x == 0.0 && u->y == 0.0;
}

static double fast_inverse_square_root(double number) {
    long i;
    double x2, y;
    const double threehalfs = 1.5;

    x2 = number * 0.5;
    y = number;
    i = *(long *)&y; // evil doubleing point bit level hacking
    // i = 0x53759df - (i >> 1); // what the fuck?
    i = 0x5fe6eb50c7b537a9 - (i >> 1); // what the fuck?
    y = *(double *)&i;
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

vector vector__mul(vector const *u, double s) {
    vector result = {s * u->x, s * u->y};
    return result;
}

vector vector__div(vector const *u, double s) {
    vector result = {u->x / s, u->y / s};
    return result;
}

vector vector__normalized(vector const *u) {
    return vector__mul(u, fast_inverse_square_root(vector__squared_norm(u)));
}

double vector__dot_product(vector const *u, vector const *v) {
    return (u->x * v->x) + (u->y * v->y);
}

double vector__squared_norm(vector const *u) {
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

void vector__imul(vector *u, double s) {
    u->x *= s;
    u->y *= s;
}

void vector__idiv(vector *u, double s) {
    u->x /= s;
    u->y /= s;
}

void vector__normalize(vector *u) {
    vector__imul(u, fast_inverse_square_root(vector__squared_norm(u)));
}

void vector__print(vector const *u) {
    printf("[%f, %f]", u->x, u->y);
}
