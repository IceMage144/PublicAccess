#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>

//Define some constants
#define video_max_x 1000
#define video_max_y 730
#define graph_max_x 1000
#define graph_max_y 530
#define graph_min_x 0
#define graph_min_y 0
#define plot_min_x 30
#define plot_max_y 500

//define some colors
#define LightGray sf::Color(192, 192, 192)
#define DarkGray sf::Color(64, 64, 64)
#define DarkBlue sf::Color(68, 68, 249)
#define Black sf::Color::Black
#define White sf::Color::White

std::vector<char> input;

int checkForKey (sf::Event event, int *maxplot, int *total) {
	if (event.key.code == sf::Keyboard::BackSpace && input.size() > 0) {
		input.pop_back();
		return 0;
	}
	else if (event.key.code == sf::Keyboard::Return) {
		*total = 0;
		std::string strAux (input.begin(), input.end());
		*maxplot = atoi(strAux.c_str());
		input.clear();
		return 1;
	}
	else if (input.size() < 5) {
		if (event.key.code == sf::Keyboard::Num0 || event.key.code == sf::Keyboard::Numpad0)
			input.push_back('0');
		else if (event.key.code == sf::Keyboard::Num1 || event.key.code == sf::Keyboard::Numpad1)
			input.push_back('1');
		else if (event.key.code == sf::Keyboard::Num2 || event.key.code == sf::Keyboard::Numpad2)
			input.push_back('2');
		else if (event.key.code == sf::Keyboard::Num3 || event.key.code == sf::Keyboard::Numpad3)
			input.push_back('3');
		else if (event.key.code == sf::Keyboard::Num4 || event.key.code == sf::Keyboard::Numpad4)
			input.push_back('4');
		else if (event.key.code == sf::Keyboard::Num5 || event.key.code == sf::Keyboard::Numpad5)
			input.push_back('5');
		else if (event.key.code == sf::Keyboard::Num6 || event.key.code == sf::Keyboard::Numpad6)
			input.push_back('6');
		else if (event.key.code == sf::Keyboard::Num7 || event.key.code == sf::Keyboard::Numpad7)
			input.push_back('7');
		else if (event.key.code == sf::Keyboard::Num8 || event.key.code == sf::Keyboard::Numpad8)
			input.push_back('8');
		else if (event.key.code == sf::Keyboard::Num9 || event.key.code == sf::Keyboard::Numpad9)
			input.push_back('9');
		return 0;
	}
}

