#ifndef SHAPE_H
#define SHAPE_H
#include <Windows.h>
#include <iostream>
#include "Color.h"
#include "ConsolePixelDrawing.h"
using namespace std;
#define PI 3.14159
class ConsolePixelFrame;
class Shape 
{
	friend ostream& operator << (ostream& fout, Shape& shape);
public:
	Shape(); // default constructor
	Shape(string name);
	Shape(int px, int py, int angle, int pen_thickness, COLORREF color, COLORREF brush_color, string name); // constructor
	virtual ~Shape();
	//-----------------inline fucntion -----------------------------------
	int get_pos_x() const { return pos_x; } //get x position
	int get_pos_y() const { return pos_y; } //get y position 
	int get_angle() const{ return angle; } //get angle
	string get_name() { return name; } //get name 
	COLORREF get_color() { return color; } //get color 
	COLORREF get_brush_color() { return brush_color; }
	int get_pen_thickness() { return pen_thickness; }
	void set_pos_x(int x) { this->pos_x = x; } //set x position
	void set_pos_y(int y) { this->pos_y = y; } //set y position
	void set_angle(int angle) { this->angle = angle; } //set angle
	void set_name(string name) { this->name = name; } // set name
	void set_color(COLORREF color) { this->color = color; }
	void set_brush_color(COLORREF brush_color) { this->brush_color = brush_color; }
	void set_pen_thickness(int pen_thickness) { this->pen_thickness = pen_thickness; }
	//-----------------function ------------------------------------------
	virtual void draw(); //drawa fucntion
	virtual void draw(ConsolePixelFrame cp_frame); //drawa fucntion
	void fprint(ostream& fout); //self printing
	Shape& operator = (const Shape & right); //assign overloading 
protected:
	int pos_x; // position x
	int pos_y; // position y
	int angle; // degree
	string name; //name
	int pen_thickness; //radius thickness 
	COLORREF color;  // defined color
	COLORREF brush_color; //radius color
};
#endif