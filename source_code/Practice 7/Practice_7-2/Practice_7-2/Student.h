#ifndef STUDENT_H
#define STUDENT_H
#include <iomanip>
#include "Person.h"
class Student : public Person
{
	friend ostream& operator<< (ostream&, Student&);
public:
	Student(); // default constructor
	Student(int st_id, string name, int regID, string country, double gpa); //constructor
	void getKey(string keyName, void* pKey); //sorting, searching key
	bool operator<(const Student& other) const { return (st_id < other.st_id); }
	bool operator<=(const Student& other) const { return (st_id <= other.st_id); }
	bool operator>(const Student& other) const { return (st_id > other.st_id); }
	bool operator>=(const Student& other) const { return (st_id >= other.st_id); }
	bool operator==(const Student& other) const { return (st_id == other.st_id); }
private:
	int st_id;
	double gpa;
};
#endif