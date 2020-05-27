#ifndef VEC3F8_H
#define VEC3F8_H
#pragma once

#include <immintrin.h>

#define f8 __m256
#define mul8(a,b) _mm256_mul_ps(a,b)
#define div8(a, b) _mm256_div_ps (a, b)
#define add8(a,b) _mm256_add_ps(a,b)
#define sub8(a,b) _mm256_sub_ps(a,b)
#define set8(x) _mm256_set1_ps(x)
#define min8(a, b) _mm256_min_ps(a, b)
#define cmp8(a, b, i) _mm256_cmp_ps(a, b, i)
#define mm8(a) _mm256_movemask_ps(a)
#define bld8(a, b, m) _mm256_blendv_ps(a, b, m)
#define sqrt8(a) _mm256_sqrt_ps (a)

struct vec3f8 { 
    f8 x, y, z;

    vec3f8() : x(set8(0)), y(set8(0)), z(set8(0)) {}
    vec3f8(f8 x, f8 y, f8 z) : x(x), y(y), z(z) {}

    vec3f8 operator+(const vec3f8 &rhs) const {
        vec3f8 res;
        res.x = add8(x, rhs.x);
        res.y = add8(y, rhs.y);
        res.z = add8(z, rhs.z);
        return res;
    }

    vec3f8 operator-(const vec3f8 &rhs) const {
        vec3f8 res;
        res.x = sub8(x, rhs.x);
        res.y = sub8(y, rhs.y);
        res.z = sub8(z, rhs.z);
        return res;
    }

    vec3f8 operator*(const vec3f8 &rhs) const {
        vec3f8 res;
        res.x = mul8(x, rhs.x);
        res.y = mul8(y, rhs.y);
        res.z = mul8(z, rhs.z);
        return res;
    }

    vec3f8 operator/(const vec3f8 &rhs) const {
        vec3f8 res;
        res.x = div8(x, rhs.x);
        res.y = div8(y, rhs.y);
        res.z = div8(z, rhs.z);
        return res;
    }

    f8 dotP(const vec3f8 &v) const {
        vec3f8 mul_res(mul8(x, v.x), mul8(y, v.y), mul8(z, v.z));
        return add8(mul_res.x, add8(mul_res.y, mul_res.z));
    }
};

#endif // VEC3F8_H