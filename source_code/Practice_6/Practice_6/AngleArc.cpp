#include "AngleArc.h"


ostream& operator << (ostream& fout, AngledArc& shape)
{
	fout << shape.get_name() << ": pos(" << shape.get_pos_x() << ", " << shape.get_pos_y();
	fout << "), line_color(" << shape.get_color();
	fout << "), brush_color(" << shape.get_brush_color();
	fout << "), pen_thickness(" << shape.get_pen_thickness();
	fout << ", radius(" << shape.getRadius() << ")";
	fout << ", start_angle (" << shape.getStart_angle() << ")";
	fout << ", sweep_angle (" << shape.getSweep_angle() << ")";
	fout << endl;
	return fout;
}

AngledArc::AngledArc()
	:Shape("Angled Arc"), radius(0), start_angle(0), sweep_angle(0)
{
	cout << "A default Angled arc constructed " << endl;
}

AngledArc::AngledArc(string name)
	:Shape(name), radius(0), start_angle(0), sweep_angle(0)
{
	cout << "A default Angled arc constructed name : " << this->name << endl;
}

AngledArc::AngledArc(int px, int py, int radius, int ang, int start_ang, int sweep_ang, COLORREF ln_clr, COLORREF br_clr, int pen_thick, string name)
	:Shape(px, py, ang, pen_thick, ln_clr, br_clr, name), radius(radius), start_angle(start_ang), sweep_angle(sweep_ang)
{
	cout << "A custom Angled arc constructed name : " << this->name << endl;
}

AngledArc::~AngledArc()
{
	cout << "destroy Angled arc : " << this->name << endl;
}

void AngledArc::draw(ConsolePixelFrame cp_frame)
{
	HPEN new_pen, old_pen;
	HBRUSH new_brush, old_brush;
	HDC hdc;
	int start_px, start_py;
	double start_ang_rad;
	int fr_px = cp_frame.get_cpfr_px() + get_pos_x();
	int fr_py = cp_frame.get_cpfr_py() + get_pos_y();
	hdc = cp_frame.getConsole_DC();
	new_pen = CreatePen(PS_SOLID, pen_thickness, color);
	old_pen = (HPEN)SelectObject(hdc, new_pen);
	new_brush = CreateSolidBrush(brush_color);
	old_brush = (HBRUSH)SelectObject(hdc, new_brush);
	start_ang_rad = start_angle * 3.141592 / 180.0;
	start_px = fr_px + radius * cos(start_ang_rad);
	start_py = fr_py - radius * sin(start_ang_rad);
	MoveToEx(hdc, fr_px, fr_py, (LPPOINT)NULL);
	LineTo(hdc, start_px, start_py);
	AngleArc(hdc, fr_px, fr_py, radius, start_angle, sweep_angle);
	LineTo(hdc, fr_px, fr_py);
	SelectObject(hdc, old_pen); DeleteObject(new_pen);
	SelectObject(hdc, old_brush); DeleteObject(new_brush);
}

void AngledArc:: draw()
{
	cout << "draw() of Angle arc"; //console output
	fprint(cout);
}

void AngledArc::fprint(ostream& fout)
{
	Shape::fprint(fout); //befor print, shape information print 
	fout << ", radius(" << radius<< ")"; 
	fout << "), start_angle(" << start_angle<< ")";
	fout << "), sweep_angle(" << sweep_angle << ")";
	fout << endl;
} 

AngledArc& AngledArc::operator=(const AngledArc& cir)
{
	Shape::operator=(cir); //assign shape first
	this->radius= cir.radius; //assign radius
	this->start_angle= cir.start_angle; //assign start_angle 
	this->sweep_angle = cir.sweep_angle; // assign sweep_angle
	return *this; 
}
