#ifndef __POLYGONS_H__
#define __POLYGONS_H__

#include <iostream>

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

#endif