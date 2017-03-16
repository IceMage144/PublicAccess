#ifndef __PHYSICAL_OBJECTS_H__
#define __PHYSICAL_OBJECTS_H__

#include "vectors.h"

#define TAU 6.283185
#define PI 3.141592
#define acc 9.80665
#define airden 1.225

class physical_object {
    double x, y, mass, airrescons;
    bool grav, airres;
    vector2d velocity;
public:
    vector2d get_pos();
    vector2d get_velocity();
    double get_mass() {
        return mass;
    };
    virtual char type() = 0;
    void gravity(bool boo) {
        grav = boo;
    };
    void air_resistance(bool boo) {
        airres = boo;
    };
    void apply_gravity();
    virtual void apply_air_resistance() = 0;
    void apply_velocity();
    void add_velocity(vector2d vec) {
        velocity = vsum(velocity, vec);
    };
    void change_velocity(vector2d vec)   {
        velocity = vec;
    };
    virtual void wall_collision(double xmax, double ymax) = 0;
    virtual void ball_collision(class ball& other) = 0;
};

class ball : public physical_object {
    double x, y, mass, airrescons;
    bool grav, airres;
    vector2d velocity;
    double radius;
public:
    ball(): x(0), y(0), radius(0), mass(0), grav(true), airres(true) {};
    ball(double x, double y, double radius, double mass): x(x), y(y), radius(radius), mass(mass), grav(true), airres(true) {
        airrescons = 0.47*airden*PI*sq(radius)/(mass*10000);
    };
    char type() {
        return 'b';
    };
    double get_radius() {
        return radius;
    };
    void apply_air_resistance();
    void wall_collision(double xmax, double ymax);
    void ball_collision(ball& other);
};

#endif
