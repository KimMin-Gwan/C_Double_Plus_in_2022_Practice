#ifndef COLOR_H
#define COLOR_H
#include <iostream>
#include <string>
#include <iomanip>
#include <Windows.h>
using namespace std;
// COLORREF is defined in <Windows.h>
// The COLORREF value is used to specify an RGB color,
// in hexadecimal form of 0x00bbggrr
const COLORREF RGB_RED = 0x000000FF;
const COLORREF RGB_GREEN = 0x0000FF00;
const COLORREF RGB_BLUE = 0x00FF0000;
const COLORREF RGB_BLACK = 0x00000000;
const COLORREF RGB_ORANGE = 0x0000A5FF;
const COLORREF RGB_YELLOW = 0x0000FFFF;
const COLORREF RGB_MAGENTA = 0x00FF00FF;
const COLORREF RGB_WHITE = 0x00FFFFFF;
ostream& fprintRGB(ostream& ostr, const COLORREF color);
// RGB color code chart: https://www.rapidtables.com/web/color/RGB_Color.html
/* Note: RGB(red, green, blue) macro also provides COLORREF data
 . RGB(FF, 00, 00) => 0x000000FF (RGB_RED)
 . RGB(00, FF, 00) => 0x0000FF00 (RGB_GREEN)
 . RGB(00, 00, FF) => 0x00FF0000 (RGB_BLUE)
*/
#endif