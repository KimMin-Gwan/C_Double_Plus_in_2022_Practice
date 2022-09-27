#include <iostream>
#include <fstream>
#include "Class_Mtrx.h"
using namespace std;
void main()
{
	ifstream fin;
	ofstream fout;
	fin.open("Matrix_input.txt");  //mtrix element data
	if (fin.fail())
	{
		cout << "Error in opening Matrix_5x5_data.txt !!" << endl;
		exit;
	}
	fout.open("output.txt");  //output txt
	if (fout.fail())
	{
		cout << "Error in opening Matrix_operations_results.txt !!" << endl;
		exit;
	}
	//making matrix A
	Mtrx mtrxA(fin);
	mtrxA.setName("mtrxA");
	mtrxA.fprintMtrx(fout);
	//making matrix B
	Mtrx mtrxB(fin);
	mtrxB.setName("mtrxB");
	mtrxB.fprintMtrx(fout);
	//making matrix C
	Mtrx mtrxC(fin);
	mtrxC.setName("mtrxC");
	mtrxC.fprintMtrx(fout);
	//add matrix A with B
	Mtrx mtrxD(mtrxA.getN_row(), mtrxB.getN_col());
	mtrxD = mtrxA.addMtrx(mtrxB);
	mtrxD.setName("mtrxD = mtrxA.addMtrx(mtrxB)");
	mtrxD.fprintMtrx(fout);
	//sub matrix A with B
	Mtrx mtrxE(mtrxA.getN_row(), mtrxB.getN_col());
	mtrxE = mtrxA.subMtrx(mtrxB);
	mtrxE.setName("mtrxE = mtrxA.subMtrx(mtrxB)");
	mtrxE.fprintMtrx(fout);
	//mul matrix A with C
	Mtrx mtrxF(mtrxA.getN_row(), mtrxC.getN_col());
	mtrxF = mtrxA.mulMtrx(mtrxC);
	mtrxF.setName("mtrxF = mtrxA.mulMtrx(mtrxC)");
	mtrxF.fprintMtrx(fout);
	//transpose Matrix A
	Mtrx mtrxG(mtrxA.getN_col(), mtrxA.getN_row());
	mtrxG = mtrxA.transposeMtrx();
	mtrxG.setName("mtrxG = mtrxA.transposeMtrx()");
	mtrxG.fprintMtrx(fout);
	fout.close();
	//할당해제
} // end of main()