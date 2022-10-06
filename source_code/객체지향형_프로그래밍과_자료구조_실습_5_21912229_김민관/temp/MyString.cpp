#include "MyString.h"

string gensRandString(int minLen, int MaxLen)
{
	string temp; //temp
	char charArray[2] = {}; //temp character array
	int length;
	length = rand() % 4 + 4; // 4 ~ 7 
	for (int i = 0; i < length; i++)
	{
		if (i == 0)
			charArray[0] = rand() % 26 + 'A';
		else
			charArray[0] = rand() % 26 + 'a';
		charArray[1] = '\0';
		temp.append(charArray); //append char array to string
	}
	return temp; 
}
