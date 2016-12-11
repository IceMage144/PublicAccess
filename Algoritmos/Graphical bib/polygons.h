#ifndef __POLYGONS_H__
#define __POLYGONS_H__

#include <iostream>
#include <cmath>

#define TAU 6.2831853

double sq (double x);

struct Point {
	double x, y;
	Point (): x(0), y(0) {}
	Point (double x, double y): x(x), y(y) {}
};

struct Rect {
	Point urc, llc;
	Rect (): urc(Point(0, 0)), llc(Point(0, 0)) {}
	Rect (Point urc, Point llc): urc(urc), llc(llc) {}
};

class GraphicalObject {
public:
	virtual ~GraphicalObject () {}
	virtual bool has_point (const Point& p) const = 0;
	virtual Rect boundingBox () const = 0;
	virtual GraphicalObject *clone () const = 0;
};

class Circle : public GraphicalObject {
	Point center;
	double radius, thick;
public:
	Circle (const Point& center, double radius, double thick):
		center(center), thick(thick), radius(radius) {}
	bool has_point (const Point& p) const;
	Rect boundingBox () const;
	GraphicalObject *clone () const {
		return (new Circle(*this));
	}
	void get_thick () {
		std::cout << thick << std::endl;
	}
};

class Line : public GraphicalObject {
	Point p1, p2;
	double thick;
public:
	Line (const Point& p1, const Point& p2, double thick):
		p1(p1), p2(p2), thick(thick) {}
	bool has_point (const Point& p) const;
	Rect boundingBox () const;
	GraphicalObject *clone () const {
		return (new Line(*this));
	}
};

class Group : public GraphicalObject {
	struct Node {
		GraphicalObject *obj;
		struct Node *next;
	};
	Node *Head;
public:
	Group(): Head(NULL) {}
	Group(const Group& other);
	~Group();
	void add (const GraphicalObject& obj);
	bool has_point (const Point& p) const;
	Rect boundingBox () const;
	GraphicalObject *clone () const {
		return (new Group(*this));
	}
};

class Polygon : public GraphicalObject {
	struct Node {
		Point *pt;
		struct Node *next;
	};
	Node *Head;
	bool filled;
	double thick;
public:
	Polygon (bool filled, double thick): Head(NULL), filled(filled), thick(thick) {}
	Polygon (const Polygon& other, bool filled, double thick);
	~Polygon ();
	void add (const Point& pt);
	virtual bool has_point (const Point& p) const;
	Rect boundingBox () const;
	GraphicalObject *clone () const {
		return (new Polygon(*this));
	}
};

class LineArray : public GraphicalObject {
	struct Node {
		Point *pt;
		struct Node *next;
	};
	Node *Head;
	double thick;
public:
	LineArray (double thick): Head(NULL), thick(thick) {}
	LineArray (const LineArray& other, double thick);
	void add (const Point& pt);
	bool has_point (const Point& p) const;
	Rect boundingBox () const;
	GraphicalObject *clone () const {
		return (new LineArray(*this));
	}
};

class RegularPolygon : public GraphicalObject {
	struct Node {
		Point *pt;
		struct Node *next;
	};
	Node *Head;
	Point center;
	double thick, size;
	int sides;
public:
	RegularPolygon (const Point& center, int sides, double size, double thick);
	RegularPolygon (const RegularPolygon& other);
	bool has_point (const Point& p) const;
	Rect boundingBox () const;
	GraphicalObject *clone () const {
		return (new RegularPolygon(*this));
	}
};

class Ellipse : public GraphicalObject {
	Point f1, f2, center;
	double a, b, angle, thick;
public:
	Ellipse (const Point& center, double angle, double a, double b, double thick):
		center(center), angle(angle), a(a), b(b), thick(thick) {
		double recoilx = sqrt(fabs(sq(a)-sq(b)))*cos(angle);
		double recoily = sqrt(fabs(sq(a)-sq(b)))*sin(angle);
		f1 = Point(center.x+recoilx, center.y+recoily);
		f2 = Point(center.x-recoilx, center.y-recoily);
	}
	Ellipse (const Ellipse& other);
	bool has_point (const Point& p) const;
	Rect boundingBox () const;
	GraphicalObject *clone () const {
		return (new Ellipse(*this));
	}
};

#endif
