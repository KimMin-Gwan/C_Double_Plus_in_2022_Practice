#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <string>
#include "TrieNode.h"
#define MAX_STR_LEN 50

using namespace std;

typedef list<MyVoca*> List_pVoca;
typedef list<MyVoca*>::iterator List_pVoca_Iter;
enum SearchMode {FULL_MATCH, PREFIX_MATCH};

template<typename E>
class Trie
{
public:
	Trie(string name); //constructor
	int size() { return num_keys; } //return size 
	void insert(string keyStr, E value); //insert node with value
	void insertExternalTN(TrieNode<E>* pTN, string keyStr, E value); //insert extenal Trie node
	TrieNode<E>* find(string keyStr); //search function
	void findPrefixMatch(string prefix, List_Str& predictWords); //serch function with prefix match
	void deleteKeyStr(string keyStr); //delete with key(string)
	void eraseTrie(); //erase node
	void fprintTrie(ostream& fout);  //print function
protected:
	TrieNode<E>* _find(string keyStr, SearchMode sm = FULL_MATCH); //search inner function
	void _traverse(TrieNode<E>* pTN, List_pVoca& list_keywords); //traverser inner function
private:
	TrieNode<E>* _root; //root node
	int num_keys; // size
	string trie_name; //trie name
};

template<typename E>
Trie<E>::Trie(string name)
{

}

template<typename E>
void Trie<E>::insert(string keyStr, E value)
{

}

template<typename E>
void Trie<E>::insertExternalTN(TrieNode<E>* pTN, string keyStr, E value)
{

}

template<typename E>
TrieNode<E>* Trie<E>::find(string keyStr)
{

}

template<typename E>
void Trie<E>::findPrefixMatch(string prefix, List_Str& predictWords)
{

}

template<typename E>
void Trie<E>::deleteKeyStr(string keyStr)
{
	
}

template<typename E>
void Trie<E>::eraseTrie()
{

}

template<typename E>
void Trie<E>::fprintTrie(ostream& fout)
{

}

//protected--------------------
template<typename E>
TrieNode<E>* Trie<E>::_find(string keyStr, SearchMode sm = FULL_MATCH)
{

}

template<typename E>
void Trie<E>::_traverse(TrieNode<E>* pTN, List_pVoca& list_keywords)
{

}

#endif