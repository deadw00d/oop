#include <iostream>
#include "Container.h"
#include "Base.h"
#include "Shapes.h"
#include "Factory.h"

int main() {
	try {
		Container<Shape *> shapes;
		int size = 50;
		for (int i = 0; i < size; i++) {
			shapes.pushFirst(Factory::create(rand()%6));
		}
		std::cout << "Shape count " << Shape::getCount() << std::endl;
		for (int i = 0; i < size; i++) {
			std::cout << "Shape number " << i+1 << ": \n" << *shapes.getItem(i) << std::endl;
		}
		shapes.clear();
		std::cout << "All shapes deleted. Shapes count: " << Shape::getCount() << std::endl;
	} catch(char const * e) {
		std::cout << e << "\n";
	}

	return 0;
}
