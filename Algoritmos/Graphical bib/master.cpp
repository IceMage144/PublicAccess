#include "polygons.h"
#include "pgmdrawer.h"
#include <iostream>

int main () {
	Point pt1(0,0);
	Point pt2(0,7);
	Point pt3(3,0);
	Point pt4(1,2);
	Group G;
	Circle circ(pt1, 3, 0.5);
	Circle circ2(pt2, 3, 1);
	Line line(pt1, pt2, 2);
	Line line2(pt1, pt4, 2);
	G.add(circ);
	G.add(circ2);
	//G.add(line);
	//G.add(line2);
	Rect box = G.boundingBox();
	std::cout << box.llc.x << ", " << box.llc.y << ":";
	std::cout << box.urc.x << ", " << box.urc.y << std::endl;
	FILE *f = fopen("image.pgm", "w");
	Canvas c;
	c.save_pgm(G, f, 5, 3);
	fclose(f);
	return 0;
}