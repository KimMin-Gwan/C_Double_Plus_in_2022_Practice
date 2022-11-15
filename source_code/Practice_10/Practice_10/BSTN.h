#ifndef BST_H
#define BST_H
#include "T_Entry.h"

template<typename K, typename V>
class T_BSTN
{
public:
	//---------------------------------------------------------------
	T_BSTN() : entry(), pPr(NULL), pLc(NULL), pRc(NULL) { } // default constructor
	T_BSTN(T_Entry<K, V> e) : entry(e), pPr(NULL), pLc(NULL), pRc(NULL) { } // constructor
	//---------------------------------------------------------------
	K getKey() { return entry.getKey(); } //get key
	V getValue() { return entry.getValue(); } //get element value
	T_Entry<K, V>& getEntry() { return entry; } //set element value
	void setEntry(T_Entry<K, V> e) { entry = e; } //set T_Entry
	T_BSTN<K, V>* getpPr() { return pPr; } //get parent node 
	T_BSTN<K, V>* getpLc() { return pLc; } //get left child node 
	T_BSTN<K, V>* getpRc() { return pRc; } //get right child node
	T_BSTN<K, V>** getppLc() { return &pLc; } //get address of left child
	T_BSTN<K, V>** getppRc() { return &pRc; } //get address of right child
	void setpPr(T_BSTN<K, V>* pTN) { pPr = pTN; } //set parent node
	void setpLc(T_BSTN<K, V>* pTN) { pLc = pTN; } //set left child
	void setpRc(T_BSTN<K, V>* pTN) { pRc = pTN; } //set right child
	//---------------------------------------------------------------
	T_Entry<K, V>& operator*() { return entry; } //pointer for T_Entry
private:
	T_Entry<K, V> entry; // element value
	T_BSTN<K, V>* pPr; // parent
	T_BSTN<K, V>* pLc; // left child
	T_BSTN<K, V>* pRc; // right child
};

#endif