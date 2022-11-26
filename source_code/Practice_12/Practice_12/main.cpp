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

void test_simple_trie(ostream& fout);
void test_trie_myVoca(ostream& fout);

int main(void)
{
	ofstream fout;
	fout.open("output.txt");
	if (fout.fail())
	{
		cout << "Error in opening output file" << endl; exit;
	}

	Trie<MyVoca*> trie_myVoca("Trie_MyVoca");

}