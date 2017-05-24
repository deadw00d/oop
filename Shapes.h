#pragma once

#include <iostream>
#include "Base.h"
#include <cmath>
#include "Container.h"

class Point : public Named, public Shape {
public:
	Point(double _x, double _y);
	double getX();
	double getY();
protected:
	void print(std::ostream& out);
	double x;
	double y;
};

Point::Point(double _x, double _y) : Named("Point") {
	x = _x;
	y = _y;
}

void Point::print(std::ostream& out) {
	out << "Name: " << name << ", x: " << x << ", y: " << y; 
	return;
}

double Point::getX() {
	return x;
}

double Point::getY() {
	return y;
}

class Circle : public Named, public Shape {
public:
	Circle(double _x, double _y, double radius);
	~Circle();
protected:
	void print(std::ostream& out);
private:
	Point * center;
	double radius;
	double space;
};

Circle::Circle(double _x, double _y, double _radius) : Named("Circle") {
	radius = _radius;
	if (radius <= 0) throw "Cant create circle. Wrong radius.";
	center = new Point(_x, _y);
	radius = _radius;
	space = radius * radius * M_PI;
}

Circle::~Circle() {
	delete center;
}

void Circle::print(std::ostream& out) {
	out << "Name: " << name << " Center: (" << *center << ") Radius: " << radius << " Space: " << space; 
	return;
}

class Rect : virtual public Named, public Shape {
public:
	Rect(double _x1, double _y1, double _x2, double _y2);
	~Rect();
protected:
	void print(std::ostream& out);
	Point * A;
	Point * B;
	double space;
};

Rect::Rect(double _x1, double _y1, double _x2, double _y2) : Named("Rect") {
	A = new Point(_x1, _y1);
	B = new Point(_x2, _y2);
	space = sqrt((A->getX()-B->getX())*(A->getX()-B->getX()))*sqrt((A->getY()-B->getY())*(A->getY()-B->getY()));
}

Rect::~Rect() {
	delete A;
	delete B;
}

void Rect::print(std::ostream& out) {
	out << "Name: " << name << " A: (" << *A << ") B: (" << *B << ") Space: " << space; 
	return;
}


class Square : public Rect {
public:
	Square(double _x1, double _y1, double _x2, double _y2);
};

Square::Square(double _x1, double _y1, double _x2, double _y2) : Named("Square"), Rect(_x1, _y1, _x2, _y2) {
	double width = sqrt((A->getX()-B->getX())*(A->getX()-B->getX()));
	double height = sqrt((A->getY()-B->getY())*(A->getY()-B->getY()));
	if (width != height) throw "Cant create square. Wrong points";
}


class Polyline: virtual public Named, public Shape {
public:
	Polyline();
	~Polyline();
	void addPoint(Point * point);
protected:
	void print(std::ostream& out);
	Container<Point*> * line;
	double length;
};

Polyline::Polyline() : Named("Polyline") {
	line = new Container<Point*>;
	length = 0;
}

Polyline::~Polyline() {
	line->clear();
	delete line;
}

void Polyline::addPoint(Point * point) {
	line->pushLast(point);
	unsigned int size = line->getCount();
	if ( size != 1) {
		//прибавляем длину новой линии
		double x1 = line->getItem(size-2)->getX();
		double y1 = line->getItem(size-2)->getY();
		double x2 = line->getItem(size-1)->getX();
		double y2 = line->getItem(size-1)->getY();
		length += sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	}
}

void Polyline::print(std::ostream& out) {
	std::cout << "\nPolyline Length:" << length << std::endl << "Polyline points: \n";
	for (int i = 0; i < line->getCount(); i++) {
		std::cout << *line->getItem(i) << std::endl;
	}
	std::cout << "Polyline printed\n";
}

class Polygon: public Polyline {
public:
	Polygon() : Named("Polygon"), Polyline() {};
	void print(std::ostream& out);
protected:
	double getPerimeter();
};

double Polygon::getPerimeter() {
	unsigned int size = line->getCount();
	double tmp;
	if (size <= 1) return 0;
	double x1 = line->getItem(0)->getX();
	double y1 = line->getItem(0)->getY();
	double x2 = line->getItem(size-1)->getX();
	double y2 = line->getItem(size-1)->getY();
	tmp = sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
	return length + tmp;
}

void Polygon::print(std::ostream& out) {
	std::cout << "\nPolygon perimeter: " << getPerimeter() << std::endl << "\nPolygon points: \n";
	for (int i = 0; i < line->getCount(); i++) {
		std::cout << *line->getItem(i) << std::endl;
	}
	std::cout << "Polygon printed\n";
}
