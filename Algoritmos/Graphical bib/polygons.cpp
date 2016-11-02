#include "polygons.h"
#include <cmath>
#include <cstdio>

double sq (double x) {
	return x*x;
}

bool areIntersecting (const Point& v1p1, const Point& v1p2, const Point& v2p1, const Point& v2p2) {
	double a1, b1, c1, d1, d2, a2, b2, c2, d3, d4;
	a1 = v1p1.y-v1p2.y;
	b1 = v1p1.x-v1p2.y;
	c1 = v1p1.y*v1p2.x - v1p1.x*v1p2.y;
	d1 = a1*v2p1.x + b1*v2p1.y + c1;
	d2 = a1*v2p2.x + b1*v2p2.y + c1;
	a2 = v2p1.y-v2p2.y;
	b2 = v2p1.x-v2p2.y;
	c2 = v2p1.y*v2p2.x - v2p1.x*v2p2.y;
	d3 = a2*v1p1.x + b2*v1p1.y + c2;
	d4 = a1*v1p2.x + b1*v1p2.y + c1;
	if ((d1 < 0 && d2 > 0) || (d1 > 0 && d2 < 0))
		if ((d3 < 0 && d4 > 0) || (d3 > 0 && d4 < 0))
			return true;
	return false;
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
		/*double ythick = thick*1.0/sin(fabs(90.0-atan(deltay/deltax)));
		double det = p2.x*p1.y + p1.x*p2.y;
		if (deltax*p.y+deltay*p.x+(det-ythick) > 0)*/
		double det = p2.x*p1.y + p1.x*p2.y;
		distPL = std::fabs(deltax*p.y+deltay*p.x+det)/sqrt(sq(deltax)+sq(deltay));
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
	box.llc.x = fmin(p1.x, p2.x)-thick;
	box.llc.y = fmin(p1.y, p2.y)-thick;
	box.urc.x = fmax(p1.x, p2.x)+thick;
	box.urc.y = fmax(p1.y, p2.y)+thick;
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
		if (cell->obj->has_point(p)) {
			printf("%p have (%f, %f)\n", cell, p.x, p.y);
			return true;
		}
	printf("I do not have (%f, %f)\n", p.x, p.y);
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
        if(aux.urc.y > box.urc.y)
            box.urc.y = aux.urc.y;
	}
	return box;
}

Polygon::Polygon (const Polygon& other, bool filled, double thick):
	filled(filled), thick(thick) {
	for (Node *cell = other.Head; cell != NULL; cell = cell->next) {
		add(*cell->pt);
	}
}

Polygon::~Polygon () {
	for (Node *temp, *cell = Head; cell != NULL; cell = temp) {
		temp = cell->next;
		delete cell->pt;
		delete cell;
	}
}

void Polygon::add (const Point& pt) {
	Node *cell = new Node;
	cell->pt = new Point(pt.x, pt.y);
	cell->next = Head;
	Head = cell;
}

bool Polygon::has_point (const Point& p) const {
	if (Head == NULL)
		return false;
	Node *cell = Head;
	for (Node *cell2 = Head->next; cell2 != NULL; cell = cell2, cell2 = cell2->next) {
		Line line(*cell->pt, *cell2->pt, thick);
		if (line.has_point(p))
			return true;
	}
	Line line(*cell->pt, *Head->pt, thick);
	if (line.has_point(p))
		return true;
	if (filled == true) {
		Rect box = boundingBox();
		Point raypt1(box.llc.x, p.y);
		Point raypt2(p.x, p.y);
		int count = 0;
		cell = Head;
		for (Node *cell2 = Head->next; cell2 != NULL; cell = cell2, cell2 = cell2->next) {
			if (areIntersecting(*cell->pt, *cell2->pt, raypt1, raypt2))
				count++;
		}
		if (areIntersecting(*cell->pt, *Head->pt, raypt1, raypt2))
			count++;
		if (count%2)
			return true;
		return false;
	}
}

Rect Polygon::boundingBox () const {
	Rect box;
	for (Node *cell = Head; cell != NULL; cell = cell->next) {
		if(cell->pt->x < box.llc.x)
            box.llc.x = cell->pt->x;
        if(cell->pt->y < box.llc.y)
            box.llc.y = cell->pt->y;
        if(cell->pt->x > box.urc.x)
            box.urc.x = cell->pt->x;
        if(cell->pt->y > box.urc.y)
            box.urc.y = cell->pt->y;
	}
	return box;
}

CurvedLine::CurvedLine (const CurvedLine& other, double thick):
	thick(thick) {
	for (Node *cell = other.Head; cell != NULL; cell = cell->next) {
		add(*cell->pt);
	}
}

bool CurvedLine::has_point (const Point& p) const {
	if (Head == NULL)
		return false;
	Node *cell = Head;
	for (Node *cell2 = Head->next; cell2 != NULL; cell = cell2, cell2 = cell2->next) {
		Line line(*cell->pt, *cell2->pt, thick);
		if (line.has_point(p))
			return true;
	}
	Line line(*cell->pt, *Head->pt, thick);
	if (line.has_point(p))
		return true;
}