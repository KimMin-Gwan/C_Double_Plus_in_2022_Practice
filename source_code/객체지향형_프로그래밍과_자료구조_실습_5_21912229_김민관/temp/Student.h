#ifndef STUDENT_H
#define STUDENT_H
#include <iostream>
#include <iomanip>
#include "Person.h"
#include "MyString.h"
#define ID_SIZE 40000
#define ID_OFFSET 10000
using namespace std;
class StudentArray;
class Student : public Person
{
	friend class StudentArray;
	friend ostream& operator << (ostream& fout, const Student& student);
public:
	Student(); // default constructor
	Student(int st_id); // constructor
	Student(int st_id, string dept_name, double gpa, Date dob, string n); //constructor
	//----------------inline accessor and mutator ---------------------------
	int getST_id() const { return st_id; } //return st_id
	string getDept_name() const { return dept_name; }//return dept_name
	double getGPA() const { return gpa; } //return gpa
	Date getBirthDate() const { return birthDate; } //return birthDate
	void setST_id(int id) { st_id = id; } //set id
	void setDept_name(string dp_n) { dept_name = dp_n; } //set name
	void setGPA(double g) { gpa = g; } //set gpa
	//-----------------operator overloading-----------------------------------
	const Student& operator = (const Student& right); //asign operation
	bool operator > (const Student& right);  //compare operation
	bool operator == (const Student& right); //equal opeartion
private:
	int st_id;
	string dept_name; 
	double gpa;
};
Student genRandStudent(int id); //genarate random student data
void genST_ids(int num_students, int* st_ids);  //get random id
#endif