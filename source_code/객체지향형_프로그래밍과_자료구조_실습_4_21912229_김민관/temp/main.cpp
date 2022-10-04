#include <iostream>
#include <fstream>
#include <string>
#include "Mtrx.h"
#include "MtrxArray.h"
using namespace std;
#define NUM_MTRX 8
int main()
{
	ifstream fin;
	ofstream fout;
	int n_row, n_col;
	fin.open("input.txt");
	if (fin.fail())
	{
		cout << "Error in opening input data file !!" << endl;
		exit;
	}
	fout.open("Result.txt");
	if (fout.fail())
	{
		cout << "Error in opening output data file !!" << endl;
		exit;
	}
	MtrxArray mtrx(NUM_MTRX);
	fin >> mtrx[0] >> mtrx[1] >> mtrx[2];
	mtrx[0].set_name("mtrx[0]");
	mtrx[1].set_name("mtrx[1]");
	mtrx[2].set_name("mtrx[2]");
	fout << mtrx[0] << endl;
	fout << mtrx[1] << endl;
	fout << mtrx[2] << endl;
	mtrx[3] = mtrx[0] + mtrx[1];
	mtrx[3].set_name("mtrx[3] = mtrx[0] + mtrx[1]");
	fout << mtrx[3] << endl;
	mtrx[4] = mtrx[0] - mtrx[1];
	mtrx[4].set_name("mtrx[4] = mtrx[0] - mtrx[1]");
	fout << mtrx[4] << endl;
	mtrx[5] = mtrx[0] * mtrx[2];
	mtrx[5].set_name("mtrx[5] = mtrx[0] * mtrx[2]");
	fout << mtrx[5] << endl;
	mtrx[6] = ~mtrx[5];
	mtrx[6].set_name("mtrx[6] = ~mtrx[5] (transposed matrix)");
	fout << mtrx[6] << endl;
	mtrx[7] = mtrx[0];
	mtrx[7].set_name("mtrx[7] = mtrx[0]");
	fout << mtrx[7] << endl;
	if (mtrx[7] == mtrx[0])
		fout << "mtrx[7] and mtrx[0] are equal.\n";
	if (mtrx[5] != mtrx[6])
		fout << "mtrx[5] and mtrx[6] are not equal.\n";
	fin.close();
	fout.close();
	return 0;
}