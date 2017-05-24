#pragma once

#include "Shapes.h"
#include <string>

class Factory {
public:
	static Shape * create(int num);
};

Shape * Factory::create(int num) {
	if (num == 0) return new Point(rand()%15, rand()%15);
	if (num == 1) return new Circle(rand()%15, rand()%15, rand()%15);
	if (num == 2) return new Rect(rand()%15, rand()%15, rand()%15, rand()%15);
	if (num == 3) {
		float x = rand()%15;
		float y = rand()%15;
		return new Square(x, x, y, y);
	}
	if (num == 4) {
		int size = rand()%15;
		Polyline * obj = new Polyline();
		for (int i = 0; i < size; i++) {
			obj->addPoint(new Point(rand() % 15, rand() % 15));
		}
		return obj;
	}
	if (num == 5) {
		int size = rand()%15;
		Polygon * obj = new Polygon();
		for (int i = 0; i < size; i++) {
			obj->addPoint(new Point(rand() % 15, rand() % 15));
		}
		return obj;
	}
	throw "No such figure.";
}
