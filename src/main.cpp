#include <iostream>
#include <immintrin.h>

#define f8 __m256
#define mul8(a,b) _mm256_mul_ps(a,b)
#define add8(a,b) _mm256_add_ps(a,b)
#define sub8(a,b) _mm256_sub_ps(a,b)
#define set8(x) _mm256_set1_ps(x)
#define min8(a, b) _mm256_min_ps(a, b)
#define cmp8(a, b, i) _mm256_cmp_ps(a, b, i)
#define mm8(a) _mm256_movemask_ps(a)
#define bld8(a, b, m) _mm256_blendv_ps(a, b, m)

struct vec3f { 
    float x, y, z;

    vec3f operator+(const vec3f &rhs) {
        vec3f res;
        res.x = x + rhs.x;
        res.y = y + rhs.y;
        res.z = z + rhs.z;
        return res;
    }    
};

struct vec3f8 { 
    f8 x, y, z;

    vec3f8 operator+(const vec3f8 &rhs) {
        vec3f8 res;
        res.x = add8(x, rhs.x);
        res.y = add8(y, rhs.y);
        res.z = add8(z, rhs.z);
        return res;
    }
};

void main() {
    printf("Hello world\n");

    vec3f8 a, b;
    a.x = set8(1);
    b.x = set8(2);

    a.y = set8(3);
    b.y = set8(4);

    a.z = set8(5);
    b.z = set8(6);

    vec3f8 res = a + b;

    printf("%f, %f, %f", res.x.m256_f32[0], res.y.m256_f32[0], res.z.m256_f32[0]);
}