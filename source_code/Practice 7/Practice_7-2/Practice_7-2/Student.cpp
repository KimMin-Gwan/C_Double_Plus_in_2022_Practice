#include "Student.h"

ostream& operator<< (ostream& ostr, Student& student)
{
	//print like
	// Student [ st_id:  5555, name: Kim    , gpa: 3.57 , regID:  10205, nation: Korea ]
	ostr.setf(ios::left);
	ostr.setf(ios::fixed);
	ostr.precision(2);
	ostr << "Student [ st_id: " << setw(6) << student.st_id << ", name: ";
	ostr.setf(ios::left);
	ostr << setw(6) << student.name << ", gpa: " << setw(4) << student.gpa << " , regID: ";
	ostr.setf(ios::right);
	ostr << setw(6) << student.regID << ", nation: ";
	ostr.setf(ios::left);
	ostr << setw(6) << student.nation << "]";
	return ostr;
}

Student::Student()
{
	this->st_id = 0; //init
	this->gpa = 0; //init 
	this->name = "anaymous"; //anaymous
	this->regID = 0; //0 regID
	this->nation = "none"; //none
}

Student::Student(int st_id, string name, int regID, string country, double gpa)
{
	this->st_id = st_id; //set st_id
	this->name = name;  //set name
	this->regID = regID; //set regID
	this->nation = country; //set nation
	this->gpa = gpa; //set gpa
}

void Student::getKey(string keyName, void* pKey)
{
	if (keyName == "ST_ID")
		*(int*)pKey = this->st_id; //return st_id
	else if (keyName == "NAME")
		*(string*)pKey = this->name; //return name
	else if (keyName == "GPA")
		*(double*)pKey = this->gpa; //return gpa
	else if (keyName == "REGID")
		*(int*)pKey = this->regID; //return regID
	else if (keyName == "NATION")
		*(string*)pKey = this->nation; //return nation
	else
		pKey = NULL; //return nothing
}