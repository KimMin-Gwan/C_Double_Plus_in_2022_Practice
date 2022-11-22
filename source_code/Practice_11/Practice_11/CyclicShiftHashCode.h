#ifndef CYCLIC_SHIFT_HASH_CODE_H
#define CYCLIC_SHIFT_HASH_CODE_H 
#include <iostream>
#include <string>

using namespace std;
#define BIT_SHIFTS 5
#define BITS_INT 32

class CyclicShiftHashCode
{
public:
	int operator() (const string key)
	{
		int len = key.length();
		unsigned int h = 0;
		for (int i = 0; i < len; i++)
		{
			h = (h << BIT_SHIFTS) | (h >> (BITS_INT - BIT_SHIFTS));
			h += (unsigned int)key.at(i);
		}
		return h;
	}
};

#endif