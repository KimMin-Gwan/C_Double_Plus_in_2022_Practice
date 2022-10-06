/**
*파일명 : "객체지향형_프로그래밍과_자료구조_실습_5_21912229_김민관"
*프로그램의 목적 및 기본 기능: 
*      -이 프로그램은 학생 정보를 랜덤하게 생성하여 정렬하고, 출력하는 프로그램이다.
*	   -연산는 Person클래스를 Student클래스가 상속받아서 사용한다.
*프로그램 작성자 : 김민관(2022년 10월 07일)
*최종 Update : Version 1.0, 2022년 10월 07일(김민관)
*============================================================================
*/

#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <iomanip>
#include "Date.h"
using namespace std;
#define MAX_NAME_LEN 15
#define MIN_NAME_LEN 5

class Person
{
	friend ostream& operator << (ostream& fout, const Person& ps);
public:
	Person() { birthDate = Date(1, 1, 1); name = ""; } //constructer
	Person(string nm, Date bd) { birthDate = bd; name = nm; } //construct with name nad birthday
	//------------------accessor and mutator--------------------------------------------
	void setName(string n) { name = n; }  //setting name
	void setBirthDate(Date bd) { birthDate = bd; } //setting Birthday
	string getName() const { return name; } // return name
	Date getBirthDate() const { return birthDate; } //return Birthday
protected:
	Date birthDate;
	string name;
};
#endif
