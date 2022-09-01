/**
*파일명 : "프로그래밍_21912229_김민관_실습_1"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 난수를 생성하여 학생의 정보를 생성하고
*		생성된 학생들의 정보를 정렬하여 출력하거나, 검색하여 찾는 기능을
*		수행한다.
*프로그램 작성자 : 김민관(2022년 09월 01일)
*최종 Update : Version 1.0, 2022년 월 일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*============================================================================
*/

#include <iostream>
#include <iomanip>
#include <fstream>
#include "Student.h"
#include "BigRand.h"


using namespace std;
#define NUM_STUDENTS 5000
#define NUM_SEARCH 5
#define NUM_FIRST_LAST_BLOCK 100
void main()
{
	ofstream fout;
	int* student_ids;
	Student* students, * pSt;
	int student_search[NUM_SEARCH] = { 1, 123, 999, 2500, 4999 };

	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening output.txt" << endl;
		exit;
	}

	students = (Student*)calloc(NUM_STUDENTS, sizeof(Student));
	student_ids = genBigRandArray(NUM_STUDENTS, 0);
	initStudents(students, student_ids, NUM_STUDENTS);
	/*학생 생성 후 출력*/
	fout << endl << endl;
	fout << "Initialized array of students : " << endl;
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	/*ID기준 오름차순 정렬*/
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	sortStudentsByID(students, NUM_STUDENTS);
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	/*GPA기준 내림차순 정렬*/
	fout << endl << endl;
	fout << "Sorting array of students by (decreasing order of GPA, increasing order of ID) : " << endl;
	sortStudentsByGPA_ID(students, NUM_STUDENTS); // non-increasing order
	fprintBigArrayOfStudent_GPA_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	/*ID기준 오름차순 정렬*/
	fout << endl << endl;
	fout << "Sorting array of students by non-decreasing order of ID : " << endl;
	sortStudentsByID(students, NUM_STUDENTS);
	fprintBigArrayOfStudent_IDs(fout, students, NUM_STUDENTS, NUM_FIRST_LAST_BLOCK);
	/*바이너리 서칭 후 출력*/
	fout << endl << endl;
	fout << "Searching student with student_ID : " << endl;

	for (int i = 0; i < NUM_SEARCH; i++)
	{
		pSt = searchStudentByID(students, NUM_STUDENTS, student_search[i]);
		fout << "Student search by ID (" << setw(4) << student_search[i] << ") : ";
		if (pSt != NULL)
			fprintStudent(fout, pSt);
		else
			fout << "NULL - student was not found !!";
		fout << endl;
	}
	/*동적 할당 해제*/
	free(student_ids);
	free(students);
	fout.close();
}