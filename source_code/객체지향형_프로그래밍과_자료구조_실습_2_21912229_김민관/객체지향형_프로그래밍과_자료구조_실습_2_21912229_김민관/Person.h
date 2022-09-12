#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include "Date.h"
using namespace std;
#define MAX_NAME_LEN 15
#define MIN_NAME_LEN 5
class Person
{
public:
	Person() : name(string("nobody")), birthDate(Date(1, 1, 1)) { } //initialize list 
	Person(string n, Date bd) : name(n), birthDate(bd) { } //intialize list
	void setName(string n) { name = n; }
	string getName() { return name; }
	void setBirthDate(Date bd) { birthDate = bd; }
	Date getBirthDate() { return birthDate; }
	void setRandPersonAttributes(); //set name, name length, birthday as random
	void fprintPerson(ostream& fout); //printing the attributes on txt
private:
	Date birthDate;
	string name;
};
#endif