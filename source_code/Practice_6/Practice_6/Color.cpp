#include "Color.h"

ostream& printRGB(ostream& ostr, const COLORREF	color)
{
	ostr << "color (" << setw(6) << dec << color << endl;
	return ostr;
}