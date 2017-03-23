#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <cmath>

using namespace std;

// Physical constants
#define TAU 6.283185
#define PI 3.141592
#define g 9.80665
#define airden 1.225
#define circcons 0.47
#define G 0.00000000006674

// Display constants
#define video_max_x 1000
#define video_max_y 600

// Colors
#define MWhite sf::Color(255, 255, 255)
#define Blue sf::Color(0, 0, 255)
#define Red sf::Color(255, 0, 0)

inline float sq(float num) {
    return num*num;
}

struct Vector2d {
    double x, y;
    Vector2d(): x(0), y(0) {};
    Vector2d(double x, double y): x(x), y(y) {};
};

Vector2d vsum(Vector2d v1, Vector2d v2) {
    Vector2d res(v1.x+v2.x, v1.y+v2.y);
    return res;
}

Vector2d vsub(Vector2d v1, Vector2d v2) {
    Vector2d res(v1.x-v2.x, v1.y-v2.y);
    return res;
}

double dprod(Vector2d v1, Vector2d v2) {
    return v1.x*v2.x + v1.y*v2.y;
}

Vector2d rprod(double num, Vector2d v) {
    Vector2d res(num*v.x, num*v.y);
    return res;
}

Vector2d rdiv(double num, Vector2d v) {
    Vector2d res(v.x/num, v.y/num);
    return res;
}

double svabs(Vector2d v) {
    return sq(v.x)+sq(v.y);
}

double direction(Vector2d v) {
    if (v.x != 0 && v.y != 0)
        return atan2(v.y, v.x);
    return 0;
}

class physical_object {
public:
    double x, y, mass, airrescons, volume;
    bool grav, airres, buoy;
    Vector2d velocity;
    Vector2d get_pos();
    Vector2d get_velocity();
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
    void bouyancy(bool boo) {
        buoy = boo;
    };
    void apply_gravity();
    virtual void apply_air_resistance() = 0;
    void apply_buoyancy() {
        velocity.y -= airden*g*volume/10000000;
    };
    void apply_velocity();
    void add_velocity(Vector2d vec) {
        velocity = vsum(velocity, vec);
    };
    void change_velocity(Vector2d vec)   {
        velocity = vec;
    };
    virtual void wall_collision(double xmax, double ymax) = 0;
    virtual void ball_collision(class ball& other) = 0;
};

class ball : public physical_object {
    double radius;
public:
    ball() {
        physical_object::x = 0;
        physical_object::y = 0;
        radius = 1;
        physical_object::mass = 1;
        physical_object::grav = true;
        physical_object::airres = true;
        physical_object::buoy = true;
        airrescons = circcons*airden*PI*radius/(mass*10000);
        volume = PI*sq(radius);
        velocity = Vector2d();
    };
    ball(double x, double y, double r, double mass) {
        physical_object::x = x;
        physical_object::y = y;
        radius = r;
        physical_object::mass = mass;
        physical_object::grav = true;
        physical_object::airres = true;
        physical_object::buoy = true;
        airrescons = circcons*airden*PI*radius/(mass*10000);
        volume = PI*sq(radius);
        velocity = Vector2d();
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

void physical_object::apply_gravity() {
    if (grav)
        velocity.y += g/500;
}

void physical_object::apply_velocity() {
    x += velocity.x/100;
    y += velocity.y/100;
}

Vector2d physical_object::get_pos() {
    return Vector2d(x, y);
}

Vector2d physical_object::get_velocity() {
    Vector2d res(velocity.x, velocity.y);
    return res;
}

void ball::apply_air_resistance() {
    if (airres) {
        double acc = airrescons*svabs(physical_object::velocity);
        double dir = direction(physical_object::velocity);
        physical_object::velocity.x -= acc*cos(dir)/500;
        physical_object::velocity.y -= acc*sin(dir)/500;
    }
}

void ball::wall_collision(double xmax, double ymax) {
    if (physical_object::x < 0 || physical_object::x > xmax - 2*radius)
        physical_object::velocity.x = -85*(physical_object::velocity.x)/100;
    if (physical_object::y < 0 || physical_object::y > ymax - 2*radius) {
        physical_object::velocity.y = -85*(physical_object::velocity.y)/100;
    }
}

void ball::ball_collision(ball& other) {
    double oradius = other.get_radius();
    Vector2d opos = vsum(other.get_pos(), Vector2d(oradius, oradius));
    double myx = physical_object::x + radius;
    double myy = physical_object::y + radius;
    double dist = sqrt(sq(myx - opos.x) + sq(myy - opos.y));
    if (dist < radius + oradius) {
        double omass = other.get_mass();
        Vector2d ovel = other.get_velocity();
        Vector2d vf1 = vsum(rprod(2*omass, ovel), rprod(mass-omass, physical_object::velocity));
        vf1 = rdiv(mass + omass, vf1);
        Vector2d vf2 = vsum(rprod(2*mass, physical_object::velocity), rprod(omass-mass, ovel));
        vf2 = rdiv(mass + omass, vf2);
        physical_object::velocity = vf1;
        other.change_velocity(vf2);
    }
}

int main() {
    sf::RenderWindow window(sf::VideoMode(video_max_x, video_max_y), "Bouncing balls");
    sf::VertexArray window_bg(sf::Quads, 4);
    int siz;
    double radius;

    window_bg[0].position = sf::Vector2f(0, 0);
    window_bg[1].position = sf::Vector2f(video_max_x, 0);
    window_bg[2].position = sf::Vector2f(video_max_x, video_max_y);
    window_bg[3].position = sf::Vector2f(0, video_max_y);

    vector<physical_object*> objs;
    vector<sf::CircleShape*> shapes;
    objs.resize(2);
    shapes.resize(2);

    objs[0] = new ball(200.0, 200.0, 20.0, 20.0);
    objs[0]->add_velocity(Vector2d(20.0, 0.0));
    shapes[0] = new sf::CircleShape(20.0);
    Vector2d vect = objs[0]->get_pos();
    shapes[0]->setPosition(vect.x, vect.y);
    shapes[0]->setFillColor(Blue);

    objs[1] = (physical_object*)new ball(400.0, 400.0, 20.0, 20.0);
    objs[1]->add_velocity(Vector2d(-20.0, -20.0));
    shapes[1] = new sf::CircleShape(20.0);
    vect = objs[1]->get_pos();
    shapes[1]->setPosition(vect.x, vect.y);
    shapes[1]->setFillColor(Red);

    siz = objs.size();
    cout << siz << endl;

    for (int i = 0; i < 4; i++)
        window_bg[i].color = MWhite;

    bool boo = true;
    while (window.isOpen()) {
        sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
        }
        for (int i = 0; i < siz; i++) {
            objs[i]->apply_velocity();
            objs[i]->apply_gravity();
            objs[i]->apply_air_resistance();
            objs[i]->apply_buoyancy();
            if (boo)
                objs[i]->wall_collision(video_max_x, video_max_y);
        }
        for (int i = 0; i < siz; i++) {
            for (int j = i+1; j < siz; j++) {
                if (objs[j]->type() == 'b')
                    objs[i]->ball_collision(*((ball*)objs[j]));
            }
        }
        window.clear();
        window.draw(window_bg);
        for (int i = 0; i < siz; i++) {
            vect = objs[i]->get_pos();
            shapes[i]->setPosition(vect.x, vect.y);
            window.draw(*(shapes[i]));
        }
        window.display();
        boo = !boo;
    }
}
