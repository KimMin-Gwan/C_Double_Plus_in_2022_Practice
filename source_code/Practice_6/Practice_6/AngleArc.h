#ifndef ANGLE_ARC_H
#define ANGLE_ARC_H
#include <string>
#include "Shape.h"
using namespace std;
class AngledArc : public Shape
{
	friend ostream& operator<<(ostream& fout, AngledArc& shape);
public:
	AngledArc(); //constructor 
	AngledArc(string name);
	AngledArc(int px, int py, int radius, int ang, int start_ang, int sweep_ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name);
	//AngledArc(AngledArc &angarc);
	~AngledArc(); //destructor
	//inline function ----------------------------------------------------
	int getRadius() const { return radius; } //get Angle arc's radius
	int getStart_angle() const { return start_angle; } //get start angle in arc
	int getSweep_angle() const { return sweep_angle; } //get sweep angle in arc
	void setRadius(int r) { radius = r; } //set angle arc's radius
	void setStart_angle(int start) { start_angle = start; } //set start angle in arc
	void setSweep_angle(int sweep) { sweep_angle = sweep; } //set sweep angle in arc
	//function ----------------------------------------------------------
	virtual void draw(ConsolePixelFrame cp_frame); // virtual draw function
	virtual void draw(); // used for testing of late binding
	void fprint(ostream&); // print in file
	AngledArc& operator=(const AngledArc& cir); //assign operator overloading
protected:
	int radius;
	int start_angle;
	int sweep_angle;
};
#endif