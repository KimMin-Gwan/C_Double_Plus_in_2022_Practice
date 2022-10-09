#ifndef PolyGon_H
#define PolyGon_H
#include <string>
#include "Shape.h"
using namespace std;
class PolyGon : public Shape
{
	//friend ostream& operator<<(ostream &, PolyGonle &);
public:
	PolyGon(); //constructor 
	PolyGon(string name);
	PolyGon(int px, int py, int radius, int num_poly, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
	~PolyGon(); //destructor
	//inline function -------------------------------------------------------
	int getRadius() { return radius; } //get polygon's radius
	int getNumPoly() { return num_poly; } // get number of polygon
	//function --------------------------------------------------------------
	virtual void draw(ConsolePixelFrame cp_frame); //virtual draw function
	virtual void draw();
	void fprint(ostream& fout); //print in file
	PolyGon& operator=(PolyGon& pg); //assign operator overloading
protected:
	int radius;
	int num_poly;
};
#endif