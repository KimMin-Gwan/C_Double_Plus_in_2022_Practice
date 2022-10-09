#ifndef Circle_H
#define Circle_H
#include <string>
#include "Shape.h"
using namespace std;
#define PI 3.14159
class Circle : public Shape
{
	friend ostream& operator<<(ostream&, Circle&);
public:
	Circle(); //constructor
	Circle(string name);
	//Circle(Circle &tr);
	Circle(int px, int py, int radius, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
	~Circle(); //destructor
	//inline function ---------------------------------------------------
	int getRadius() const { return radius; } //get circle's radius
	void setRadius(int r) { radius = r; } //setting radius
	//function ------------------------------------------------------
	double getArea(); //calculate circle's area
	virtual void draw(ConsolePixelFrame cp_frame); //virtual draw function
	virtual void draw();
	void fprint(ostream& fout); //print in file
	Circle& operator=(const Circle& cir); //assign operator overloading
protected:
	int radius;
};
#endif