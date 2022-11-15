#ifndef HEAP_PRIO_Q_H 
#define HEAP_PRIO_Q_H
#include "CompleteBinaryTree.h"
#include <mutex>
using namespace std;
template<typename K, typename V>
class HeapPrioQueue : public CompleteBinaryTree<K, V>
{
public:
	HeapPrioQueue(); //default constructor
	HeapPrioQueue(int capa, string nm);//constructor 
	~HeapPrioQueue(); //destructor
	//inline-function----------------------------------------------------
	bool isEmpty() { return size()  == 0; } //check this Que is empty
	bool isFull() { return size() == capacity; } //check this Que is Full
	int size() { return this->end; } //get size
	//interface----------------------------------------------------------
	T_Entry<K, V>* insert(T_Entry<K, V>& elem);//insert data with mutex cs_priQ
	//T_Entry<K, V>* insert(T_Entry<K, V>& elem); 
	T_Entry<K, V>* removeHeapMin(); //remove heap with mutex cs_priQ
	T_Entry<K, V>* getHeapMin(); //get heap min
	//function-----------------------------------------------------------
	void fprint(ofstream& fout);  //print in file
	void printQue(); //print in console
private:
	mutex cs_priQ; //critical section for HPQ
	int capacity;
};


template<typename K, typename V>
HeapPrioQueue<K, V>::HeapPrioQueue(int capa, string nm)
	: CompleteBinaryTree<K, V>(capa, nm), capacity(capa)
{

} //constructor 

template<typename K, typename V>
HeapPrioQueue<K, V>::~HeapPrioQueue()
{
	cout << "HeapPrioQueue destructed" << endl;
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::insert(T_Entry<K, V>& elem)
{
	int index, _parentIndex;
	T_Entry<K, V> temp;
	cs_priQ.lock();
	if(isFull())
	{
		cout << "ERROR : Queue is Full !!" << endl;
		cs_priQ.unlock();
		return NULL;
	}
	index = this->add_at_end(elem); //inserting and get the end of index

	while(index != CBT_ROOT)
	{
		_parentIndex = this->parentIndex(index); // get parent index from CBT
		if (this->t_GA[index].getKey() >= this->t_GA[_parentIndex].getKey())
			break;
		else //up-heap bubbling
		{
			temp = this->t_GA[index];
			this->t_GA[index] = this->t_GA[_parentIndex]; 
			this->t_GA[_parentIndex] = temp; 
			index = _parentIndex;
		}
	}
	cs_priQ.unlock();
	T_Entry<K, V>* pRoot = &(this->t_GA[CBT_ROOT]);
	return pRoot;
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>:: removeHeapMin()
{
	int index_p, index_c, index_rc;
	T_Entry<K, V>* pMinElem;
	T_Entry<K, V> temp, t_p, t_c;
	int HPQ_size = size();
	if (HPQ_size <= 0)
	{
		return NULL;
	}
	pMinElem = (T_Entry<K, V>*) new T_Entry<K, V>;
	*pMinElem = this->getRootElement();
	if (HPQ_size == 1) //if only one element in CBT
	{
		this->removeCBTEnd(); //just return the element
	}
	else
	{
		index_p = CBT_ROOT; //p index is root index
		this->t_GA[CBT_ROOT] = this->t_GA[this->end];
		this->end--; //decrease end index
		/* down-heap bubbling */
		while (this->hasLeftChild(index_p))
		{
			index_c = this->leftChildIndex(index_p); //check the left child
			index_rc = this->rightChildIndex(index_p); //check the right child
			if (this->hasRightChild(index_p) && (this->t_GA[index_c] > this->t_GA[index_rc])) //if has right child
				index_c = index_rc; //using right child index
			t_p = this->t_GA[index_p];
			t_c = this->t_GA[index_c];
			if (t_p > t_c)
			{
				//swap(index_u, index_c);
				temp = this->t_GA[index_p];
				this->t_GA[index_p] = this->t_GA[index_c];
				this->t_GA[index_c] = temp;
				index_p = index_c;
			}
			else
				break;
		}
	}
	return pMinElem;
}

template<typename K, typename V>
T_Entry<K, V>* HeapPrioQueue<K, V>::getHeapMin()
{
	T_Entry<K, V>* pMinElement;
	if (this->size() <= 0)
		return NULL;
	pMinElement = (T_Entry<K, V> *) new T_Entry<K, V>;
	*pMinElement = this->getRootElement(); //root element is min data
	return pMinElement;

}

template<typename K, typename V>
void HeapPrioQueue<K, V>::fprint(ofstream& fout)
{
	if (this->size() <= 0) //if empty
	{
		fout << "ERROR : Que is Empty" << endl;
		return;
	}
	else //print by CBT
		CompleteBinaryTree<K, V>::fprintCBT(fout);
}

template<typename K, typename V>
void HeapPrioQueue<K, V>::printQue()
{
	if (this->size() <= 0) //if empty
	{
		cout << "ERROR : Que is Empty" << endl;
		return;
	}
	else //print by CBT
		CompleteBinaryTree<K, V>::printCBT();
}


#endif