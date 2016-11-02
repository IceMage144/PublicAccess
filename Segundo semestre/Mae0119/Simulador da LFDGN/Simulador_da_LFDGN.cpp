#include <SFML/Graphics.hpp>
#include <vector>
#include <cstdlib>
#include <iostream>
#include <string>
#include <cmath>

//Define some constants
#define video_max_x 1000
#define video_max_y 730
#define graph_max_x 1000
#define graph_max_y 530
#define graph_min_x 0
#define graph_min_y 0
#define plot_max_x 950
#define plot_min_x 50
#define plot_min_y 30
#define plot_max_y 500

//define some colors
#define LightGray sf::Color(192, 192, 192)
#define DarkGray sf::Color(64, 64, 64)
#define Gray sf::Color(128, 128, 128)
#define DarkBlue sf::Color(68, 68, 249)
#define MBlack sf::Color(0, 0, 0)
#define MWhite sf::Color(255, 255, 255)
#define Blue sf::Color(0, 0, 255)
#define Red sf::Color(220, 20, 60)
#define Orange sf::Color(255, 128, 0)
#define Green sf::Color(0, 201, 87)
#define Purple sf::Color(128, 0, 128)

std::vector<char> input;

int checkForMouse (sf::Window *window) {
	sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
	float x = localPosition.x;
	float y = localPosition.y;
	if (x > graph_min_x+150 && x < graph_min_x+250 && y > graph_max_y+125 && y < graph_max_y+155) {
		return 1;
	}
	return 0;
}

