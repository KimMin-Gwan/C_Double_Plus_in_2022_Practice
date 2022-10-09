#include "Shape.h"
ostream& operator << (ostream& ostr, Shape& shape)
{
	ostr << shape.name << ": pos(" << setw(4) << shape.get_pos_x() << ", " << 
		setw(4) << shape.get_pos_y() << "), ";
	ostr << "angle (" << setw(4) << shape.angle << "), ";
	ostr << "color (" << setw(8) << showbase << hex << uppercase << shape.color << ")" << endl;
	return ostr;
}

Shape::Shape()
{
	this->pos_x = 0; this->pos_y = 0; this->angle = 0; //init member 
	this->name = "anaymous"; this->color = RGB_BLACK; //init color is black
	this->pen_thickness = 0; this->brush_color = RGB_BLACK; // init color is black
}

Shape::Shape(string name)
{
	this->pos_x = 0; this->pos_y = 0; this->angle = 0; //init member
	this->name = name; this->color = RGB_BLACK; //itit color is black
	this->pen_thickness = 0; this->brush_color = RGB_BLACK; // init color is black
}

Shape::Shape(int px, int py, int angle, int pen_thickness, COLORREF color, COLORREF brush_color, string name)
{
	set_pos_x(px); set_pos_y(py); set_angle(angle); //settting
	set_name(name); set_color(color); //settting
	set_pen_thickness(pen_thickness); set_brush_color(brush_color); //settting
}

Shape::~Shape()
{
	cout << "destory shape : " << this->name << endl; 
}

void Shape::draw(ConsolePixelFrame cp_frame)
{
//	cout << "draw fucntion" << this->name << endl;
}

void Shape::draw()
{
	//cout << "draw function" << this->name << endl; //no use
}



void Shape::fprint(ostream& fout)
{
	fout << this->name << ": pos(" << setw(10) << this->get_pos_x() << ", " << 
		setw(10) << this->get_pos_y() << "), ";
	fout << "angle (" << setw(7) << this->angle << "), ";
	fout << "color (" << setw(8) << showbase << hex << uppercase << this->color << "), ";
	fout << "pen thickness (" << setw(3) << this->get_pen_thickness() << "), ";
	fout << "brush color (" << setw(8) << showbase << hex << uppercase << this->get_brush_color() << ") " << endl;
}

Shape& Shape:: operator = (const Shape& right)
{
	this->pos_x = right.pos_x; //assign x position
	this->pos_y = right.pos_y; //assign y positio
	this->angle = right.angle; //assign angle
	this->name = right.name; // assign name
	this->color = right.color; //assign color
	return *this;
}