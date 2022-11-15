#include "Date.h"

int days_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
istream& operator >> (istream& cin, Date& dt)
{
	int year = 0, month = 0, day = 0;
	cout << "Enter date in year month day :";
	cin >> year >> month >> day;	
	dt.setDate(year, month, day);
	return cin;
}
ostream& operator << (ostream& out, const Date& dt)
{
	out << "(" << setw(4) << dt.year << "-"
		<< setw(2) << dt.month << "-" << setw(2) << dt.day << ")";

	return out;
}
Date::Date()
{
	year = 1; month = 1; day = 1;
}
Date::Date(int y, int m, int d)
{
	setDate(y, m, d);
}

void Date::setDate(int newYear, int newMonth, int newDay)
{
	this->year = newYear; //input the Year
	if ((newMonth >= 1) && (newMonth <= 12)) //Ensure correct input
		this->month = newMonth; 
	else {
		cout << "Illegal month value! Program aborted.\n"; exit(1);
	}
	if ((newDay >= 1) && (newDay <= 31)) //Ensure correct input
		day = newDay;
	else {
		cout << "Illegal day value!! Program aborted.\n"; exit(1);
	}
}
int Date::getYearDay()
{
	int yearDay = 0;
	if (isLeapYear()) //check the leap year
		days_month[2] = 29;
	for (int m = 1; m < month; m++)
		yearDay += days_month[m]; //add the day in each months
	yearDay += day; //add least day 
	return yearDay; // return the sum
}
int Date::getWeekDay()
{
	int weekDay_AD010101 = MON;
	// AD Jan. 1, 1 was Monday
	int yearDay = 1;
	int weekDay = 1;
	int elapsedDays = 0;

	return weekDay;
}
int Date::getElapsedDays()
{
	int yearDay;
	int elpsDay = 0;
	for (int y = 1; y < year; y++)
	{
		elpsDay += 365;		//add of the day from A010101 to last year
	}
	yearDay = getYearDay(); //add how this year passed
	elpsDay += yearDay;
	return elpsDay; //return sum
}

const Date Date::operator = (const Date rightSide)
{
	this->year = rightSide.year; //asign year
	this->month = rightSide.month; //asign month
	this->day = rightSide.day; //asign day
	return *this;
}

bool Date::operator > (Date rightSide)
{
	if (this->year == rightSide.year) //compare year element
	{
		if (this->month == rightSide.month) //compare month element
		{
			if (this->day > rightSide.day) //compare day element
				return true;
			else
				return false;
		}
		else if (this->month > rightSide.month)
			return true;
		else
			return false;
	}
	else if (this->year > rightSide.year)
		return true;
	else
		return false;
}

bool Date::operator < (Date rightSide)
{
	if (this->year == rightSide.year)//compare year element
	{
		if (this->month == rightSide.month)//compare month element
		{
			if (this->day < rightSide.day)//compare day element
				return true;
			else
				return false;
		}
		else if (this->month < rightSide.month)
			return true;
		else
			return false;
	}
	else if (this->year < rightSide.year)
		return true;
	else
		return false;

}

bool Date::operator >= (Date rightSide)
{
	if (this->year == rightSide.year) //compare year element
	{
		if (this->month == rightSide.month) //compare month element
		{
			if (this->day >= rightSide.day) //compare day element
				return true;
			else
				return false;
		}
		else if (this->month > rightSide.month)
			return true;
		else
			return false;
	}
	else if (this->year > rightSide.year)
		return true;
	else
		return false;
}

bool Date::operator <= (Date rightSide)
{
	if (this->year == rightSide.year)//compare year element
	{
		if (this->month == rightSide.month)//compare month element
		{
			if (this->day <= rightSide.day)//compare day element
				return true;
			else
				return false;
		}
		else if (this->month < rightSide.month)
			return true;
		else
			return false;
	}
	else if (this->year < rightSide.year)
		return true;
	else
		return false;
}

bool Date::operator == (Date rightSide)
{
	int flag = 0; //if Date's each elements is same, flag will added
	this->year == rightSide.year ? flag++ : flag = 0; 
	this->month == rightSide.month ? flag++ : flag = 0;
	this->day == rightSide.day ? flag++ : flag = 0;
	if (flag == 3) //if 3 all index are saem, flag will 3
		return true;
	else
		return false;
}
bool Date::operator != (Date rightSide)
{
	int flag = 0; //if Date's each elements is same, flag will added
	this->year == rightSide.year ? flag++ : flag = 0; 
	this->month == rightSide.month ? flag++ : flag = 0;
	this->day == rightSide.day ? flag++ : flag = 0;
	if (flag != 3) //if 3 all index are saem, flag will 3
		return true;
	else
		return false;

}
bool Date::isLeapYear(int y)
{
	if (y % 4 == 0)
	{
		if ((y % 100 == 0) && (y % 400 == 0))
			return true;
	}
	else
	{
		return false;
	}
}
//private function----------------------------------------------
bool Date::isLeapYear()
{
	if (isLeapYear(year))
		return true;
	else
		return false;
}
bool Date::isValidDate(int y, int m, int d)
{
	if (isLeapYear(y))
		days_month[2] = 29;
	if ((m >= 1) && (m <= 12) &&
		(d >= 1) && (d <= days_month[m]))
	{
		return true;
	}
	else
	{
		cout << "Ilegal date! (" << m << ", "
			<< d << ") ==> Program aborted.\n";
		return false;
	}
}
//out of class--------------------------------------------------
bool isLeapYear(int y) {
	if (y % 4 == 0)
	{
		if ((y % 100 == 0) && (y % 400 == 0))
			return true;
	}
	else
	{
		return false;
	}

}
Date genRandDate() {
	int newYear = rand() % 1000 + 1999;
	int newMonth = rand() % 12 + OFFSET;
	int newDay = 0;
	if (newMonth == 2)
	{
		if (isLeapYear(newYear))
			newDay = rand() % 29 + OFFSET;
		else
			newDay = rand() % 28 + OFFSET;
	}
	else
	{
		newDay = rand() % days_month[newMonth] + OFFSET;
	}
	Date newDate(newYear, newMonth, newDay);
	return newDate;
}
