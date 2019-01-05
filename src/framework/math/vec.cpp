#include "libtech/vec.h"

#include <cmath>

vec2::vec2()
{
}

vec2::vec2(float scale)
{
    this->x = scale;
    this->y = scale;
}

vec2::vec2(float x, float y)
{
    this->x = x;
    this->y = y;
}

float vec3_len(vec3* v)
{
    return sqrt(pow(v->x, 2) + pow(v->y, 2) + pow(v->z, 2));
}

vec3 vec3_normalize(vec3* v)
{
    vec3 res = *v;
    float length = vec3_len(v);

    vec3_div_scalar(&res, length);

    return res;
}

void vec3_add_scalar(vec3* v, float scalar)
{
    v->x += scalar;
    v->y += scalar;
    v->z += scalar;
}

void vec3_sub_scalar(vec3* v, float scalar)
{
    v->x -= scalar;
    v->y -= scalar;
    v->z -= scalar;
}

void vec3_mul_scalar(vec3* v, float scalar)
{
    v->x *= scalar;
    v->y *= scalar;
    v->z *= scalar;
}

void vec3_div_scalar(vec3* v, float scalar)
{
    v->x /= scalar;
    v->y /= scalar;
    v->z /= scalar;
}

float vec3_dot_product(vec3* v, vec3* r)
{
    return (v->x * r->x) + (v->y * r->y) + (v->z * r->z);
}