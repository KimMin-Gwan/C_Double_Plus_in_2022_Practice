#include "MtrxArray.h"
#include "Mtrx.h"

MtrxArray::MtrxArray(int arraySize)
{
	mtrxArraySize = arraySize; //set matrix size
	pMtrx = new Mtrx[arraySize]; //get dynamic array
}

MtrxArray::~MtrxArray()
{
	cout << "MtrxArray :: destructor" << endl;
	if (pMtrx != NULL) //free allocated memory
	{
		delete[] pMtrx;
	}
}

void subError()
{
	cout << "Subscript out of range \n" << endl; //error messege on console
	exit(0);
}

bool MtrxArray::isValidIndex(int index)
{
	if (index < 0 || index >= mtrxArraySize) //check the marix made in collect size
		return false;
	else
		return true;
}

Mtrx& MtrxArray::operator [](int sub)
{
	if (isValidIndex(sub))
		return pMtrx[sub];
	else
		subError();
}