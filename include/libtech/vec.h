#pragma once

struct vec3
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