#ifndef CYLINDER_H
#define CYLINDER_H
#include <string>
#include "Shape.h"
using namespace std;
class Cylinder : public Shape
{
	friend ostream& operator<<(ostream&, const Cylinder&);
public:
	Cylinder(); //constuctor 
	Cylinder(string name);
	Cylinder(int px, int py, int radius, int ang, int height, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
	//Cylinder(Cylinder &cyl);
	~Cylinder(); //destructor
	//inline function -------------------------------------------------------
	int getRadius() const { return radius; } //get cylinder's radius
	int getHeight() const { return height; } //get cylinder's height
	void setRadius(int r) { radius = r; } //setting cylinder's radius
	void setHeight(int h) { height = h; } //setting cylinder's height
	//function --------------------------------------------------------------
	//double getArea(); //calculate cylinder's volume
	virtual void draw(ConsolePixelFrame cp_frame); // virtual draw function
	virtual void draw(); // used for testing of late binding
	void fprint(ostream& fout); //print in file
	Cylinder& operator=(const Cylinder& cir); //assign operator overloading
protected:
	int radius;
	int height;
};
#endif