int checkForKey (sf::Event event, int *maxplot, int *total, sf::Window *window) {
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
	int maxplot = 0;
	int buttonFrame = 0;
	sf::Color colors[] = {Red,
						  Blue,
						  Purple,
						  Green,
						  Orange,
						  Gray};

	for (int i = 0; i < 6; i++)
		ocurr[i] = 0;

	sf::RenderWindow window(sf::VideoMode(video_max_x, video_max_y), "Week law of large numbers simulator");
	window.setKeyRepeatEnabled(false);

	sf::Font font;
	if (!font.loadFromFile("font.ttf")) {
		std::cout << "Erro\n";
	}

	//Creating the objects
	sf::VertexArray window_bg(sf::Quads, 4);
	sf::VertexArray graph_bg(sf::Quads, 4);
	std::vector<sf::Vertex> vertices[6];
	sf::VertexArray Grid(sf::Lines, 12);
	sf::VertexArray HUD(sf::Quads, 12);
	sf::VertexArray Legend(sf::Quads, 24);
	sf::VertexArray Details(sf::Triangles, 6);
	sf::Text text[18];

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
	graph_bg[0].color = MWhite;
	graph_bg[1].color = MWhite;
	graph_bg[2].color = MWhite;
	graph_bg[3].color = MWhite;

	//Creating a grid
	//y axis
	Grid[0].position = sf::Vector2f(plot_min_x, plot_min_y);
	Grid[1].position = sf::Vector2f(plot_min_x, plot_max_y);
	//x axis
	Grid[2].position = sf::Vector2f(plot_min_x, plot_max_y);
	Grid[3].position = sf::Vector2f(plot_max_x, plot_max_y);
	//3/4 line
	Grid[4].position = sf::Vector2f(plot_min_x, plot_min_y+(plot_max_y-plot_min_y)*3/4);
	Grid[5].position = sf::Vector2f(plot_max_x, plot_min_y+(plot_max_y-plot_min_y)*3/4);
	//1/2 line
	Grid[6].position = sf::Vector2f(plot_min_x, plot_min_y+(plot_max_y-plot_min_y)/2);
	Grid[7].position = sf::Vector2f(plot_max_x, plot_min_y+(plot_max_y-plot_min_y)/2);
	//1/4 line
	Grid[8].position = sf::Vector2f(plot_min_x, plot_min_y+(plot_max_y-plot_min_y)/4);
	Grid[9].position = sf::Vector2f(plot_max_x, plot_min_y+(plot_max_y-plot_min_y)/4);
	//1/6 line
	Grid[10].position = sf::Vector2f(plot_min_x, plot_min_y+(plot_max_y-plot_min_y)*5/6);
	Grid[11].position = sf::Vector2f(plot_max_x, plot_min_y+(plot_max_y-plot_min_y)*5/6);

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
	Grid[10].color = MBlack;
	Grid[11].color = MBlack;

	//Creating a HUD
	//Top line
	HUD[0].position = sf::Vector2f(graph_min_x, graph_max_y);
	HUD[1].position = sf::Vector2f(graph_max_x, graph_max_y);
	HUD[2].position = sf::Vector2f(graph_max_x, graph_max_y+5);
	HUD[3].position = sf::Vector2f(graph_min_x, graph_max_y+5);
	//Number box
	HUD[4].position = sf::Vector2f(graph_min_x+100, graph_max_y+75);
	HUD[5].position = sf::Vector2f(graph_min_x+300, graph_max_y+75);
	HUD[6].position = sf::Vector2f(graph_min_x+300, graph_max_y+105);
	HUD[7].position = sf::Vector2f(graph_min_x+100, graph_max_y+105);
	//Plot button
	HUD[8].position = sf::Vector2f(graph_min_x+150, graph_max_y+125);
	HUD[9].position = sf::Vector2f(graph_min_x+250, graph_max_y+125);
	HUD[10].position = sf::Vector2f(graph_min_x+250, graph_max_y+155);
	HUD[11].position = sf::Vector2f(graph_min_x+150, graph_max_y+155);

	HUD[0].color = LightGray;
	HUD[1].color = LightGray;
	HUD[2].color = MBlack;
	HUD[3].color = MBlack;
	HUD[4].color = MWhite;
	HUD[5].color = MWhite;
	HUD[6].color = MWhite;
	HUD[7].color = MWhite;
	HUD[8].color = Gray;
	HUD[9].color = Gray;
	HUD[10].color = Gray;
	HUD[11].color = Gray;

	//Graph details
	Details[0].position = sf::Vector2f(plot_min_x, plot_min_y-5);
	Details[1].position = sf::Vector2f(plot_min_x+5, plot_min_y+5);
	Details[2].position = sf::Vector2f(plot_min_x-5, plot_min_y+5);
	Details[3].position = sf::Vector2f(plot_max_x+5, plot_max_y);
	Details[4].position = sf::Vector2f(plot_max_x-5, plot_max_y-5);
	Details[5].position = sf::Vector2f(plot_max_x-5, plot_max_y+5);

	Details[0].color = MBlack;
	Details[1].color = MBlack;
	Details[2].color = MBlack;
	Details[3].color = MBlack;
	Details[4].color = MBlack;
	Details[5].color = MBlack;

	//Graph legend
	for (int i = 0; i < 6; i++) {
		Legend[4*i].position = sf::Vector2f(graph_min_x+400 + 80*i, graph_max_y+75);
		Legend[4*i+1].position = sf::Vector2f(graph_min_x+460 + 80*i, graph_max_y+75);
		Legend[4*i+2].position = sf::Vector2f(graph_min_x+460 + 80*i, graph_max_y+135);
		Legend[4*i+3].position = sf::Vector2f(graph_min_x+400 + 80*i, graph_max_y+135);
	}

	for (int i = 0; i < 4; i++)
		Legend[i].color = Red;
	for (int i = 0; i < 4; i++)
		Legend[i+4].color = Blue;
	for (int i = 0; i < 4; i++)
		Legend[i+8].color = Purple;
	for (int i = 0; i < 4; i++)
		Legend[i+12].color = Green;
	for (int i = 0; i < 4; i++)
		Legend[i+16].color = Orange;
	for (int i = 0; i < 4; i++)
		Legend[i+20].color = Gray;


	//Creating the text
	for (int i = 0; i < 18; i++) {
		text[i].setFont(font);
		text[i].setFillColor(MBlack);
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
	text[10].setCharacterSize(15);
	text[11].setCharacterSize(15);
	text[12].setCharacterSize(50);
	text[13].setCharacterSize(50);
	text[14].setCharacterSize(50);
	text[15].setCharacterSize(50);
	text[16].setCharacterSize(50);
	text[17].setCharacterSize(50);

	text[0].setPosition(sf::Vector2f(plot_min_x-15, plot_min_y));
	text[1].setPosition(sf::Vector2f(plot_min_x-15, plot_max_y));
	text[2].setPosition(sf::Vector2f(plot_min_x-30, plot_min_y+(plot_max_y-plot_min_y)*3/4-7));
	text[3].setPosition(sf::Vector2f(plot_min_x-30, plot_min_y+(plot_max_y-plot_min_y)/2-7));
	text[4].setPosition(sf::Vector2f(plot_min_x-30, plot_min_y+(plot_max_y-plot_min_y)/4-7));
	text[5].setPosition(sf::Vector2f(plot_min_x-30, plot_min_y+(plot_max_y-plot_min_y)*5/6-7));
	text[6].setPosition(sf::Vector2f(graph_min_x+164, graph_max_y+75));
	text[7].setPosition(sf::Vector2f(graph_min_x+170, graph_max_y+125));
	text[8].setPosition(sf::Vector2f(graph_min_x+590, graph_max_y+25));
	text[9].setPosition(sf::Vector2f(graph_min_x+90, graph_max_y+25));
	text[10].setPosition(sf::Vector2f(plot_min_x-45, plot_min_y-30));
	text[11].setPosition(sf::Vector2f(plot_max_x-15, plot_max_y+10));
	text[12].setPosition(sf::Vector2f(graph_min_x+415, graph_max_y+72));
	text[13].setPosition(sf::Vector2f(graph_min_x+495, graph_max_y+72));
	text[14].setPosition(sf::Vector2f(graph_min_x+575, graph_max_y+72));
	text[15].setPosition(sf::Vector2f(graph_min_x+655, graph_max_y+72));
	text[16].setPosition(sf::Vector2f(graph_min_x+735, graph_max_y+72));
	text[17].setPosition(sf::Vector2f(graph_min_x+815, graph_max_y+72));

	text[0].setString("1");
	text[1].setString("0");
	text[2].setString("1/4");
	text[3].setString("1/2");
	text[4].setString("3/4");
	text[5].setString("1/6");
	text[7].setString("Plot");
	text[8].setString("Legend");
	text[9].setString("Number of rolls");
	text[10].setString("Ocurrences/rolls");
	text[11].setString("Roll");
	text[12].setString("1");
	text[13].setString("2");
	text[14].setString("3");
	text[15].setString("4");
	text[16].setString("5");
	text[17].setString("6");

	//Loop
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed) {
				if (checkForKey(event, &maxplot, &total, &window)) {
					for (int i = 0; i < 6; i++) {
						vertices[i].clear();
						ocurr[i] = 0;
					}
				}
			}
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				if (checkForMouse(&window)) {
					total = 0;
					std::string strAux (input.begin(), input.end());
					maxplot = atoi(strAux.c_str());
					input.clear();
					for (int i = 0; i < 6; i++) {
						vertices[i].clear();
						ocurr[i] = 0;
					}
				}
			}
		}

		std::string strAux (input.begin(), input.end());
		text[6].setString(strAux);

		if (!checkForMouse(&window)) {
			HUD[8].color = Gray;
			HUD[9].color = Gray;
			HUD[10].color = Gray;
			HUD[11].color = Gray;
		}
		else {
			HUD[8].color = LightGray;
			HUD[9].color = LightGray;
			HUD[10].color = LightGray;
			HUD[11].color = LightGray;
		}

		//Randomizing
		for (int j = 0; j < log10(maxplot); j++) {
			if (total < maxplot && maxplot != 0) {
				face = rand()%6;
				ocurr[face]++;
				total++;
				for (int i = 0; i < 6; i++)
					vertices[i].push_back(sf::Vertex(sf::Vector2f(plot_min_x+(plot_max_x-plot_min_x)*total/maxplot, plot_max_y-(plot_max_y-plot_min_y)*ocurr[i]/total), colors[i]));
			}
		}


		//Drawing
		window.clear();
		window.draw(window_bg);
		window.draw(graph_bg);
		window.draw(Grid);
		window.draw(HUD);
		window.draw(Details);
		window.draw(Legend);
		for (int i = 0; i < 18; i++)
			window.draw(text[i]);
		for (int i = 0; i < 6; i++)
			window.draw(&vertices[i][0], total, sf::LinesStrip);
		window.display();
	}

	return 0;
}