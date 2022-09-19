#pragma once
/**
*���ϸ� : "���α׷��� ���_21912229_��ΰ�_�ǽ�_3"
*���α׷��� ���� �� �⺻ ���:
*      -�� ���α׷��� 2���� ����� �����Ѵ�
*	   -2���� ����� ���ϰ�, ����, ���ϰ�, ��ġ�Ѵ�.
*���α׷� �ۼ��� : ��ΰ�(2022�� 09�� 18��)
*���� Update : Version 1.0, 2022�� 09�� 18��(��ΰ�)
*============================================================================
*���α׷� ����/���� �̷�
*============================================================================
*���α׷� ����/�����۾���   ����   ����/���ϳ���
*��ΰ�      2022/00/00      v1.0   ��������
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