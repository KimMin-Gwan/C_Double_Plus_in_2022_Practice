#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <iomanip>
#include "Date.h"
using namespace std;
#define MAX_NAME_LEN 15
#define MIN_NAME_LEN 5

class Person
{
	friend ostream& operator << (ostream& fout, const Person& ps);
public:
	Person() { birthDate = Date(1, 1, 1); name = ""; } //constructer
	Person(string nm, Date bd) { birthDate = bd; name = nm; } //construct with name nad birthday
	//------------------accessor and mutator--------------------------------------------
	void setName(string n) { name = n; }  //setting name
	void setBirthDate(Date bd) { birthDate = bd; } //setting Birthday
	string getName() const { return name; } // return name
	Date getBirthDate() const { return birthDate; } //return Birthday
protected:
	Date birthDate;
	string name;
};
#endif