#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;
class Person
{
	friend ostream& operator<< (ostream& fout, const Person& p);
public:
	//only_in_lined_fucntions-----------------------------------------
	Person() { name = "nobody"; } //constructor
	Person(string n) { name = n; } //constructor
	//mutator-------------------------
	void set_name(string n) { name = n; }
	void set_nation(string country) { nation = country; }
	void set_regID(int rgID) { regID = rgID; } 
	//accesser------------------------
	const string get_name() const { return name; } //name
	const string get_nation() const { return nation; } //nation
	const int get_regID() const { return regID; } //register ID
protected:
	string name;
	int regID;
	string nation;
};
#endif