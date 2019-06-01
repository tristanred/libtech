#pragma once

#include "libtech.h"

class LIBTECH_CLASS vec2
{
public:
    vec2();
    vec2(float scale);
    vec2(float x, float y);

    float x;
    float y;

    float Length();
    vec2 Normalize();

    void Add(float scalar);
    void Subtract(float scalar);
    void Multiply(float scalar);
    void Divide(float scalar);

    float DotProduct(vec2* other);
};

float vec2_len(vec2* v);
vec2 vec2_normalize(vec2* v);
void vec2_add_scalar(vec2* v, float scalar);
void vec2_sub_scalar(vec2* v, float scalar);
void vec2_mul_scalar(vec2* v, float scalar);
void vec2_div_scalar(vec2* v, float scalar);
float vec2_dot_product(vec2* v, vec2* r);

struct LIBTECH_CLASS vec3
{
    float x;
    float y;
    float z;
};

float vec3_len(vec3* v);
vec3 vec3_normalize(vec3* v);
void vec3_add_scalar(vec3* v, float scalar);
void vec3_sub_scalar(vec3* v, float scalar);
void vec3_mul_scalar(vec3* v, float scalar);
void vec3_div_scalar(vec3* v, float scalar);
float vec3_dot_product(vec3* v, vec3* r);