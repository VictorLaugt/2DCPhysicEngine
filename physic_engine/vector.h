#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct vector {
    double x;
    double y;
} vector;

extern vector const ZERO;

bool vector__is_zero(vector const *);

// out of place operations
vector vector__add(vector const *, vector const *);
vector vector__sub(vector const *, vector const *);
vector vector__mul(vector const *, double);
vector vector__div(vector const *, double);
vector vector__normalized(vector const *);

double vector__dot_product(vector const *, vector const *);
double vector__squared_norm(vector const *);

// in place operations
void vector__iadd(vector *, vector const *);
void vector__isub(vector *, vector const *);
void vector__imul(vector *, double);
void vector__idiv(vector *, double);
void vector__normalize(vector *);

void vector__print(vector const *);

#endif
