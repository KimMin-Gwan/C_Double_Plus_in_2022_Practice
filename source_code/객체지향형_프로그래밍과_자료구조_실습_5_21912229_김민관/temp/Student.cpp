#include "Student.h"

string genRandName(); //random name
Date genRandDate(); //random Date
string genRandDeptName(); //random DeptName
double genRandGPA(); //random GPA
 
ostream& operator << (ostream& fout, const Student& student)
{
	fout << " Student[ " << "st_id : " << setw(6) << student.getST_id() <<
		", name : " << setw(8) << student.getName() <<
		", Dept : " << setw(6) << student.getDept_name() <<
		", birth date : " << setw(10) << student.getBirthDate();
	//cout << student.getName() << endl;
	fout.setf(ios::showpoint);
	fout.setf(ios::fixed);
	fout << ", GPA : " << setw(6) << student.getGPA() << endl;
	fout.unsetf(ios::adjustfield);
	return fout;
}
Student::Student()
{
	this->st_id = 0;
	this->dept_name = "Undesignated";
	this->gpa = 0;
}
Student::Student(int st_id)
{
	setST_id(st_id);
	this->dept_name = "Undesignated";
	this->gpa = 0;
}
Student::Student(int st_id, string dept_name, double gpa, Date dob, string n)
{
	setST_id(st_id);
	setDept_name(dept_name);
	setGPA(gpa);
	setBirthDate(dob);
	setName(n);
}
const Student& Student::operator = (const Student& right)
{
	this->st_id = right.st_id; //assign year
	this->dept_name = right.dept_name; //assign month
	this->gpa = right.gpa; //assign day
	this->name = right.name; //assign name
	this->birthDate = right.birthDate; //assign birthDate
	return *this;
}
bool Student::operator > (const Student& right)
{
	if (this->getGPA() > right.getGPA())
		return true;
	else
		return false;
}
bool Student::operator == (const Student& right)
{
	int flag = 0; //if Date's each elements is same, flag will added
	this->st_id == right.st_id ? flag++ : flag = 0; 
	this->gpa == right.gpa ? flag++ : flag = 0;
	this->dept_name == right.dept_name ? flag++ : flag = 0;
	if (flag == 3) //if 3 all index are saem, flag will 3
		return true;
	else
		return false;
}
//out of class function--------------------------------------------------------
Student genRandStudent(int id)
{
	Student rStudents(id);
	rStudents.setBirthDate(genRandDate()); //generate date
	rStudents.setDept_name(genRandDeptName()); //generate DeptName
	rStudents.setGPA(genRandGPA()); //generate GPA
	rStudents.setName(genRandName()); //generate name
	cout << rStudents.getName() << endl;
	//cout << rStudents << endl;

	return rStudents;
}
void genST_ids(int num_students, int* st_ids)
{
	int temp_id = 0;
	int* flag = NULL;
	flag = new int[ID_SIZE]; //flag allocate
	for (int i = 0; i < num_students; i++)
	{
		temp_id = (((unsigned int)rand() << 15) | rand()) % ID_SIZE; 
		if (flag[temp_id] == 1)
			i--; //same index, i decrease
		else
		{
			flag[temp_id]++; //flag up
			st_ids[i] = temp_id + ID_OFFSET; 
		}
	}
}
string genRandName()
{
	string temp = gensRandString(MIN_NAME_LEN, MAX_NAME_LEN); 
	return temp;
}
string genRandDeptName()
{
	string temp; //temp
	char charArray[2] = {}; //temp character array
	int length;
	length = rand() % 2 + 3; // 3 ~ 4
	for (int i = 0; i < length; i++)
	{
		charArray[0] = rand() % 26 + 'A'; //A ~ Z
		charArray[1] = '\0'; //NULL
		temp.append(charArray); //append char array to string
	}
	return temp; 
}
double genRandGPA()
{
	double temp; //temp 
	temp = rand() % 10000; //0 ~ 9999
	temp /= 100; //0.00 ~ 99.99
	return temp;
}
