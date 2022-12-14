#ifndef VECTOR_HANDLER_H
#define VECTOR_HANDLER_H
#include <vector>
#include <algorithm>

template<typename T>
void printVector(vector<T>& v)
{
	string typeName = typeid(T).name(); //name
	cout << "Vector size(" << v.size() << "), elements : \n"; 
	typename vector<T>::iterator p; //use p to roaming 
	for (p = v.begin(); p != v.end(); p++)
	{
		cout << *p << " ";
		if ((typeName == "class Date") || (typeName == "class Time"))
			continue;
		else
			cout << endl;
	}
	cout << endl;
};
#endif