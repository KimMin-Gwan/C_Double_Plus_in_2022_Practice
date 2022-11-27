#ifndef TRIE_NODE_H
#define TRIE_NODE_H
#include <iostream>
#include <list>
#include "MyVoca.h"

#define VALUE_INTERNAL_NODE NULL
using namespace std;
typedef list<string>STL_list;

template <typename E>
class TrieNode
{
public:
	//construct--------------------------------------------
	TrieNode() {} //default constructor
	TrieNode(char k, E v) :key(k), value(v) {prev = next = parent = child = NULL; } //constructor
	//accessor and mutator--------------------------------
	void setKey(char k) { key = k; } // key mutator 
	void setValue(E v) { value = v; } //value mutator
	void setNext(TrieNode<E>* next) { this->next = next; } //next node pointer mutator
	void setPrev(TrieNode<E>* prev) { this->prev = prev; } //prev node pointer mutator
	void setParent(TrieNode<E>* parent) { this->parent = parent; } //parent node pointer mutator
	void setChild(TrieNode<E>* child) { this->child = child; } //child node pointer mutator
	char getKey() { return key; } //key accessor
	E getValue() { return value; } //value accessor
	TrieNode<E>* getPrev() { return prev; } //prev node accessor
	TrieNode<E>* getNext() { return next; } //next node accessor
	TrieNode<E>* getParent() { return parent; } //Parent node accessor
	TrieNode<E>* getChild() { return child; } //child node accessor
	//util------------------------------------------------
	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent); //fprinting inner function

private:
	char key; //key type char
	E value; //value type undefine
	TrieNode<E>* prev; //prev node
	TrieNode<E>* next; //next node
	TrieNode<E>* parent; //parent node
	TrieNode<E>* child; //child node
};

template <typename E>
void TrieNode<E>:: _fprint(ostream& fout, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)  //check empty
	{
		fout << endl;
		return;
	}
	else 
	{
		fout << pTN->key;  //print key
		_fprint(fout, pTN->child, indent + 1); //fisrt recursive here
		if (pTN->next == NULL) //if next node did not exist, escape recursive
			return;
		for (int i = 0; i < indent; i++) 
			fout << " "; //indent
		_fprint(fout, pTN->next, indent); //second recursive here
	}
}

#endif
