#include "Person.h"
void Person::setRandPersonAttributes()
{
	char str[MAX_NAME_LEN + 1];
	int name_len, i = 0;
	birthDate.setRandDateAttributes();
	name_len = rand() % (MAX_NAME_LEN - MIN_NAME_LEN) + MIN_NAME_LEN;
	str[0] = rand() % 26 + 'A'; //first word must be upper
	for (i = 1; i < name_len; i++) //except first word, lower word name
		str[i] = rand() % 26 + 'a';
	str[i] = '\0'; //null word
	name = string(str);
}


void Person::fprintPerson(ostream& fout)
{
	fout << " Person [name: ";
	fout.setf(ios::left);
	fout << setw(20) << name;
	fout << ", birth date: ";
	fout.unsetf(ios::left);
	birthDate.fprintDate(fout);
	fout << "]";
}