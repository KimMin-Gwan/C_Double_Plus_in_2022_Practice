#include "Star.h"

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

Star::Star()
	:Shape("Star"), radius(0), num_vertices(0)
{
	cout << "A default star constructed " << endl;
}

Star::Star(string name)
	:Shape(name), radius(0), num_vertices(0)
{
	cout << "A default star constructed name : " << this->name << endl;
}

Star::Star(int px, int py, int radius, int num_vertices, double ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, pen_thick, ln_clr, br_clr, name), radius(radius), num_vertices(num_vertices)
{
	cout << "A custom star constructed name : " << this->name << endl;
}

Star::~Star()
{
	cout << "destroy Star : " << this->name << endl;
}

void Star::draw(ConsolePixelFrame cp_frame)
{
	POINT* points = (POINT*)malloc(5.0 * sizeof(POINT));
	int fr_px = cp_frame.get_cpfr_px() + this->get_pos_x();
	int fr_py = cp_frame.get_cpfr_py() + this->get_pos_y();
	int x, y;
	double delta_angle = 2.0 * PI / 5.0; 
	double rad_angle = PI / 2.0; // angle in radian
	for (int i = 0; i < 5.0; i++, rad_angle += delta_angle)
	{
		x = fr_px + radius * cos(rad_angle);
		y = fr_py - radius * sin(rad_angle);
		points[i].x = x; points[i].y = y;
	}
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, brush_color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	MoveToEx(hdc, points[0].x, points[0].y, NULL);
	LineTo(hdc, points[2].x, points[2].y);
	LineTo(hdc, points[4].x, points[4].y);
	LineTo(hdc, points[1].x, points[1].y);
	LineTo(hdc, points[3].x, points[3].y);
	LineTo(hdc, points[0].x, points[0].y);
	SelectObject(hdc, old_pen);
	DeleteObject(new_pen);
	SelectObject(hdc, old_brush);
	DeleteObject(new_brush);
}

void Star:: draw()
{
	cout << "draw() of Star";
	fprint(cout);
}

void Star::fprint(ostream& fout)
{
	Shape::fprint(fout); //befor print, shape information print 
	fout << ", radius (" << radius << ")";
	fout << "), num vertices (" << num_vertices << ")";
	fout << endl;
}

Star& Star::operator=(Star& pg)
{
	Shape::operator=(pg); //assign shape first
	this->radius = pg.radius; //assign radius
	this->num_vertices = pg.radius; //assign num_vertices
	return *this;
}
