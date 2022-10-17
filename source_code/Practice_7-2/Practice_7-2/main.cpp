#include <iostream>
#include <conio.h> # for _getch()
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "T_Array.h"
#include "Student.h"
using namespace std;
#define NUM_STUDENTS 10
int main()
{
	Student students[NUM_STUDENTS] =
	{
	Student(5555, "Kim", 10205, "Korea", 3.57),
	Student(1234, "Lee", 11213, "Korea", 4.37),
	Student(4444, "Park", 12227, "Korea", 3.72),
	Student(2222, "Hao", 10121, "China", 2.35),
	Student(3333, "James", 11219, "USA", 3.89),
	Student(6666, "Thomas", 12320, "UK", 4.42),
	Student(7777, "Leon", 10722, "France", 4.12),
	Student(9999, "Carlo", 11519, "Italy", 4.35),
	Student(1000, "Tanaka", 13920, "Japan", 3.21),
	Student(8888, "Wang", 10622, "China", 3.45),
	};
	Student* pSt;
	T_Array<Student*, int> stArray_keySTID(NUM_STUDENTS, "T_Array<Student, keyST_ID>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keySTID.insert(i, &students[i]);
	}
	cout << "T_Array<Student*_keyID> at initialization :" << endl;
	stArray_keySTID.print(1);
	stArray_keySTID.selection_sort(string("ST_ID"), INCREASING);
	cout << "\nT_Array<Student*, keyID> after selection sorting (increasing order) by ST_ID : " << endl;
	stArray_keySTID.print(1);
	T_Array<Student*, string> stArray_keyName(NUM_STUDENTS, "T_Array<Student, keyName>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyName.insert(i, &students[i]);
	}
	stArray_keyName.selection_sort(string("NAME"), INCREASING);
	cout << "T_Array<Student*_keyName> after selection_sorting (increasing order) by Name : " << endl;
	stArray_keyName.print(1);
	T_Array<Student*, double> stArray_keyGPA(NUM_STUDENTS, "T_Array<Student, keyGPA>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyGPA.insert(i, &students[i]);
	}
	stArray_keyGPA.selection_sort(string("GPA"), DECREASING);
	cout << "T_Array<Student*_keyGPA> after selection_sorting (decreasing order) by GPA : " << endl;
	stArray_keyGPA.print(1);
	T_Array<Student*, int> stArray_keyRegID(NUM_STUDENTS, "T_Array<Student, keyRegID>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyRegID.insert(i, &students[i]);
	}
	stArray_keyRegID.merge_sort(string("REGID"), INCREASING);
	cout << "\nT_Array<Student*_keyRegID> after merge sorting (increasing order) by regID : " << endl;
	stArray_keyRegID.print(1);
	T_Array<Student*, string> stArray_keyNation(NUM_STUDENTS, "T_Array<Student, keyNation>");
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		stArray_keyNation.insert(i, &students[i]);
	}
	stArray_keyNation.merge_sort(string("NATION"), INCREASING);
	cout << "\nT_Array<Student*_keyNation> after merge sorting (increasing order) by nation : " << endl;
	stArray_keyNation.print(1);
	return 0;
}