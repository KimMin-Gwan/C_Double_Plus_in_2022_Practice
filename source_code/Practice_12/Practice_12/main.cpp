/**
*파일명 : "Practice_12"
*프로그램의 목적 및 기본 기능: 
*	  이 프로그램은 Trie 자료구조를 이용하여 영단어 검색 사전의 동작을 
*	  수행한다. 검색 기능을 console에서 지원한다.
*프로그램 작성자 : 김민관(2022년 11월 27일)
*최종 Update : Version 1.0, 2022년 11월 27일(김민관)
*============================================================================
*프로그램 수정/보완 이력
*============================================================================
*/

#include <iostream>
#include <fstream>
#include <list>
#include <string>
#include "MyVoca.h"
#include "MyVocaList.h"
#include "Trie.h"
#include "TrieNode.h"

using namespace std;

#define MAX_WORD_LENGTH 100
#define NUM_TEST_VOCAS 7

//void test_simple_trie(ostream& fout);
//void test_trie_myVoca(ostream& fout);

int main(void)
{
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening output file" << endl; exit;
	}

	Trie<MyVoca*> trie_myVoca("Trie_MyVoca");
	TrieNode<MyVoca*>* pTN;
	MyVoca* pVoca;
	int word_count;
	string keyStr;
	char keyWord[MAX_WORD_LENGTH];
	List_pVoca predictVocas;
	List_pVoca_Iter itr;

	MyVoca testVocas[NUM_TEST_VOCAS] =
	{
		MyVoca("xyz", NOUN, { "" }, { "" }),
		MyVoca("ABCD", NOUN, { "" }, { "" }),
		MyVoca("ABC", NOUN, { "" }, { "" }),
		MyVoca("AB", NOUN, { "" }, { "" }),
		MyVoca("A", NOUN, { "" }, { "" }),
		MyVoca("xy", NOUN, { "" }, { "" }),
		MyVoca("x", NOUN, { "" }, { "" })
	};
	fout << "Testing basic operations of trie inserting ..... " << endl;
	for (int i = 0; i < NUM_TEST_VOCAS; i++)
		trie_myVoca.insert(testVocas[i].getKeyWord(), &testVocas[i]);
	trie_myVoca.fprintTrie(fout);

	fout << endl << "Testing Trie Destroy..." << endl;
	word_count = 0;
	pVoca = &myToeicVocaList[0];

	while (pVoca->getKeyWord() != "")
	{
		keyStr = pVoca->getKeyWord();
		trie_myVoca.insert(keyStr, pVoca);
		pVoca++;
	}
	fout << "Total " << trie_myVoca.size() << " words in trie_myVoca .." << endl;
	trie_myVoca.fprintTrie(fout);

	while (1)
	{
		cout << endl << "Input any prefix to search in tire (. to finish) : ";
		cin >> keyStr;
		if (keyStr == string("."))
			break;
		predictVocas.clear();
		trie_myVoca.findPrefixMatch(keyStr, predictVocas);
		cout << "list of predictive words with prefix (" << keyStr << "):" << endl;
		itr = predictVocas.begin();
		for (int i = 0; i < predictVocas.size(); i++)
		{
			pVoca = *itr;
			cout << *pVoca << endl;
			++itr;
		}
	} //end of while
	cout << endl << "Ereasing trie myVoca . . . " << endl;
	fout << endl << "Ereasing trie myVoca . . . " << endl;
	trie_myVoca.eraseTrie();

	fout.close();
	return 0;
}

