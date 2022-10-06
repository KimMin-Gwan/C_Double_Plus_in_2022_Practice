#include "StudentArray.h"

ostream& operator << (ostream& fout, const StudentArray& sa)
{
	fout << "StudentArray (size ; " << sa.size() << ")" << endl;
	for (int i = 0; i < sa.size(); i++)
		fout << sa.pStudents[i];
	return fout;
}

StudentArray::StudentArray(int size)
{
	this->num_students = size;
	pStudents = new Student[size];
}
StudentArray::StudentArray(const StudentArray& obj)
{
	this->num_students = obj.num_students;
	this->pStudents = new Student[this->num_students];
	for (int i = 0; i < this->size(); i++)
	{
		this->pStudents[i] = obj.pStudents[i];
	}
}

StudentArray::~StudentArray()
{
	cout << "StudentArray :: destructor" << endl;
	if (pStudents != NULL) //free allocated memory
		delete[] pStudents;
}

Student& StudentArray::operator [](int index) const
{
	if (isValidIndex(index))
		return pStudents[index];
	else
	{
		cout << "System Error : No more memory" << endl;
		exit(0);
	}
}

//sorting-----------------------------------
void StudentArray::sortByBirthDate()
{
	Student minStd; 
	int indexMin;

	for (int i = 0; i < this->size() - 1; i++)
	{
		indexMin = i;
		minStd = this->pStudents[i];
		for (int j = i + 1; j < this->size(); j++) //search
		{
			if (minStd.getBirthDate() > this->pStudents[j].getBirthDate()) //if found smaller elements
			{
				indexMin = j; //change temp index
				minStd = this->pStudents[j];
			}
		}
		if (indexMin != i)
		{
			this->pStudents[indexMin] = this->pStudents[i]; //sorting
			this->pStudents[i] = minStd;
		}
	}
}
void StudentArray::sortByName() 
{
	Student minStd; 
	int indexMin;

	for (int i = 0; i < this->size() - 1; i++)
	{
		indexMin = i;
		minStd = this->pStudents[i];
		for (int j = i + 1; j < this->size(); j++) //search
		{
			if (minStd.getName() > this->pStudents[j].getName()) //if found smaller elements
			{
				indexMin = j; //change temp index
				minStd = this->pStudents[j];
			}
		}
		if (indexMin != i)
		{
			this->pStudents[indexMin] = this->pStudents[i]; //sorting
			this->pStudents[i] = minStd;
		}
	}
}
void StudentArray::sortByST_ID() 
{
	Student minStd; 
	int indexMin;

	for (int i = 0; i < this->size() - 1; i++)
	{
		indexMin = i;
		minStd = this->pStudents[i];
		for (int j = i + 1; j < this->size(); j++) //search
		{
			if (minStd.getST_id() > this->pStudents[j].getST_id()) //if found smaller elements
			{
				indexMin = j; //change temp index
				minStd = this->pStudents[j];
			}
		}
		if (indexMin != i)
		{
			this->pStudents[indexMin] = this->pStudents[i]; //sorting
			this->pStudents[i] = minStd;
		}
	}
}
void StudentArray::sortByGPA() 
{
	Student minStd; 
	int indexMin;

	for (int i = 0; i < this->size() - 1; i++)
	{
		indexMin = i;
		minStd = this->pStudents[i];
		for (int j = i + 1; j < this->size(); j++) //search
		{
			if (minStd.getGPA() > this->pStudents[j].getGPA()) //if found smaller elements
			{
				indexMin = j; //change temp index
				minStd = this->pStudents[j];
			}
		}
		if (indexMin != i)
		{
			this->pStudents[indexMin] = this->pStudents[i]; //sorting
			this->pStudents[i] = minStd;
		}
	}
}

//private
bool StudentArray::isValidIndex(int index) const
{
	if (index < 0 || index >= num_students)
		return false;
	else
		return true;
}
