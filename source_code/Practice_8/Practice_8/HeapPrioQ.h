#ifndef HEAP_PRIO_Q_H 
#define HEAP_PRIO_Q_H
#include "CompleteBinaryTree.h"
using namespace std;
template<typename K, typename V>
class HeapPrioQueue : public CompleteBinaryTree<K, V>
{
public:
	HeapPrioQueue() //default constructor
	HeapPrioQueue(int capa, string nm) : CompleteBinaryTree(capa,nm) {} //constructor 
	~HeapPrioQueue(); //destructor
	//inline-function----------------------------------------------------
	bool isEmpty() { return size()  == 0; } //check this Que is empty
	bool isFull() { return size() == capacity; } //check this Que is Full
	int size() { return end; } //get size
	//interface----------------------------------------------------------
	int insert(T_Entry<K, V>& elem); //insert data
	T_Entry<K, V>* removeHeapMin(); //remove heap
	T_Entry<K, V>* getHeapMin(); //get heap min
	//function-----------------------------------------------------------
	void fprint(ofstream& fout);  //print in file
private:
};

template<typename K, typename V>
int insert(T_Entry<K, V>& elem)
{
	

}

template<typename K, typename V>
T_Entry<K, V>* removeHeapMin()
{

}

template<typename K, typename V>
T_Entry<K, V>* getHeapMin()
{

}

template<typename K, typename V>
void fprint(ofstream& fout)
{

}

#endif
