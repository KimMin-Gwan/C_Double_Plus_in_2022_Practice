#include "Mtrx.h"
#include <iostream>
#include <iomanip>
using namespace std;
typedef double* DBLPTR;

istream& operator >> (istream& fin, Mtrx& m)
{
	int num_row, num_col, cnt;
	double d;

	fin >> num_row >> num_col;
	cout << num_row << num_col << endl;
	m.n_row = num_row;
	m.n_col = num_col;
	m.dM = new DBLPTR[m.n_row]; //making row
	for (int i = 0; i < m.n_row; i++) //making col
	{
		m.dM[i] = new double[m.n_col];
	}
	//cnt = 0;
	for (int i = 0; i < m.n_row; i++)
	{
		for (int j = 0; j < m.n_col; j++) {
			if (!fin.eof())
			{
				fin >> m.dM[i][j];
				cout << m.dM[i][j] << setw(SETW);
				//cnt++;
			}
			else
			{
				m.dM[i][j] = 0.0;
			}
		}
		cout << endl;
	}
	return fin;
}

ostream& operator<< (ostream& fout, const Mtrx& m)
{
	unsigned char a6 = 0xA6, a1 = 0xA1, a2 = 0xA2;
	unsigned char a3 = 0xA3, a4 = 0xA4, a5 = 0xA5;
	fout << m.name << endl;

	for (int i = 0; i < m.n_row; i++) {
		for (int j = 0; j < m.n_col; j++)
		{
			fout.setf(ios::fixed);
			fout.precision(2);
			if ((i == 0) && (j == 0))
			{
				fout << a6 << a3 << setw(SETW) << m.dM[i][j];
				cout << a6 << a3 << setw(SETW) << m.dM[i][j];
			}
			else if ((i == 0) && (j == (m.n_row - 1)))
			{
				fout << setw(SETW) << m.dM[i][j] << a6 << a4;
				cout << setw(SETW) << m.dM[i][j] << a6 << a4;
			}
			else if ((i > 0) && (i < (m.n_row - 1)) && (j == 0))
			{
				fout << a6 << a2 << setw(SETW) << m.dM[i][j];
				cout << a6 << a2 << setw(SETW) << m.dM[i][j];
			}
			else if ((i > 0) && (i < (m.n_row - 1)) && (j == (m.n_col - 1)))
			{
				fout << setw(SETW) << m.dM[i][j] << a6 << a2;
				cout << setw(SETW) << m.dM[i][j] << a6 << a2;
			}
			else if ((i == (m.n_row - 1)) && (j == 0))
			{
				fout << a6 << a6 << setw(SETW) << m.dM[i][j];
				cout << a6 << a6 << setw(SETW) << m.dM[i][j];
			}
			else if ((i == (m.n_row - 1)) && (j == (m.n_col - 1)))
			{
				fout << setw(SETW) << m.dM[i][j] << a6 << a5;
				cout << setw(SETW) << m.dM[i][j] << a6 << a5;
			}
			else
			{
				fout << setw(SETW) << m.dM[i][j];
				cout << setw(SETW) << m.dM[i][j];
			}
		}
		fout << endl;
		cout << endl;
	}
	fout << endl;
	cout << endl;
	return fout;
}


Mtrx::Mtrx(string nm, int num_row, int num_col) //input constructor
	: n_row(num_row), n_col(num_col), name(nm)
{
	cout << "construct new Mtrx (name : " << name << ")" << endl;
	cout << "n_row : " << num_row << "  n_col : " << num_col << endl;
	init(n_row, n_col);
}

Mtrx::~Mtrx() //destructor
{
	cout << "Mtrx (" << name << ") detroied" << endl;
	/*
	for(int i = 0;, i < n_row;, i++)  //delete each row
	{
		delete[] dM[i];
	}
	delete[] dM[]; // delete col
	*/
}

