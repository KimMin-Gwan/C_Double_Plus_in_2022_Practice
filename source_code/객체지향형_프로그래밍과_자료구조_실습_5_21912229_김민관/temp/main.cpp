#include <iostream>
#include <fstream>
#include "StudentArray.h"
#include <string>
#include <time.h>
#define NUM_STUDENTS 10
int main()
{
	StudentArray studentArray(NUM_STUDENTS);
	Student st;
	ofstream fout;
	//srand(time(NULL));
	int st_ids[NUM_STUDENTS];
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open an output file (output.txt)\n";
		exit(1);
	}
	genST_ids(NUM_STUDENTS, st_ids);
	fout << "Initializing student array (num_students: " << NUM_STUDENTS << ")" << endl;
	for (int i = 0; i < NUM_STUDENTS; i++)
	{
		st = genRandStudent(st_ids[i]);
		cout << "name : " << st.getName() << endl;
		cout << "birthday :" << st.getBirthDate() << endl;
		cout << "dept name : " << st.getDept_name() << endl;
		studentArray[i] = st;
	}
	fout << studentArray;
	fout << "\nSorting studentArray by student id : " << endl;
	studentArray.sortByST_ID();
	fout << studentArray;
	fout << "\nSorting studentArray by student name : " << endl;
	studentArray.sortByName();
	fout << studentArray;
	fout << "\nSorting studentArray by GPA : " << endl;
	studentArray.sortByGPA();
	fout << studentArray;
	fout << "\nSorting studentArray by BirthDate : " << endl;
	studentArray.sortByBirthDate();
	fout << studentArray;
	fout << endl;
	fout.close();
	return 0;
}