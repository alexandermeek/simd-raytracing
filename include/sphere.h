#ifndef SPHERE_H
#define SPHERE_H
#pragma once

#include "vec3f.h"
#include "vec3f8.h"

#include <cmath>

struct sphere {
    vec3f c;
    float r;

    sphere(vec3f c, float r) : c(c), r(r) {}

    bool intersect(const vec3f &o, const vec3f &d) const {
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

    f8 intersect(const vec3f8 &o, const vec3f8 &d) const {
        vec3f8 o_c = o - d;
        f8 b = mul8(set8(2), d.dotP(o_c));
        f8 a = d.dotP(d);
        f8 r8 = set8(r);
        f8 c = sub8(o_c.dotP(o_c), mul8(r8, r8));
        f8 b24ac = sub8(mul8(b, b), mul8(set8(4), mul8(a, c)));

        f8 t1 = div8(add8(mul8(set8(-1), b), sqrt8(b24ac)), mul8(set8(2), a));
        f8 t2 = div8(sub8(mul8(set8(-1), b), sqrt8(b24ac)), mul8(set8(2), a));

        f8 t_min = min8(t1, t2);
        return cmp8(t1, set8(0), _CMP_LT_OQ);
    }
};

#endif // SPHERE_H