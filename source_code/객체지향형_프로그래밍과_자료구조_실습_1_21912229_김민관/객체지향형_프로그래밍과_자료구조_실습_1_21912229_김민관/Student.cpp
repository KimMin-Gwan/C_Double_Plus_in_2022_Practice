#include "Student.h"

#define BIG_SIZE 300
#define LINESIZE 10

void initStudents(Student students[], int st_ids[], int num_students)
{
	//학생 배열 초기화
	srand(time(NULL));
	for (int i = 0; i < num_students; i++)
	{
		int nameLength = rand() % 10 + 5; //이름 길이( 5 ~ 15)
		int deptLength = rand() % 2 + 3; //학과 이름(2 ~ 5) 

		for (int j = 0; j < nameLength; j++)
		{
			if (j == 0)
				students[i].name[j] = rand() % 26 + 'A'; //첫글자 대문자
			else
				students[i].name[j] = rand() % 26 + 'a';
		}
		students[i].name[nameLength] = '\0'; //공백문자

		for (int j = 0; j < deptLength; j++)
		{
			students[i].dept[j] = rand() % 26 + 'A'; //학과이름
		}
		students[i].dept[deptLength] = '\0'; //공백문자

		students[i].st_id = st_ids[i];	//학번
		students[i].grade = rand() % 8 + 1;	//학년
		students[i].gpa = ((rand() % 10000) / 100.0); //성적
	}
}

void fprintStudent(ostream& fout, Student* pSt)
{

	fout.setf(ios::fixed);		// 고정소수점사용
	fout.setf(ios::showpoint);	// 소수점표시
	fout.precision(2);	// 소수점 2자리만 표시

	fout << "Student(ID: " << setw(4) << pSt->st_id << ", "; // 학번
	fout << "Name: " << setw(16) << pSt->name << ", ";	 // 이름
	fout << "Dept: " << setw(5) << pSt->dept << ", "; // 학과
	fout << "Grade: " << pSt->grade << ", "; // 학년
	fout << "GPA: " << setw(5) << pSt->gpa;	// 성적
}

void fprintStudentIDs(ostream& fout, Student students[])
{
	fout << setw(7) << students->st_id;
}

void fprintBigArrayOfStudent_IDs(ostream& fout, Student students[], int num_students, int num_first_last)
{
	Student* pSt;
	int count = 0;
	if (num_students <= num_first_last * 2)
	{
		for (int i = 0; i < num_students; i++)
		{
			pSt = &students[i];
			fout << setw(6) << pSt->st_id;
			count++;
			if ((count % 20) == 0)
				fout << endl;
		}
		return;
	}
	for (int i = 0; i < num_first_last; i++)
	{
		pSt = &students[i];
		fout << setw(6) << pSt->st_id;
		count++;
		if ((count % 20) == 0)
			fout << endl;
	}
	fout << " . . . . . " << endl;
	for (int i = num_students - num_first_last; i < num_students; i++)
	{
		pSt = &students[i];
		fout << setw(6) << pSt->st_id;
		count++;
		if ((count % 20) == 0)
			fout << endl;
	}
}

void fprintStudentGPA_ID(ostream& fout, Student* pSt)
{
	fout.setf(ios::fixed);
	fout.setf(ios::showpoint);
	fout.precision(2);

	fout << "(" << setw(5) << pSt->gpa << ", " << setw(5) << pSt->st_id << ") ";
}

void fprintBigArrayOfStudent_GPA_IDs(ostream& fout, Student students[], int num_students, int num_first_last)
{
	int count = 0;
	int num_lines = num_first_last / LINESIZE;
	Student* pSt = NULL;

	if (num_students < BIG_SIZE)
	{
		num_lines = num_students / LINESIZE;
	}

	for (int i = 0; i < num_lines; i++)
	{
		for (int j = 0; j < LINESIZE; j++)	// 10개씩 출력
		{
			pSt = &students[count];
			if (count == num_students)		// 전부 출력했으면 탈출
				break;
			fprintStudentGPA_ID(fout, pSt);	//출력
			count++;
		}
		fout << endl;
	}

	if (num_students >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;
		count = num_students - (LINESIZE * num_lines);

		for (int i = 0; i < num_lines; i++)
		{
			for (int j = 0; j < LINESIZE; j++)
			{
				pSt = &students[count];
				fprintStudentGPA_ID(fout, pSt);	// 출력
				count++;
			}
			fout << endl; // 한줄 띄우기
		}
		fout << endl;
	}
}

void sortStudentsByID(Student students[], int num_students)
{
	Student temp;
	int min_index = 0;
	int sort_index = 0;

	while (true)
	{
		if (sort_index == num_students) // 마지막에 도착하면 종료
			break;
		temp = students[sort_index]; // 인덱스 선택
		min_index = sort_index; //최소값 업데이트 

		for (int i = sort_index; i < num_students; i++)
		{
			if (temp.st_id > students[i].st_id) //더 작은 값이 등장하면
			{
				temp = students[i]; //값을 업데이트
				min_index = i;
			}
		}
		//교체
		students[min_index] = students[sort_index];
		students[sort_index] = temp;
		sort_index++;
	}

}
void sortStudentsByGPA_ID(Student students[], int num_students)
{
	Student temp;
	int max_index = 0;
	int sort_index = 0;
	//int min_ID_index = 0;

	sortStudentsByID(students, num_students);

	while (true)
	{
		if (sort_index == num_students)	 // 마지막에 도착하면 종료
			break;
		temp = students[sort_index];// 인덱스 선택
		max_index = sort_index;	// 최대값 업데이트

		for (int i = sort_index; i < num_students; i++)
		{
			if (temp.gpa < students[i].gpa)	 // 성적이 더 크면
			{
				temp = students[i];	//데이터 업데이트
				max_index = i;
			}
			else if (temp.gpa == students[i].gpa) //같은 성적이라면 학번비교
			{
				if (temp.st_id < students[i].st_id)
				{
					temp = students[i]; //값을 업데이트
					max_index = i;
				}
			}
		}
		//변경
		students[max_index] = students[sort_index];
		students[sort_index] = temp;
		sort_index++;
	}
}

Student* searchStudentByID(Student students[], int num_students, int st_ID)  //학번으로 이진검색
{
	int first = 0;  //처음 
	int last = num_students - 1;//끝
	int mid; //중간

	if ((st_ID > students[num_students - 1].st_id) || (st_ID < students[0].st_id))
		return NULL;	// 값이 범위 내에 없을 경우 NULL을 반환

	while (first <= last)
	{
		mid = (first + last) / 2;				// mid 찾기
		if (st_ID == students[mid].st_id)	// 만약 중간이면 바로 반환
			return &students[mid];
		else if (st_ID < students[mid].st_id)		//찾는 값이 중간보다 작으면
			last = mid - 1;		// 최대를 중간보다 하나 작은값으로 설정
		else
			first = mid + 1;	//최소를 중간으로 설정
	}
}