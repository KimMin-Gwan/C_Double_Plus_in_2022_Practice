#include "Person.h"
ostream& operator << (ostream& fout, const Person& ps)
{
	fout << "Name : " << setw(8) << ps.getName();
	fout << ", BirthDate : " << ps.getBirthDate();
	return fout;
}
