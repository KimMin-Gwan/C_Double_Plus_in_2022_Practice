#include "Cylinder.h"



ostream& operator << (ostream& fout, Cylinder& shape)
{
	fout << shape.get_name() << ": pos(" << shape.get_pos_x() << ", " << shape.get_pos_y();
	fout << "), line_color(" << shape.get_color();
	fout << "), brush_color(" << shape.get_brush_color();
	fout << "), pen_thickness(" << shape.get_pen_thickness();
	fout << ", radius(" << shape.getRadius() << ")";
	fout << ". height(" << shape.getHeight() << ")";
	fout << endl;
	return fout;
}


Cylinder::Cylinder()
	:Shape("Cylinder"), radius(0), height(0)
{
	cout << "A default Cylinder constructed " << endl;
}

Cylinder::Cylinder(string name)
	:Shape(name), radius(0), height(0)
{
	cout << "A default Cylinder constructed name : " << this->name << endl;
}

Cylinder::Cylinder(int px, int py, int radius, int ang, int height, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, pen_thick, ln_clr, br_clr, name), radius(radius), height(height)
{
	cout << "A custom Cylinder constructed name : " << this->name << endl;
}

Cylinder::~Cylinder()
{
	cout << "destroy Cylinder : " << this->name << endl;
}

void Cylinder::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	int cx = cp_frame.get_cpfr_px() + get_pos_x();
	int cy = cp_frame.get_cpfr_py() + get_pos_y();
	MoveToEx(hdc, cx - radius, cy - height / 2, (LPPOINT)NULL);
	LineTo(hdc, cx - radius, cy + height / 2);
	MoveToEx(hdc, cx + radius, cy - height / 2, (LPPOINT)NULL);
	LineTo(hdc, cx + radius, cy + height / 2);
	Ellipse(hdc, cx - radius, cy - height / 2 - 20, cx + radius, cy - height / 2 + 20);
	MoveToEx(hdc, cx - radius, cy + height / 2, (LPPOINT)NULL);
	ArcTo(hdc, cx - radius, cy + height / 2 - 20, cx + radius, cy + height / 2 + 20, cx - radius, cy + height / 2,
		cx + radius, cy + height / 2);
	SelectObject(hdc, old_pen); DeleteObject(new_pen);
	SelectObject(hdc, old_brush); DeleteObject(new_brush);
}

void Cylinder:: draw()
{
	cout << "draw() of Cylinder"; //console output
	fprint(cout);
}

void Cylinder::fprint(ostream& fout)
{
	Shape::fprint(fout); //befor print, shape information print 
	fout << ", radius(" << radius<< ")";
	fout << "), height(" << height<< ")";
	fout << endl;
}

Cylinder& Cylinder::operator=(const Cylinder& cir)
{
	Shape::operator=(cir); //assign shape first
	this->radius= cir.radius; //assign radius
	this->height= cir.height; //assign height 
	return *this;
}


