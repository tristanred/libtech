#include "libtech/vec.h"

#include <cmath>

vec2::vec2() {}

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

vec2::vec2(const vec2& other)
{
    this->x = other.x;
    this->y = other.y;
}

float vec2::Length() const
{
    return sqrt(pow(this->x, 2) + pow(this->y, 2));
}

vec2 vec2::Normalize()
{
    vec2 normalized = vec2(*this);
    normalized = normalized.Divide(normalized.Length());

    return normalized;
}

vec2 vec2::Add(float scalar) const
{
    return vec2(this->x + scalar, this->y + scalar);
}

vec2 vec2::Subtract(float scalar) const
{
    return vec2(this->x - scalar, this->y - scalar);
}

vec2 vec2::Multiply(float scalar) const
{
    return vec2(this->x * scalar, this->y * scalar);
}

vec2 vec2::Divide(float scalar) const
{
    return vec2(this->x / scalar, this->y / scalar);
}

vec2 vec2::Add(const vec2* other) const
{
    return vec2(this->x + other->x, this->y + other->y);
}

vec2 vec2::Subtract(const vec2* other) const
{
    return vec2(this->x - other->x, this->y - other->y);
}

vec2 vec2::Multiply(const vec2* other) const
{
    return vec2(this->x * other->x, this->y * other->y);
}

float vec2::DotProduct(const vec2* other) const
{
    return (this->x * other->x) + (this->y * other->y);
}

vec2 vec2::Perpendiculate()
{
    return vec2(-(this->y), this->x);
}

vec2 Add_Vectors(vec2* first, vec2* second)
{
    return vec2(first->x + second->x, first->y + second->y);
}

vec2 Sub_Vectors(vec2* first, vec2* second)
{
    return vec2(first->x - second->x, first->y - second->y);
}

vec2 Mul_Vectors(vec2* first, vec2* second)
{
    return vec2(first->x * second->x, first->y * second->y);
}

float vec2_len(vec2* v)
{
    return sqrt(pow(v->x, 2) + pow(v->y, 2));
}

vec2 vec2_normalize(vec2* v)
{
    vec2 res = *v;
    float length = vec2_len(v);

    vec2_div_scalar(&res, length);

    return res;
}

void vec2_add_scalar(vec2* v, float scalar)
{
    v->x += scalar;
    v->y += scalar;
}

void vec2_sub_scalar(vec2* v, float scalar)
{
    v->x -= scalar;
    v->y -= scalar;
}

void vec2_mul_scalar(vec2* v, float scalar)
{
    v->x *= scalar;
    v->y *= scalar;
}

void vec2_div_scalar(vec2* v, float scalar)
{
    v->x /= scalar;
    v->y /= scalar;
}

float vec2_dot_product(vec2* v, vec2* r)
{
    return (v->x * r->x) + (v->y * r->y);
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

vec2* operator+(vec2* lhs, const vec2& rhs)
{
    return new vec2(lhs->x + rhs.x, lhs->y + rhs.y);
}

vec2 operator+(vec2& lhs, const vec2& rhs)
{
    return vec2(lhs.x + rhs.x, lhs.y + rhs.y);
}
