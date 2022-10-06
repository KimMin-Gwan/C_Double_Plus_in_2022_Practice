#ifndef STUDENT_ARRAY_H
#define STUDENT_ARRAY_H
#include <iostream>
#include "Student.h"

using namespace std;

class StudentArray
{
	friend ostream& operator << (ostream& fout, const StudentArray& sa);
public:
	StudentArray(int size); // constructor
	StudentArray(const StudentArray& obj);// copy constructor
	~StudentArray(); //destructor
	int size() const { return num_students; } //return numstudent
	Student& operator [](int index) const; // make array
	//---------sorting operation----------------------------------
	void sortByBirthDate();
	void sortByName();
	void sortByST_ID();
	void sortByGPA();
private:
	Student* pStudents;
	int num_students; //size of the students
	bool isValidIndex(int index)const; //check the valid index
};

#endif
