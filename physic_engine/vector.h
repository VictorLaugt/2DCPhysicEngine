#ifndef VECTOR_H
#define VECTOR_H

#include <stdbool.h>

typedef struct vector
{
    float x;
    float y;
} vector;

extern vector const ZERO;

bool vector__is_zero(vector const *);

// out of place operations
vector vector__add(vector const *, vector const *);
vector vector__sub(vector const *, vector const *);
vector vector__mul(vector const *, float);
vector vector__div(vector const *, float);
vector vector__normalized(vector const *);

float vector__dot_product(vector const *, vector const *);
float vector__squared_norm(vector const *);

// in place operations
void vector__iadd(vector *, vector const *);
void vector__isub(vector *, vector const *);
void vector__imul(vector *, float);
void vector__idiv(vector *, float);
void vector__normalize(vector *);

void vector__print(vector const *);

#endif
