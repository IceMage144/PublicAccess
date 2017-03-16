#include "physical_objects.h"
#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

#define video_max_x 1000
#define video_max_y 730

#define MWhite sf::Color(255, 255, 255)
#define Blue sf::Color(0, 0, 255)

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
    ball ba(50.0, 50.0, 20.0, 20.0);
    sf::CircleShape circ(ba.get_radius());
    circ.setFillColor(Blue);

    shapes.push_back(&circ);
    objs.push_back((physical_object*)&ba);
    siz = objs.size();

    for (int i = 0; i < 4; i++)
        window_bg[i].color = MWhite;

    while (window.isOpen()) {
        for (int i = 0; i < siz; i++) {
            objs[i]->apply_velocity();
            objs[i]->apply_gravity();
            objs[i]->apply_air_resistance();
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
            vector2d vect = objs[i]->get_pos();
            shapes[i]->setPosition((float)vect.x, (float)vect.y);
            window.draw(*(shapes[i]));
        }
        window.display();
    }
}
