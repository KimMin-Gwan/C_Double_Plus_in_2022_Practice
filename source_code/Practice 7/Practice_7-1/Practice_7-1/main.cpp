/**
*���ϸ� : "Practice_7-1"
*���α׷��� ���� �� �⺻ ���: 
*      -�� ���α׷��� vector ���̺귯���� ����Ͽ� Student Ŭ���� ��ü����
*		�����ϰ�, �����Ͽ� Console�� ����ϴ� ���α׷��̴�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 10�� 17��)
*���� Update : Version 1.0, 2022�� 10�� 17��(��ΰ�)
*============================================================================
* 
*/
#include <iostream>
#include <conio.h> # for _getch()
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "Student.h"
#include "VectorHandler.h"
using namespace std;
#define NUM_STUDENTS 10
#define NUM_DATES 10
void main()
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
	vector<Student> v_students(students, students + NUM_DATES);
	cout << "Initial v_students :" << endl;
	printVector(v_students);
	sort(v_students.begin(), v_students.end());
	cout << "\nstudents after sorting by st_id :" << endl;
	printVector(v_students);
}