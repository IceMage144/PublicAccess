#include "polygons.h"
#include "pgmdrawer.h"
#include <iostream>

int main () {
	Point pt1(0,0);
	Point pt2(0,7);
	Point pt3(3,0);
	Point pt4(0,8);
	Group G;
	Circle circ(pt1, 3, 0.2);
	Line line(pt1, pt2, 0.2);
	Line line2(pt1, pt4, 0.2);
	G.add(circ);
	G.add(line);
	G.add(line2);
	FILE *f = fopen("image.pgm", "w");
	Canvas c;
	c.save_pgm(circ, f, 5, 3);
	fclose(f);
	return 0;
}