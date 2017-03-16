#include "vectors.h"

vector2d vsum(vector2d v1, vector2d v2) {
    vector2d res(v1.x+v2.x, v1.y+v2.y);
    return res;
}

vector2d vsub(vector2d v1, vector2d v2) {
    vector2d res(v1.x-v2.x, v1.y-v2.y);
    return res;
}

double dprod(vector2d v1, vector2d v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

vector2d rprod(double num, vector2d v) {
    vector2d res(num*v.x, num*v.y);
    return res;
}

vector2d rdiv(double num, vector2d v) {
    vector2d res(v.x/num, v.y/num);
    return res;
}

double svabs(vector2d v) {
    return sq(v.x)+sq(v.y);
}

double direction(vector2d v) {
    if (v.x != 0 && v.y != 0)
        return atan2(v.y, v.x);
    return 0;
}
