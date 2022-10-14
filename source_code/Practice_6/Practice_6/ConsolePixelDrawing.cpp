#include "ConsolePixelDrawing.h"

ConsolePixelFrame::ConsolePixelFrame(int px, int py)
{
	console = GetConsoleWindow();
	console_DC = GetDC(console);
	pShapes = new Shape * [MAX_NUM_SHAPES]; //allocate memory by maximun size
	num_shapes = 0;
	capacity = MAX_NUM_SHAPES; //capacity is 100
	cpfr_px = px; // set coordinate
	cpfr_py = py;
}
ConsolePixelFrame::~ConsolePixelFrame()
{
	//delete[] shapes;
	//ReleaseDC(console, console_DC);
}

void ConsolePixelFrame::addShape(Shape* new_shape)
{
	if (num_shapes >= capacity) //if capacity is insufficient
	{
		cout << "ConsolePixelFrame::addShape ==> Expanding capacity to "
			<< capacity * 2 << "shapes " << endl;
		Shape** old_shapes = pShapes; //get the allocate memory
		pShapes = new Shape * [capacity * 2]; //get double sized allocate memory
		if (pShapes == NULL) //if you are in memory exhaustion 
		{
			cout << "Error in expanding dynamic array for shapes capacity "
				<< capacity * 2 << "shapes " << endl;
			exit; //exit this program
		}
		for (int i = 0; i < num_shapes; i++) 
		{
			pShapes[i] = old_shapes[i]; //copy them
		}
		capacity = capacity * 2; 
		delete[] old_shapes;
	}
	//or
	pShapes[num_shapes] = new_shape; //new shape saved as reference
	num_shapes++;// prepare next shape
}

void ConsolePixelFrame::drawShapes()
{
	cout << "Drawing " << num_shapes << " shapes :" << endl;
	if (num_shapes > 0)
	{
		for (int i = 0; i < num_shapes; i++) //for each shapes
			pShapes[i]->draw(*this); //using pointer, the draw function execution
	}
}

bool ConsolePixelFrame::isValidIndex(int index)
{
	if ((index < 0) || (index >= num_shapes))
	{
		cout << "Error in ConsolePixelFrame::isValidIndex : current number of shapes ("
			<< num_shapes << "), index : " << index << ") !!" << endl;
		return false;
	}
	else
		return true;
}
