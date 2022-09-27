#ifndef MTRX_ARRAY_H
#define MTRX_ARRAY_H
#include <iostream>
#include "Mtrx.h"
using namespace std;
class Mtrx;
class MtrxArray
{
public:
	MtrxArray(int arraySize); // constructor
	~MtrxArray(); // destructor
	Mtrx& operator[](int);
	int getSize();
private:
	Mtrx* pMtrx;
	int mtrxArraySize;
	bool isValidIndex(int index);
};
#endif
