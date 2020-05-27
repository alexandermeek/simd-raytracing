#ifndef VEC3F_H
#define VEC3F_H
#pragma once

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

#endif // VEC3F_H