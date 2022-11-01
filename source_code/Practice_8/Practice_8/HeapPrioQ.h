#ifndef HEAP_PRIO_Q_H 
#define HEAP_PRIO_Q_H
#include "CompleteBinaryTree.h"
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
	int insert(T_Entry<K, V>& elem); //insert data
	T_Entry<K, V>* removeHeapMin(); //remove heap
	T_Entry<K, V>* getHeapMin(); //get heap min
	//function-----------------------------------------------------------
	void fprint(ofstream& fout);  //print in file
private:
	int capacity;
};


template<typename K, typename V>
HeapPrioQueue<K, V>::HeapPrioQueue(int capa, string nm)
	: CompleteBinaryTree(capa,nm), capacity(capa)
{

} //constructor 

template<typename K, typename V>
int HeapPrioQueue<K, V>::insert(T_Entry<K, V>& elem)
{
	int index, _parentIndex;
	T_Entry<K, V> temp;
	
	if(isFull())
	{
		cout << this->getValue() << "is Full !!" << endl;
		return size();
	}
	index = this->add_at_end(elem); //inserting and get the end of index

	while(index != CBT_ROOT)
	{
		_parentIndex = this->parentIndex(index); // get parent index from CBT
		if (tArray.getKey() >= tArray .getKey())
			break;
		else //up-heap bubbling
		{
			temp = tArray[index];
			tArray[index] = tArray[_parentIndex]; 
			tArray[_parentIndex] = temp; 
			index = _parentIndex;
		}
	}
	return size();
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
	*pMinElem = this->getRootElemen();
	if (HPQ_size == 1)
	{
		this->removeCBTEnd();
	}
	else
	{
		index_p = CBT_ROOT;
		this->t_GA[CBT_ROOT] = this->t_GA[end];
		this->end--;
		/* down-heap bubbling */
		while (this->hasLeftChild(index_p))
		{
			index_c = this->leftChildIndex(index_p);
			index_rc = this->rightChildIndex(index_p);
			if (this->hasRightChild(index_p) && (this->t_GA[index_c] > this->t_GA[index_rc]))
				index_c = index_rc;
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
		} // end while
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
		CompleteBinaryTree::printCBT(fout);
}

#endif
