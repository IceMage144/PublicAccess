#ifndef __VECTORS_H__
#define __VECTORS_H__

#include <cmath>

inline float sq(float num) {
    return num*num;
}

struct vector2d {
    double x, y;
    vector2d(): x(0), y(0) {};
    vector2d(double x, double y): x(x), y(y) {};
};

extern vector2d vsum(vector2d v1, vector2d v2);

extern vector2d vsub(vector2d v1, vector2d v2);

extern double dprod(vector2d v1, vector2d v2);

extern vector2d rprod(double num, vector2d v);

extern vector2d rdiv(double num, vector2d v);

extern double svabs(vector2d v);

extern double direction(vector2d v);

#endif
