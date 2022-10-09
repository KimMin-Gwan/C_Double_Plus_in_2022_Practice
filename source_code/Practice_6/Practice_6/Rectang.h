#ifndef Rectang_H
#define Rectang_H
#include <string>
#include "Shape.h"
using namespace std;
class Rectang : public Shape
{
	//friend ostream& operator<<(ostream &, Rectangle &);
public:
	Rectang(); //constructor
	Rectang(string name);
	Rectang(int px, int py, int width, int length, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
	~Rectang(); //destructor
	//inline function ----------------------------------------------------------
	int getWidth() { return width; } //get width 
	int getLength() { return length; } //get length
	//funtion -----------------------------------------------------------------
	double getArea(); //calculate rectangle's area
	virtual void draw(ConsolePixelFrame cp_frame); //virtual draw function
	virtual void draw();
	void fprint(ostream& fout);  //print in file
	Rectang& operator=(Rectang& rec); //assign operator overloading
protected:
	int width; 
	int length;
};
#endif