/**
*파일명 : "객체지향형_프로그래밍과_자료구조_실습_2"
*프로그램의 목적 및 기본 기능: 
*      -이 프로그램은 현재 날짜로부터 크리스마스가 얼마나 남았는지 확인한다.
*	   -학생들의 데이터를 생성하고, 이름과 생일을 랜덤하게 부여한다.
*프로그램 작성자 : 김민관(2022년 09월 12일)
*최종 Update : Version 1.0, 2022년 09월 12일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*============================================================================
*/


#ifndef DATE_H
#define DATE_H
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <iomanip>

using namespace std;
#define WEEKDAY_AD01Jan01 MON
// the weekday of AD Jan 1.
#define DAYS_PER_WEEK 7
#define Secs_in_Minute 60
#define Secs_in_Hour (Secs_in_Minute * 60)
#define Secs_in_DAY (Secs_in_Hour * 24)
#define LOCAL_GMT_OFFSET_HOUR 9
class Date
{
public:
	Date(); // default constructor
	Date(int y, int m, int d); // constructor
	//~Date(); // destructor
	//void inputDate(); //inputing date by console
	//void printDate(); //printing date by console
	void fprintDate(ostream& fout); //instead of printData
	void setDate(int y, int m, int dy); //setting Date by parameter
	void setMonth(int m); // check the month in collect range
	void setRandDateAttributes(); //setting a particular value as random
	int getYear() { return year; }
	int getMonth() { return month; }
	int getDay() { return day; }
	int getYearDay(); //calculate how long the date has passed(private)
	//int getYearDay(int m, int d);
	int getYearDay(int m, int d); //claculate how long the date has passed(global)
	int getWeekDay(); //init yearDay, weekDay, elapsedDays, weekDay since 010101
	int getElapsedDaysFromAD010101(); //calulate how long the date has passed since 010101

private:
	bool isLeapYear(); //check leap year
	bool isLeapYear(int y);
	bool isValidDate(int y, int m, int d);//check the date in normal range
	int year;
	int month;
	int day;
};
#endif