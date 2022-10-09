#ifndef Star_H
#define Star_H
#include <string>
#include "Shape.h"
using namespace std;
class Star : public Shape
{
	//friend ostream& operator<<(ostream &, PolyGonle &);
public:
	Star(); //constuctor
	Star(string name);
	Star(int px, int py, int radius, int num_vertices, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
	~Star(); //destructor
	//inline function -------------------------------------------------------------------
	int getRadius() { return radius; } //get star's radius
	int getNumPoly() { return num_vertices; } //get number of poly
	//function --------------------------------------------------------------------------
	//double getArea();  
	//PolyGonle(PolyGonle &pg);
	virtual void draw(ConsolePixelFrame cp_frame); // virtual draw function
	virtual void draw(); // // used for testing of late binding
	void fprint(ostream& fout); //prin in file
	Star& operator=(Star& pg); // assign operator overloading
protected:
	int radius;
	int num_vertices;
};
#endif