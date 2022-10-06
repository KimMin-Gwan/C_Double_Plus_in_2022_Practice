#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <iomanip>
#define OFFSET 1
enum WEEKDAY { SUN, MON, TUE, WED, THR, FRI, SAT };
using namespace std;

class Date {
	friend istream& operator >> (istream& fin, Date& dt);
	friend ostream& operator << (ostream& fout, const Date& dt);
public:
	Date(); // default constructor
	Date(int y, int m, int d); // constructor
	//-------------------accessor and mutater------------------------------------
	void setDate(int newYear, int newMonth, int newDay); //set the private 
	int getYear() { return year; } //return year
	int getYearDay(); //calculate how long the date has passed sins 0101
	int getWeekDay(); //init yearDay, weekDay, elapsedDays, weekDay since 010101
	int getElapsedDays(); //calulate how long the date has passed since 010101
	//-------------------operater------------------------------------------------
	const Date operator = (const Date rightSide); //asign operation
	bool operator > (Date rightSide); //compare operater
	bool operator < (Date rightSide); //compare operater
	bool operator == (Date rightSide); //equl operater
	bool operator != (Date rightSide); //diffrential operater
	bool isLeapYear(int y); //chek the Leap Year
private:
	bool isLeapYear(); //check leap year
	bool isValidDate(int y, int m, int d);//check the date in normal range
	int year;
	int month;
	int day;
};
bool isLeapYear(int y);
Date genRandDate();
#endif