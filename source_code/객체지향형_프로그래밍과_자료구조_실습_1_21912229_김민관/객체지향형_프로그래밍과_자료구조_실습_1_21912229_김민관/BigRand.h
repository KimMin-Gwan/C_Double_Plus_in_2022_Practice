#ifndef BIGRAND_H
#define BIGRAND_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <stdbool.h>
using namespace std;

int* genBigRandArray(int num_rands, int offset);	//�������� ������
void fPrintBigRandArray(ofstream& fout, int* bigRand, int num_rands);//���		

#endif
