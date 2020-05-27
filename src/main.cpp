#include <iostream>
#include <math.h>
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
#define sqrt8(a) _mm256_sqrt_ps (a)

struct vec3f { 
    float x, y, z;

    vec3f() : x(0), y(0), z(0) {}
    vec3f(float x, float y, float z) : x(x), y(y), z(z) {}

    vec3f operator+(const vec3f &rhs) const {
        vec3f res;
        res.x = x + rhs.x;
        res.y = y + rhs.y;
        res.z = z + rhs.z;
        return res;
    }

    vec3f operator-(const vec3f &rhs) const {
        vec3f res;
        res.x = x - rhs.x;
        res.y = y - rhs.y;
        res.z = z - rhs.z;
        return res;
    }

    vec3f operator*(const vec3f &rhs) const {
        vec3f res;
        res.x = x * rhs.x;
        res.y = y * rhs.y;
        res.z = z * rhs.z;
        return res;
    }

    vec3f operator/(const vec3f &rhs) const {
        vec3f res;
        res.x = x / rhs.x;
        res.y = y / rhs.y;
        res.z = z / rhs.z;
        return res;
    }

    float dotP(const vec3f &v) const {
        return x * v.x + y * v.y + z * v.z;
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

struct sphere {
    vec3f c;
    float r;

    sphere(vec3f c, float r) : c(c), r(r) {}

    bool intersect(const vec3f &o, const vec3f &d) {
        vec3f o_c = o - d;
        float b = 2 * d.dotP(o_c);
        float a = d.dotP(d);
        float c = o_c.dotP(o_c) - (r * r);
        float b24ac = (b * b) - 4 * a * c;

	    if (b24ac < 0) {
		    return false;
	    }

	    float t1 = (-b + std::sqrt(b24ac)) / 2.0f * a;
	    float t2 = (-b - std::sqrt(b24ac)) / 2.0f * a;

	    if (t1 < 0 || t2 < 0) {
		    return false;
	    } else {
            return true;
        }
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

    printf("%f, %f, %f\n", res.x.m256_f32[0], res.y.m256_f32[0], res.z.m256_f32[0]);

    sphere s(vec3f(0, 0, 0), 5);
    bool hit = s.intersect(vec3f(10, 0, 0), vec3f(-1, 0, 0));

    printf("%d\n", hit);
}