int main() {
	int face, total = 0;
	int ocurr[6];
	int maxplot = 1;
	sf::Color colors[] = {sf::Color::Red,
						  sf::Color::Blue,
						  sf::Color(204, 0, 102),
						  sf::Color(0, 204, 0),
						  sf::Color(255, 128, 0),
						  Black};

    for (int i = 0; i < 6; i++)
    	ocurr[i] = 0;

    sf::RenderWindow window(sf::VideoMode(video_max_x, video_max_y), "Week law of big numbers simulator");
    window.setKeyRepeatEnabled(false);

    sf::Font font;
	if (!font.loadFromFile("font.ttf"))
	{
	    std::cout << "Erro\n";
	}

    

    //Creating the objects
    sf::VertexArray window_bg(sf::Quads, 4);
    sf::VertexArray graph_bg(sf::Quads, 4);
    std::vector<sf::Vertex> vertices[6];
    sf::VertexArray Grid(sf::Lines, 12);
    sf::VertexArray HUD(sf::Quads, 12);
    sf::Text text[10];

	//Defining the vertices of the window background
	window_bg[0].position = sf::Vector2f(0, 0);
	window_bg[1].position = sf::Vector2f(video_max_x, 0);
	window_bg[2].position = sf::Vector2f(video_max_x, video_max_y);
	window_bg[3].position = sf::Vector2f(0, video_max_y);

	//Defining the color of the window background
	window_bg[0].color = DarkBlue;
	window_bg[1].color = DarkBlue;
	window_bg[2].color = DarkBlue;
	window_bg[3].color = DarkBlue;

	//Defining the vertices of the graph background
	graph_bg[0].position = sf::Vector2f(graph_min_x, graph_min_y);
	graph_bg[1].position = sf::Vector2f(graph_max_x, graph_min_y);
	graph_bg[2].position = sf::Vector2f(graph_max_x, graph_max_y);
	graph_bg[3].position = sf::Vector2f(graph_min_x, graph_max_y);

	//Defining the color of the graph background
	graph_bg[0].color = White;
	graph_bg[1].color = White;
	graph_bg[2].color = White;
	graph_bg[3].color = White;

	//Creating a grid
	//y axis
	Grid[0].position = sf::Vector2f(plot_min_x, graph_min_y);
	Grid[1].position = sf::Vector2f(plot_min_x, plot_max_y);
	//x axis
	Grid[2].position = sf::Vector2f(plot_min_x, plot_max_y);
	Grid[3].position = sf::Vector2f(graph_max_x, plot_max_y);
	//3/4 line
	Grid[4].position = sf::Vector2f(plot_min_x, graph_min_y+(plot_max_y-graph_min_y)*3/4);
	Grid[5].position = sf::Vector2f(graph_max_x, graph_min_y+(plot_max_y-graph_min_y)*3/4);
	//1/2 line
	Grid[6].position = sf::Vector2f(plot_min_x, graph_min_y+(plot_max_y-graph_min_y)/2);
	Grid[7].position = sf::Vector2f(graph_max_x, graph_min_y+(plot_max_y-graph_min_y)/2);
	//1/4 line
	Grid[8].position = sf::Vector2f(plot_min_x, graph_min_y+(plot_max_y-graph_min_y)/4);
	Grid[9].position = sf::Vector2f(graph_max_x, graph_min_y+(plot_max_y-graph_min_y)/4);
	//1/6 line
	Grid[10].position = sf::Vector2f(plot_min_x, graph_min_y+(plot_max_y-graph_min_y)*5/6);
	Grid[11].position = sf::Vector2f(graph_max_x, graph_min_y+(plot_max_y-graph_min_y)*5/6);

	Grid[0].color = DarkGray;
	Grid[1].color = DarkGray;
	Grid[2].color = DarkGray;
	Grid[3].color = DarkGray;
	Grid[4].color = LightGray;
	Grid[5].color = LightGray;
	Grid[6].color = LightGray;
	Grid[7].color = LightGray;
	Grid[8].color = LightGray;
	Grid[9].color = LightGray;
	Grid[10].color = Black;
	Grid[11].color = Black;

	//Creating a HUD
	//Top line
	HUD[0].position = sf::Vector2f(graph_min_x, graph_max_y);
	HUD[1].position = sf::Vector2f(graph_max_x, graph_max_y);
	HUD[2].position = sf::Vector2f(graph_max_x, graph_max_y+3);
	HUD[3].position = sf::Vector2f(graph_min_x, graph_max_y+3);
	//Number box
	HUD[4].position = sf::Vector2f(graph_min_x+100, graph_max_y+75);
	HUD[5].position = sf::Vector2f(graph_min_x+300, graph_max_y+75);
	HUD[6].position = sf::Vector2f(graph_min_x+300, graph_max_y+105);
	HUD[7].position = sf::Vector2f(graph_min_x+100, graph_max_y+105);
	//Plot box
	HUD[8].position = sf::Vector2f(graph_min_x+150, graph_max_y+125);
	HUD[9].position = sf::Vector2f(graph_min_x+250, graph_max_y+125);
	HUD[10].position = sf::Vector2f(graph_min_x+250, graph_max_y+155);
	HUD[11].position = sf::Vector2f(graph_min_x+150, graph_max_y+155);

	HUD[0].color = Black;
	HUD[1].color = Black;
	HUD[2].color = Black;
	HUD[3].color = Black;
	HUD[4].color = White;
	HUD[5].color = White;
	HUD[6].color = White;
	HUD[7].color = White;
	HUD[8].color = LightGray;
	HUD[9].color = LightGray;
	HUD[10].color = LightGray;
	HUD[11].color = LightGray;

	//Creating the text
	for (int i = 0; i < 10; i++) {
    	text[i].setFont(font);
    	text[i].setColor(Black);
    }

    text[0].setCharacterSize(15);
    text[1].setCharacterSize(15);
    text[2].setCharacterSize(15);
    text[3].setCharacterSize(15);
    text[4].setCharacterSize(15);
    text[5].setCharacterSize(15);
    text[6].setCharacterSize(24);
	text[7].setCharacterSize(24);
	text[8].setCharacterSize(24);
	text[9].setCharacterSize(24);


    text[0].setPosition(sf::Vector2f(graph_min_x+15, graph_min_y));
    text[1].setPosition(sf::Vector2f(graph_min_x+15, plot_max_y));
    text[2].setPosition(sf::Vector2f(graph_min_x, graph_min_y+(plot_max_y-graph_min_y)*3/4-7));
    text[3].setPosition(sf::Vector2f(graph_min_x, graph_min_y+(plot_max_y-graph_min_y)/2-7));
    text[4].setPosition(sf::Vector2f(graph_min_x, graph_min_y+(plot_max_y-graph_min_y)/4-7));
    text[5].setPosition(sf::Vector2f(graph_min_x, graph_min_y+(plot_max_y-graph_min_y)*5/6-7));
    text[6].setPosition(sf::Vector2f(graph_min_x+164, graph_max_y+75));
    text[7].setPosition(sf::Vector2f(graph_min_x+170, graph_max_y+125));
    text[8].setPosition(sf::Vector2f(graph_min_x+400, graph_max_y+25));
    text[9].setPosition(sf::Vector2f(graph_min_x+90, graph_max_y+25));

    text[0].setString("1");
    text[1].setString("0");
    text[2].setString("1/4");
    text[3].setString("1/2");
    text[4].setString("3/4");
    text[5].setString("1/6");
    text[7].setString("Plot");
    text[8].setString("Weak law of big numbers simulator");
    text[9].setString("Number of throws");

	//Loop
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed) {
            	if (checkForKey(event, &maxplot, &total)) {
            		for (int i = 0; i < 6; i++) {
            			vertices[i].clear();
            			ocurr[i] = 0;
            		}
            	}
            }
        }

        std::string strAux (input.begin(), input.end());
        text[6].setString(strAux);

        //Randomizing
        if (total <= maxplot) {
	        face = rand()%6;
	        ocurr[face]++;
	        total++;
	        for (int i = 0; i < 6; i++)
	        	vertices[i].push_back(sf::Vertex(sf::Vector2f(plot_min_x+(graph_max_x-plot_min_x)*total/maxplot, plot_max_y-(plot_max_y-graph_min_y)*ocurr[i]/total), colors[i]));
	    }

	    //Drawing
        window.clear();
        window.draw(window_bg);
        window.draw(graph_bg);
        window.draw(Grid);
        window.draw(HUD);
        for (int i = 0; i < 10; i++)
        	window.draw(text[i]);
        for (int i = 0; i < 6; i++)
        	window.draw(&vertices[i][0], total, sf::LinesStrip);
        window.display();
    }

    return 0;
}