/**
*파일명 : "객체지향형_프로그래밍과_자료구조_실습_4_21912229_김민관"
*프로그램의 목적 및 기본 기능: 
*      -이 프로그램은 행렬을 txt파일로 부터 받아, 사칙연산을 수행하여 
*		txt파일에 출력하는 프로그램이다.
*	   -연산에 사용된 방법은 연산자 오버로딩방법으로 구현되어있다.
*프로그램 작성자 : 김민관(2022년 10월 04일)
*최종 Update : Version 1.0, 2022년 10월 04일(김민관)
*============================================================================
*/

#ifndef MTRX_H
#define MTRX_H
#include <string>
using namespace std;
#define SETW 8

class MtrxArray;
class Mtrx {
	//friend function-----------------------------------------
	friend ostream& operator<< (ostream& fout, const Mtrx& m); //to print mtrx in file(.txt)
	friend istream& operator>> (istream& fin, Mtrx& m); // to input mtrx in file(.txt)
	friend class MtrxArray; //Give MtrxArray access authority in private member
public:
	Mtrx() : n_row(0), n_col(0), name("no_name"), dM(NULL) {} // defaut constructor
	Mtrx(string nm, int num_row, int num_col); //input constructor
	~Mtrx(); //destructor
	//inline function-----------------------------------------
	void init(int num_row, int num_col); //intialize
	void set_name(string nm) { name = nm; } //name setting
	string get_name() { return name; } //string type name function
	int get_n_row() const { return n_row; } //get array's row size
	int get_n_col() const { return n_col; } //get array's col size
	//operator overloading function---------------------------
	const Mtrx operator+(const Mtrx& mA); //add operation
	const Mtrx operator-(const Mtrx& mA); //sub operation
	const Mtrx operator*(const Mtrx& mA); //multiplication operation
	const Mtrx operator~(); // returns transposed matrix
	const Mtrx& operator=(const Mtrx& mA); //substitution operation
	bool operator==(const Mtrx& mA); // equivalent operation
	bool operator!=(const Mtrx& mA); // unequivalent operation
private:
	string name; //mtrix name
	int n_row; //matrix row size
	int n_col; //matrix col size
	double** dM; //double type dynamic array 
};
#endif
