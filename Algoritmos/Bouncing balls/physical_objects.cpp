#include "physical_objects.h"

void physical_object::apply_gravity() {
    if (grav)
        velocity.x -= acc/100;
}

void physical_object::apply_velocity() {
    x += velocity.x/100;
    y += velocity.y/100;
}

vector2d physical_object::get_pos() {
    vector2d res(x, y);
    return res;
}

vector2d physical_object::get_velocity() {
    vector2d res(velocity.x, velocity.y);
    return res;
}

void ball::apply_air_resistance() {
    if (airres) {
        double acc = airrescons*svabs(velocity);
        double dir = direction(velocity);
        velocity.x -= acc*cos(dir);
        velocity.y -= acc*sin(dir);
    }
}

void ball::wall_collision(double xmax, double ymax) {
    if (x < radius/2 || x > xmax - radius/2)
        velocity.x = -velocity.x;
    if (y < radius/2 || y > ymax - radius/2)
        velocity.y = -velocity.y;
}

void ball::ball_collision(ball& other) {
    double oradius = other.get_radius();
    vector2d opos = other.get_pos();
    double dist = sqrt(sq(x-opos.x) + sq(y-opos.y));
    if (dist < radius + oradius) {
        double omass = other.get_mass();
        vector2d ovel = other.get_velocity();
        vector2d vf1 = vsum(rprod(2*omass, ovel), rprod(mass-omass, velocity));
        vf1 = rdiv(mass+omass, vf1);
        vector2d vf2 = vsum(rprod(2*mass, velocity), rprod(omass-mass, ovel));
        vf2 = rdiv(mass+omass, vf2);
        velocity = vf1;
        other.change_velocity(vf2);
    }
}
