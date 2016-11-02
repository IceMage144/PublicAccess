#include "polygons.h"
#include <cmath>
#include <cstdio>

double sq (double x) {
	return x*x;
}

bool Circle::has_point (const Point& p) const {
	double dist1 = sq(radius+thick);
	double dist2 = sq(radius-thick);
	double distpt = sq(p.x-center.x) + sq(p.y-center.y);
	if (distpt <= dist1 && distpt >= dist2)
		return true;
	return false;
}

Rect Circle::boundingBox () const {
	Rect box;
	box.llc.x = center.x - radius - thick;
	box.llc.y = center.y - radius - thick;
	box.urc.x = center.x + radius + thick;
	box.urc.y = center.y + radius + thick;
	return box;
}

bool Line::has_point (const Point& p) const {
	Point med((p1.x+p2.x)/2, (p1.y+p2.y)/2);
	double deltax = p1.x-p2.x;
	double deltay = p1.y-p2.y;
	double distPL;
	if (deltax == 0.0)
		distPL = std::abs(p.x-p1.x);
	else {
		double m = deltay/deltax;
		distPL = std::abs(p.y-m*p.x-m*p1.x-p1.y)/sqrt(1+sq(m));
	}
	double radius = sqrt(sq(p1.x-p2.x)+sq(p1.y-p2.y))/2;
	double distPM = sqrt(sq(med.x-p.x)+sq(med.y-p.y));
	if (distPM <= radius && distPL <= thick)
		return true;
	double distPP1 = sqrt(sq(p1.x-p.x)+sq(p1.y-p.y));
	double distPP2 = sqrt(sq(p2.x-p.x)+sq(p2.y-p.y));
	if (distPP1 <= thick || distPP2 <= thick)
		return true;
	return false;
}

Rect Line::boundingBox () const {
	Rect box;
	box.urc.x = fmin(p1.x, p2.x)-thick;
	box.urc.y = fmin(p1.y, p2.y)-thick;
	box.llc.x = fmax(p1.x, p2.x)+thick;
	box.llc.y = fmax(p1.y, p2.y)+thick;
	return box;
}

Group::Group (const Group& other): Head(NULL) {
	for (Node *cell = other.Head; cell != NULL; cell = cell->next) {
		add(*cell->obj);
	}
}

Group::~Group () {
	for (Node *temp, *cell = Head; cell != NULL; cell = temp) {
		temp = cell->next;
		delete cell->obj;
		delete cell;
	}
}

void Group::add (const GraphicalObject& obj) {
	Node *cell = new Node;
	cell->obj = obj.clone();
	cell->next = Head;
	Head = cell;
}

bool Group::has_point (const Point& p) const {
	for (Node *cell = Head; cell != NULL; cell = cell->next)
		if (cell->obj->has_point(p))
			return true;
	return false;
}

Rect Group::boundingBox () const {
	Rect box, aux;
	for (Node *cell = Head; cell != NULL; cell = cell->next) {
		aux = cell->obj->boundingBox();
		if(aux.llc.x < box.llc.x)
            box.llc.x = aux.llc.x;
        if(aux.llc.y < box.llc.y)
            box.llc.y = aux.llc.y;
        if(aux.urc.x > box.urc.x)
            box.urc.x = aux.urc.x;
        if(aux.urc.x > box.urc.x)
            box.urc.y = aux.urc.y;
	}
	return box;
}
