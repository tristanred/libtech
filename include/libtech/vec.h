#pragma once

#include "libtech.h"

class LIBTECH_CLASS vec2
{
public:
    vec2();
    vec2(float scale);
    vec2(float x, float y);
    vec2(const vec2 & other);

    float x;
    float y;

    float Length();
    vec2 Normalize();

    void Add(float scalar);
    void Subtract(float scalar);
    void Multiply(float scalar);
    void Divide(float scalar);

    void Add(vec2* other);
    void Subtract(vec2* other);
    void Multiply(vec2* other);

    float DotProduct(vec2* other);

    /**
     * \brief Return a vector perpendicular to this one.
     *
     * \return A vector perpendicular to this object.
     */
    vec2 Perpendiculate();
};

// Alternate functions while the vec2's operator overloading are fixed.
vec2 Add_Vectors(vec2* first, vec2* second);
vec2 Sub_Vectors(vec2* first, vec2* second);
vec2 Mul_Vectors(vec2* first, vec2* second);

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
