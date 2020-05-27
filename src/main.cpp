#include "vec3f.h"
#include "vec3f8.h"
#include "sphere.h"

#include <iostream>
#include <cmath>
#include <immintrin.h>

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

    f8 hit8 = s.intersect(vec3f8(set8(10), set8(0), set8(0)), vec3f8(set8(-1), set8(0), set8(0)));
    hit8 = add8(set8(1), hit8);

    printf("%1.0f\n", hit8.m256_f32[0]);
}