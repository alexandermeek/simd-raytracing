#include "vec3f.h"
#include "vec3f8.h"
#include "sphere.h"

#include <iostream>
#include <cmath>
#include <immintrin.h>
#include <chrono>

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

    sphere s(vec3f(0, 0, 0), 2);
    bool hit = s.intersect(vec3f(10, 0, 0), vec3f(-1, 0, 0));

    printf("%d\n", hit);

    f8 hit8 = s.intersect(vec3f8(set8(10), set8(-1.5), set8(-1.5)), vec3f8(set8(-1), set8(0), set8(0)));
    hit8 = add8(set8(1), hit8);

    printf("%.0f\n", hit8.m256_f32[0]);

    constexpr unsigned int image_size = 4;
    bool image[image_size * image_size];

    auto start = std::chrono::steady_clock::now();

    for (int i = 0; i < image_size * image_size; i++) {
        float x = (float) (i % image_size);
        float y = (float) (i / image_size);

        x -= 1.5;
        y -= 1.5;

        bool hit = s.intersect(vec3f(10, x, y), vec3f(-1, 0, 0));
        if (hit) image[i] = 1; else image[i] = 0;
    }

    for (int y = 0; y < image_size; y++) {
        for (int x = 0; x < image_size; x++) {
            int i = x + image_size * y;
            printf("%d ", image[i]);
        }
        printf("\n");
    }

    auto end = std::chrono::steady_clock::now();
    printf("%d", (int) std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());

    printf("\n");

    start = std::chrono::steady_clock::now();

    float x_coords1[8] = {-1.5, -0.5, 0.5, 1.5, -1.5, -0.5, 0.5, 1.5};
    float x_coords2[8] = {-1.5, -0.5, 0.5, 1.5, -1.5, -0.5, 0.5, 1.5};
    float y_coords1[8] = {-1.5, -1.5, -1.5, -1.5, -0.5, -0.5, -0.5, -0.5};
    float y_coords2[8] = {0.5, 0.5, 0.5, 0.5, 1.5, 1.5, 1.5, 1.5};

    vec3f8 d_vec(set8(-1), set8(0), set8(0));

    f8 hit8_1 = s.intersect(vec3f8(set8(10), load8(x_coords1), load8(y_coords1)), d_vec);
    f8 hit8_2 = s.intersect(vec3f8(set8(10), load8(x_coords2), load8(y_coords2)), d_vec);

    for (int i = 0; i < 8; i++) {
        if (hit8_1.m256_f32[i] != 0) image[i] = 1; else image[i] = 0;
    }
    for (int i = 0; i < 8; i++) {
        if (hit8_2.m256_f32[i] != 0) image[i + 8] = 1; else image[i + 8] = 0;
    }

    for (int y = 0; y < image_size; y++) {
        for (int x = 0; x < image_size; x++) {
            int i = x + image_size * y;
            printf("%d ", image[i]);
        }
        printf("\n");
    }

    end = std::chrono::steady_clock::now();
    printf("%d", (int) std::chrono::duration_cast<std::chrono::microseconds>(end - start).count());
}