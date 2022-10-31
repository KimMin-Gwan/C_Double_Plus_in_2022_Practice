#ifndef COMPLETE_BINARY_TREE_H 
#define COMPLETE_BINARY_TREE_H
#include "TA_Entry.h"
#include <iostream>
using namespace std;
template<typename K, typename V>
class CompleteBinaryTree : public TA_Entry<K, V>
{
public:
	CompleteBinaryTree(int capa, string nm); //constructor 
	int add_at_end(T_Entry<K, V>& elem); //adder 
	//inline-function----------------------------------------------
	T_Entry<K, V>& getEndElement() { return t_GA[end]; }  //get last element
	T_Entry<K, V>& getRootElement() { return t_GA[CBT_ROOT]; } //get root element
	int getEndIndex() { return end; } //get end index
	//function-----------------------------------------------------
	void removeCBTEnd(); //reduce the end
	void fprintCBT(ofstream& fout); //file print
	void fprintCBT_byLevel(ofstream& fout); //file print by levels
protected:
	int parentIndex(int index) { return index / 2; } //get parent index
	int leftChildIndex(int index) { return index * 2; } //get left child index
	int rightChildIndex(int index) { return (index * 2 + 1); } //get right child index
	bool hasLeftChild(int index) { return ((index * 2) <= end); } //check the left child is exist 
	bool hasRightChild(int index) { return ((index * 2 + 1) <= end); } //check the right child is exist
	void _printCBT_byLevel(ofstream& fout, int p, int level); //printing by level only in this class
	int end; //end index
};

template<typename K, typename V>
CompleteBinaryTree<K,V>::CompleteBinaryTree(int capa, string nm)
	:TA_Entry<K,V>(capa+1, nm)
{
	end = 0; //init end
}

template<typename K, typename V>
int add_at_end(T_Entry<K, V>& elem)
{
	if (end >= capacity) //if the capacity is full
	{
		cout << this->getName() << "WORRING: IS FULL NOW !!!" << endl;
		return end;
	}
	end++; //pointing the next to end
	t_arrary[end] = elem; //add next to end
	return end;
}

template<typename K, typename V>
void removeCBTEnd()
{
	end--; //reduce the end point
	num_elements--; //reduce the number of element 
}

template<typename K, typename V>
void fprintCBT(ofstream& fout)
{
	int count = 0;
	if (end = 0)
	{
		fout << this->getName() << "is Empty now" << endl;
		return;
	}
	for (int i = 1; i <= end; i++)
	{
		fout << setw(3) << t_array[i] << endl;
		count++;
	}
}

template<typename K, typename V>
void fprintCBT_byLevel(ofstream& fout)
{
	int index_child;
	if (hasRightChild(index)) //if has right child
	{
		index_child = rightChildIndex(index);  //get the right child index to print next level
		_printCBT_byLevel(fout, index_child, level + 1); //print next level
	}

	for (int i = 0; i < level; i++) //print null
		fout << "    ";
	t_array[index].fprint(fout);
	fout << endl;

	if (hasLeftChild(index)) // if has left child
	{
		index_child = leftChildIndex(index); //get the left child index to print next level 
		_printCBT_byLevel(fout, index_child, level + 1); //print next level
	}
}

template<typename K, typename V>
void _printCBT_byLevel(ofstream& fout, int p, int level)
{
	if (this->end = 0) //if capacity is ZERO
	{
		fout << "WORRING : CBT IS EMPTY!!!" << endl;
		return;
	}
	//여기 이상함
	//fout << setw(3) << t_array[p] << endl;
	_printCBT_byLevel(fout, CBT_ROOT, 0); 
}

#endif
