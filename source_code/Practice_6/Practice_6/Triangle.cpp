#include "Triangle.h"

/*
ostream& operator << (ostream& fout, Star& shape)
{
	fout << shape.get_name() << ": pos(" << shape.get_pos_x() << ", " << shape.get_pos_y();
	fout << "), line_color(" << shape.get_color();
	fout << "), brush_color(" << shape.get_brush_color();
	fout << "), pen_thickness(" << shape.get_pen_thickness();
	fout << ", radius(" << shape.getRadius() << ")";
	fout << ". radius(" << shape.getNumPoly() << ")";
	fout << endl;
	return fout;
}
*/

Triangle::Triangle()
	:Shape("Triangle"), base(0), tri_height(0)
{
	cout << "A default Triangle constructed " << endl;
}

Triangle::Triangle(string name)
	:Shape(name), base(0), tri_height(0)
{
	cout << "A default Triangle constructed name : " << this->name << endl;
}

Triangle::Triangle(int px, int py, int base, int height, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, pen_thick, ln_clr, br_clr, name), base(base), tri_height(height)
{
	cout << "A custom Triangle constructed name : " << this->name << endl;
}

Triangle::~Triangle()
{
	cout << "destroy Triangle : " << this->name << endl;
}

void Triangle::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int fr_px, fr_py;
	fr_px = cp_frame.get_cpfr_px() + get_pos_x();
	fr_py = cp_frame.get_cpfr_py() + get_pos_y();
	POINT p[3];
	p[0].x = fr_px - base / 2; p[0].y = fr_py + tri_height * 1.0 / 2.0;
	p[1].x = fr_px + base / 2; p[1].y = fr_py + tri_height * 1.0 / 2.0;
	p[2].x = fr_px; p[2].y = fr_py - tri_height * 1.0 / 2.0;
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	Polygon(hdc, p, 3);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Triangle:: draw()
{
	cout << "draw() of Triangle"; //console output
	fprint(cout);
}

void Triangle::fprint(ostream& fout)
{
	Shape::fprint(fout); //befor print, shape information print 
	fout << ", base (" << base << ")";
	fout << "), triangle height (" << tri_height << ")";
	fout << endl;
}

Triangle& Triangle::operator=(const Triangle& tri)
{
	Shape::operator=(tri); //assign shape first
	this->base= tri.base; //assign base 
	this->tri_height= tri.tri_height; //assign tri_height
	return *this;
}
