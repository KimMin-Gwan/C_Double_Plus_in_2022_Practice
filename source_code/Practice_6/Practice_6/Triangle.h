#ifndef TRIANGLE_H
#define TRIANGLE_H
#include <string>
#include "Shape.h"
using namespace std;
class Triangle : public Shape
{
	//friend ostream& operator<<(ostream &, Triangle &);
public:
	Triangle(); //constructor 
	Triangle(string name); 
	Triangle(int px, int py, int base, int height, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
	~Triangle();
	//inline function ---------------------------------------------------
	int getBase() { return base; } // get base
	int getHeight() { return tri_height; } // get height
	//function ---------------------------------------------------------
	//double getArea(); //calculate triangle's area
	virtual void draw(ConsolePixelFrame cp_frame); //virtual function
	virtual void draw();
	void fprint(ostream& fout); //print in file
	Triangle& operator=(const Triangle& tri); //assinge operator overloading
protected:
	int base;
	int tri_height;
};
#endif