void Mtrx::init(int num_row, int num_col) //intialize
{
	n_row = num_row, n_col = num_col;
	//cout << n_row << "  " << n_col << endl;
	this->dM = new DBLPTR[this->n_row]; //making row
	for (int i = 0; i < this->n_row; i++) //making col
	{
		this->dM[i] = new double[this->n_col];
	}
	
	for (int i = 0; i < n_row; i++)
	{
		for (int j = 0; j < n_col; j++) {
			dM[i][j] = 0;
			//cout << dM[i][j];
		}
		//cout << endl;
	}
	//cout << endl;
}
const Mtrx Mtrx:: operator+(const Mtrx& mA) //add operation
{
	Mtrx mR("mR_add", n_row, n_col); //Results to be returned

	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_col; j++)
			mR.dM[i][j] = dM[i][j] + mA.dM[i][j];
	return mR;
}

const Mtrx Mtrx:: operator-(const Mtrx& mA) //sub operation
{
	Mtrx mR("mR_sub", n_row, n_col);//Results to be returned

	for (int i = 0; i < n_row; i++)
		for (int j = 0; j < n_col; j++)
			mR.dM[i][j] = dM[i][j] - mA.dM[i][j];

	return mR;
}
const Mtrx Mtrx:: operator*(const Mtrx& mA) //multiplication operation
{
	Mtrx mR("mR_mul", n_row, mA.n_col); //Results to be returned

	for (int i = 0; i < n_row; i++) {
		for (int j = 0; j < mA.get_n_col(); j++) {
			mR.dM[i][j] = 0.0;
			for (int k = 0; k < n_col; k++)
				mR.dM[i][j] += dM[i][k] * mA.dM[k][j];
		}
	}

	return mR;
}
const Mtrx Mtrx:: operator~() // returns transposed matrix
{

	Mtrx mR("mR_trans", n_row, n_col); //Results to be returned

	for (int i = 0; i < n_col; i++) // i range change
		for (int j = 0; j < n_row; j++) //j range change
			mR.dM[i][j] = dM[j][i];

	return mR;
}
const Mtrx& Mtrx::operator=(const Mtrx& mA) //substitution operation
{   /*
	n_row = mA.get_n_row(); n_col = mA.get_n_col();
	cout << "n_col : " << mA.get_n_col() << "  n_row" << mA.get_n_row();
	Mtrx mR("mR_copy", n_row, n_col); //Results to be returned
	*/
	init(mA.get_n_row(), mA.get_n_col());
	//retrun as self reference
	for (int i = 0; i < mA.n_row; i++) {
		for (int j = 0; j < mA.n_col; j++)
		{
			//cout << this->dM[i][j] << " = " << mA.dM[i][j] << setw(SETW);
			this->dM[i][j] = mA.dM[i][j]; // copying target matix element
		}
		//cout << endl;
	}
	return *this;
}
bool Mtrx::operator==(const Mtrx& mM)
{
	int count = 0;	//count the equal type

	if (this->n_row == mM.n_row && this->n_col == mM.n_col)	//if length of n_row and n_col are equal
	{
		for (int i = 0; i < n_row; i++)
		{
			for (int j = 0; j < n_col; j++)
			{
				if (this->dM[i][j] == mM.dM[i][j]) //check each index elements are equal
					count++; //if both elements are same, count++
			}
		}
		if (count == n_row * n_col) //if count is same with mtrx size, return true
			return true;
		else
			return false;
	}
	else
		return false;
}
bool Mtrx::operator!=(const Mtrx& mM)
{
	int count= 0;

	if (this->n_row != mM.n_row || this->n_col != mM.n_col) //if length of n_row and n_col are not equal return true
		return true;
	else
	{								
		for (int i = 0; i < n_row; i++)
		{
			for (int j = 0; j < n_col; j++)
			{
				if (this->dM[i][j] == mM.dM[i][j])//check each index elements are equal
					count++;
			}
		}
		if (count!= n_row * n_col)//if count is not same with mtrx size, return true
			return true;
		else
			return false;
	}
}