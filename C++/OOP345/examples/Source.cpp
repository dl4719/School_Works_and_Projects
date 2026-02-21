#include <iostream>

using namespace std;

class Polygon {
public:
	virtual void show() {
		cout << "It is a polygon" << endl;
	}
};

class Hexagon : public Polygon {
public:
	void show() {
		cout << "Hexagon is a 6 sided polygon" << endl;
	}
};

class Pentagon : public Polygon {
public:
	void show() {
		cout << "Pentagon is a 5 sided polygon" << endl;
	}
};

int main() {
	Polygon* P;
	Hexagon h;
	Pentagon p;
	P = &h;
	P->show();
	P = &p;
	P->show();

	return 0;
}