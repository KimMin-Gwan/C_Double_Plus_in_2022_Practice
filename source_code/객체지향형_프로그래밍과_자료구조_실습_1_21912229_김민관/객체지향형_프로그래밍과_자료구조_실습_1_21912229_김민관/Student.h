#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdbool.h>

using namespace std;
typedef struct
{
	int st_id; //학번
	char name[16]; //이름 (최대 16자)
	char dept[16]; //학과 (최대 16자)
	int grade; //학년
	double gpa; //학점
} Student;
void initStudents(Student students[], int st_ids[], int num_students); //학생초기화
void fprintStudent(ostream& fout, Student* pSt);  //이름을 출력
void fprintStudentIDs(ostream& fout, Student students[]); //학번만 출력
void fprintBigArrayOfStudent_IDs(ostream& fout, Student students[], int num_students, int num_first_last); //학번으로 출력
void sortStudentsByID(Student students[], int num_students); //학번으로 정렬
void sortStudentsByGPA_ID(Student students[], int num_students); //학점으로 정렬

void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student students[], int num_students, int num_first_last); //성적과 학번 출력
Student* searchStudentByID(Student students[], int num_students, int st_ID); // 학번으로 이진검색
