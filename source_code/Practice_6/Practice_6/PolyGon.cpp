#include "PolyGon.h"

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

PolyGon::PolyGon()
	:Shape("PolyGon"), radius(0), num_poly(0)
{
	cout << "A default PolyGon constructed " << endl;
}

PolyGon::PolyGon(string name)
	:Shape(name), radius(0), num_poly(0)
{
	cout << "A default PolyGon constructed name : " << this->name << endl;
}

PolyGon::PolyGon(int px, int py, int radius, int num_poly, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, pen_thick, ln_clr, br_clr, name), radius(radius), num_poly(num_poly)
{
	cout << "A custom PolyGon constructed name : " << this->name << endl;
}

PolyGon::~PolyGon()
{
	cout << "destroy PolyGon: " << this->name << endl;
}

void PolyGon::draw(ConsolePixelFrame cp_frame)
{
	POINT* points = (POINT*)malloc(num_poly * sizeof(POINT));
	double rad_angle, delta_angle; // angle in radian
	int fr_px = cp_frame.get_cpfr_px() + get_pos_x();
	int fr_py = cp_frame.get_cpfr_py() + get_pos_y();
	int x, y;
	delta_angle = 2.0 * PI / num_poly;
	rad_angle = PI / 2.0;
	for (int i = 0; i < num_poly; i++, rad_angle += delta_angle)
	{
		x = fr_px + radius * cos(rad_angle);
		y = fr_py - radius * sin(rad_angle);
		points[i].x = x; points[i].y = y;
	}
	HDC hdc;
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(cp_frame.getConsole_DC(), new_brush);
	Polygon(hdc, points, num_poly);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void PolyGon:: draw()
{
	cout << "draw() of PolyGon"; //console output
	fprint(cout);
}

void PolyGon::fprint(ostream& fout)
{
	Shape::fprint(fout); //befor print, shape information print 
	fout << ", radius(" << radius<< ")";
	fout << "), num_poly(" << num_poly<< ")";
	fout << endl;
}

PolyGon& PolyGon::operator=(PolyGon& pg)
{
	Shape::operator=(pg); //assign shape first
	this->radius= pg.radius; //assign radius
	this->num_poly= pg.num_poly; //assign num_poly 
	return *this;
}
