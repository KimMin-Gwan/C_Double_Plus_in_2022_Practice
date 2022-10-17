/**
*파일명 : "Practice_7-2"
*프로그램의 목적 및 기본 기능: 
*      -이 프로그램은 Student를 템플릿을 이용하여 생성하고, 템플릿에서
*		key를 이용한 정렬알고리즘을 시행하는 프로그램이다.
*프로그램 작성자 : 김민관(2022년 10월 18일)
*최종 Update : Version 1.0, 2022년 10월 18일(김민관)
*============================================================================
*/

#ifndef PERSON_H
#define PERSON_H
#include <iostream>
#include <string>
using namespace std;
class Person
{
	friend ostream& operator<< (ostream& fout, const Person& p);
public:
	//only_in_lined_fucntions-----------------------------------------
	Person() { name = "nobody"; } //constructor
	Person(string n) { name = n; } //constructor
	//mutator-------------------------
	void set_name(string n) { name = n; }
	void set_nation(string country) { nation = country; }
	void set_regID(int rgID) { regID = rgID; } 
	//accesser------------------------
	const string get_name() const { return name; } //name
	const string get_nation() const { return nation; } //nation
	const int get_regID() const { return regID; } //register ID
protected:
	string name;
	int regID;
	string nation;
};
#endif
