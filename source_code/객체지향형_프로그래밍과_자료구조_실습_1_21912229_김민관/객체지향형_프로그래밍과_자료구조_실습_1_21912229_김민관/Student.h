#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdbool.h>

using namespace std;
typedef struct
{
	int st_id; //�й�
	char name[16]; //�̸� (�ִ� 16��)
	char dept[16]; //�а� (�ִ� 16��)
	int grade; //�г�
	double gpa; //����
} Student;
void initStudents(Student students[], int st_ids[], int num_students); //�л��ʱ�ȭ
void fprintStudent(ostream& fout, Student* pSt);  //�̸��� ���
void fprintStudentIDs(ostream& fout, Student students[]); //�й��� ���
void fprintBigArrayOfStudent_IDs(ostream& fout, Student students[], int num_students, int num_first_last); //�й����� ���
void sortStudentsByID(Student students[], int num_students); //�й����� ����
void sortStudentsByGPA_ID(Student students[], int num_students); //�������� ����

void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student students[], int num_students, int num_first_last); //������ �й� ���
Student* searchStudentByID(Student students[], int num_students, int st_ID); // �й����� �����˻�
