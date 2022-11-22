/**
*파일명 : "Practice_11"
*프로그램의 목적 및 기본 기능: 
*	  이 프로그램은 HashMap을 구성하여 데이터를 Key 와 value로 구분하고
*	  Iterator를 활용하여 둘을 연결하는 구조를 테스트 해본다.
* 
*프로그램 작성자 : 김민관(2022년 11월 23일)
*최종 Update : Version 1.0, 2022년 11월 23일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*/


#include <fstream>
#include <string>
#include "HashMap.h"
//#include "HashMap.cpp"
#include "CyclicShiftHashCode.h"
#include "Entry.h"
#include "HashDict.h"
#include "MyVoca.h"
#include "MyVocaList.h"

void main()
{
	ofstream fout;
	MyVoca* pVoca, voca;
	List_Str thesaurus;
	List_Str usages;
	int word_count;
	MyVoca mv;
	string keyWord;
	HashDict<string, MyVoca*> myVocaDict("MyVocaDict");
	HashDict<string, MyVoca*>::Iterator itr;
	HashDict<string, MyVoca*>::Range range;
	Entry<string, MyVoca*> vocaEntry;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Fail to open output.txt !!" << endl;
		exit;
	}
	fout << "Inserting My Vocabularies to “ << myVocaDict.getName() << ” . . . " << endl;
	word_count = 0;
	for (int i = 0; i < NUM_MY_TOEIC_VOCA; i++)
	{
		pVoca = &myToeicVocaList[i];
		keyWord = myToeicVocaList[i].getKeyWord(); //get key word and setting
		myVocaDict.insert(keyWord, pVoca);
	}
	//cout << endl;
	fout << "Total " << myVocaDict.size() << " words in my Voca_Dictionary .." << endl;
	// check all vocabularies in the hash_dictionary
	for (itr = myVocaDict.begin(); itr != myVocaDict.end(); ++itr)
	{
		pVoca = itr.getValue();
		fout << *pVoca << endl;
	}
	fout << endl;
	//string testWord = "mean";
	string testWord = "offer";
	range = myVocaDict.findAll(testWord);
	fout << "Thesaurus of [" << testWord << "]: \n";
	for (itr = range.begin(); itr != range.end(); ++itr)
	{
		pVoca = itr.getValue();;
		fout << *pVoca << endl;
	}
	fout << endl;
	fout.close();
}