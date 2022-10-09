#include "Rectang.h"

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

Rectang::Rectang()
	:Shape("Rectangle"), width(0), length(0)
{
	cout << "A default Rectangle constructed " << endl;
}

Rectang::Rectang(string name)
	:Shape(name), width(0), length(0)
{
	cout << "A default Rectangle constructed name : " << this->name << endl;
}

Rectang::Rectang(int px, int py, int width, int length, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, pen_thick, ln_clr, br_clr, name), width(width), length(length)
{
	cout << "A custom Rectangle constructed name : " << this->name << endl;
}

Rectang::~Rectang()
{
	cout << "destroy Rectangle : " << this->name << endl;
}

void Rectang::draw(ConsolePixelFrame cp_frame)
{
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	int fr_px, fr_py;
	fr_px = cp_frame.get_cpfr_px() + get_pos_x();
	fr_py = cp_frame.get_cpfr_py() + get_pos_y();
	POINT p[4];
	p[0].x = fr_px - width / 2; p[0].y = fr_py - length / 2;
	p[1].x = fr_px + width / 2; p[1].y = fr_py - length / 2.0;
	p[2].x = fr_px + width / 2; p[2].y = fr_py + length / 2.0;
	p[3].x = fr_px - width / 2; p[3].y = fr_py + length / 2.0;
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(cp_frame.getConsole_DC(), new_brush);
	Polygon(hdc, p, 4);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Rectang:: draw()
{
	cout << "draw() of Rectang"; //console output
	fprint(cout);
}

void Rectang::fprint(ostream& fout)
{
	Shape::fprint(fout); //befor print, shape information print 
	fout << ", width (" << width << ")";
	fout << "), length (" << length<< ")";
	fout << endl;
}

Rectang& Rectang::operator=(Rectang& rec)
{
	Shape::operator=(rec); //assign shape first
	this->width= rec.width; //assign width 
	this->length= rec.length; //assign length 
	return *this;
}
