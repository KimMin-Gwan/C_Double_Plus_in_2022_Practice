#include "BigRand.h"

#define RANDOMIZE() srand((unsigned int)time(NULL))
#define BIG_SIZE 500
#define LINESIZE 20

int* genBigRandArray(int bigRandArraySize, int offset)
{

	int* pBigRandArray;
	int idx1, idx2;
	int temp;
	pBigRandArray = (int*)calloc(bigRandArraySize, sizeof(int));
	for (int i = 0; i < bigRandArraySize; i++)
	{
		pBigRandArray[i] = i + offset; //값을 전부다 집어넣음
	}
	for (int i = 0; i < bigRandArraySize; i++) //인덱스를 생성해서 섞어줌
	{
		idx1 = (((long)rand() << 15) | rand()) % bigRandArraySize; //15비트 밀어내서 32767보다 크게 생성
		idx2 = (((long)rand() << 15) | rand()) % bigRandArraySize;
		if (idx1 == idx2) {
			continue;
		}
		else {
			temp = pBigRandArray[idx1];
			pBigRandArray[idx1] = pBigRandArray[idx2];
			pBigRandArray[idx2] = temp;
		}
	}
	return pBigRandArray;
}


void fPrintBigRandArray(ofstream& fout, int* bigRand, int num_rands)
{
	int count = 0;
	int num_lines = 5;

	if (num_rands < BIG_SIZE)
	{
		num_lines = num_rands / LINESIZE;
	}

	for (int i = 0; i < num_lines; i++)
	{
		for (int j = 0; j < LINESIZE; j++)
		{
			if (count == num_rands)	//모두 출력했다면 정지
				break;
			fout << setw(7) << bigRand[count];
			count++;
		}
		fout << endl;
	}

	if (num_rands >= BIG_SIZE)
	{
		fout << ". . . . . . . ." << endl;
		count = num_rands - (LINESIZE * num_lines);

		for (int i = 0; i < num_lines; i++)
		{
			for (int j = 0; j < LINESIZE; j++)
			{
				fout << setw(7) << bigRand[count];	//출력
				count++;
			}
			fout << endl;
		}
		fout << endl;
	}
}