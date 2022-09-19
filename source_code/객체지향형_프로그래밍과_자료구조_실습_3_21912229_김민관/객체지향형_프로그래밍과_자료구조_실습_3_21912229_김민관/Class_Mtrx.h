#pragma once
/**
*파일명 : "프로그래밍 언어_21912229_김민관_실습_3"
*프로그램의 목적 및 기본 기능:
*      -이 프로그램은 2차원 행렬을 생성한다
*	   -2차원 행렬을 더하고, 빼고, 곱하고, 전치한다.
*프로그램 작성자 : 김민관(2022년 09월 18일)
*최종 Update : Version 1.0, 2022년 09월 18일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*프로그램 수정/보완작업자   일자   수정/보완내용
*김민관      2022/00/00      v1.0   수정내용
*============================================================================
*/
#ifndef MTRX_H
#define MTRX_H
#include <iostream>
#include <fstream>
using namespace std;
#define MAX_SIZE 100
#define SETW 7 //fprint in 7 partition
#define DECIMAL_POINT 2

class Mtrx {
public:
	Mtrx(int num_row, int num_col); //constructer
	Mtrx(istream& fin); //constructer(by file)
	~Mtrx(); // destructor
	//in-line function-------------------------
	int getN_row() { return n_row; }
	int getN_col() { return n_col; }
	void setName(string nm) { name = nm; };
	string getName() { return name; };
	//mutater-----------------------------------
	Mtrx addMtrx(const Mtrx&); //add Mtrix
	Mtrx subMtrx(const Mtrx&); //sub Mtrix
	Mtrx mulMtrx(const Mtrx&); //mul Mtrix
	Mtrx transposeMtrx(); // swap transposed matrix

	void fprintMtrx(ostream& fout);
private:
	string name; //mtrix name
	int n_row; //size of row
	int n_col; //size of col
	double** dM; //elements
};
#endif