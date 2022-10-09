#include <iostream>
#include <string>
#include <fstream>
#include "ConsolePixelDrawing.h"
#include "Shape.h"
#include "Triangle.h"
#include "Circle.h"
#include "Rectang.h"
#include "Polygon.h"
#include "Star.h"
#include "AngleArc.h"
#include "Cylinder.h"
using namespace std;

int main()
{
Circle cir(100, 200, 80, 0, RGB_BLACK, RGB_RED, 3, "Circle");
Triangle tri(300, 200, 150, 130, 0, RGB_BLACK, RGB_YELLOW, 3, "Triangle");
Rectang rec(500, 200, 150, 150, 0, RGB_BLACK, RGB_BLUE, 4, "Rectangle");
PolyGon poly_5(700, 200, 80, 5, 0, RGB_BLACK, RGB_GREEN, 4, "Polygon_5");
PolyGon poly_7(100, 400, 80, 7, 0, RGB_BLACK, RGB_MAGENTA, 4, "Polygon_7");
Star star_5(300, 400, 80, 5, 0, RGB_BLACK, RGB_BLACK, 4, "Star_5");
AngledArc angle_arc(500, 400, 80, 0, 45, 270, RGB_RED, RGB_BLUE, 4, "Angle_Arc");
Cylinder cyl(700, 400, 80, 0, 100, RGB_BLUE, RGB_WHITE, 4, "Cylinder");
ConsolePixelFrame frame(50, 50); // fr_x, fr_y
frame.addShape(&cir);
frame.addShape(&tri);
frame.addShape(&rec);
frame.addShape(&poly_5);
frame.addShape(&poly_7);
frame.addShape(&star_5);
frame.addShape(&angle_arc);
frame.addShape(&cyl);
frame.drawShapes();
printf("hit any key to continue ....");
_getch();
return 0;
} // end of main()