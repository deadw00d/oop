#pragma once
#include <string>
#include <iostream>

class Printable {
public:
	friend std::ostream& operator<<( std::ostream& out, Printable & shape );
protected:
	virtual void print(std::ostream& out) = 0;
};

std::ostream& operator <<(std::ostream& out, Printable& object ) {
	object.print(out);
	return out;
}


class Named: virtual public Printable {
public:
	Named(std::string const _name);
	virtual ~Named() {};
protected:
	std::string name;
private:
	void print(std::ostream& out);
};

Named::Named(std::string const _name) {
	name = _name;
}

void Named::print(std::ostream & out) {
	out << name;
	return;
}


class Shape: virtual public Printable {
public:
	Shape();
	virtual ~Shape();
	static unsigned int getCount();
private:
	virtual void print(std::ostream& out) = 0;
	static unsigned int count;
};

Shape::Shape() {
	count++;
}

Shape::~Shape() {
	count--;
}

unsigned int Shape::getCount() {
	return count;
}

unsigned int Shape::count = 0;

