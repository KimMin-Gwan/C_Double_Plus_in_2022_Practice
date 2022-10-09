#include "CIrcle.h"


ostream& operator << (ostream& fout, Circle& shape)
{
	fout << shape.get_name() << ": pos(" << shape.get_pos_x() << ", " << shape.get_pos_y();
	fout << "), line_color(" << shape.get_color();
	fout << "), brush_color(" << shape.get_brush_color();
	fout << "), pen_thickness(" << shape.get_pen_thickness();
	fout << ", radius(" << shape.getRadius() << ")";
	fout << endl;
	return fout;
}

Circle::Circle()
	:Shape("Circle"), radius(0)
{
	cout << "A default Circle constructed " << endl;
}

Circle::Circle(string name)
	:Shape(name), radius(0)
{
	cout << "A default Circle constructed name : " << this->name << endl;
}

Circle::Circle(int px, int py, int radius, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, pen_thick, ln_clr, br_clr, name), radius(radius)
{
	cout << "A custom Circle constructed name : " << this->name << endl;
}

Circle::~Circle()
{
	cout << "destroy Circle: " << this->name << endl;
}

void Circle::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int fr_px, fr_py;
	fr_px = cp_frame.get_cpfr_px() + get_pos_x();
	fr_py = cp_frame.get_cpfr_py() + get_pos_y();
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	Ellipse(hdc, fr_px - radius, fr_py - radius, fr_px + radius, fr_py + radius);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Circle:: draw()
{
	cout << "draw() of Circle";
	fprint(cout);
}

void Circle::fprint(ostream& fout)
{
	Shape::fprint(fout); //befor print, shape information print 
	fout << ", radius (" << radius << ")";
	fout << endl;
}

Circle& Circle::operator=(const Circle& cir)
{
	Shape::operator=(cir); //assign shape first
	this->radius = cir.radius; //assign radius
	return *this;
}
