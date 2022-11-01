#ifndef TA_ENTRY_H 
#define TA_ENTRY_H
#include <iostream>
#include "T_Entry.h"
using namespace std;

enum SortingDirection { INCREASING, DECREASING };
template<typename K, typename V>
class TA_Entry
{
public:
	TA_Entry(int n, string nm); // constructor
	~TA_Entry(); // destructor
	//inline function----------------------------------------------
	int size() { return num_elements; } //get size 
	bool empty() { return num_elements == 0; } //get elements number
	string getName() { return name; } //get array name
	//interface ---------------------------------------------------
	void reserve(int newCapacity); //reserve the capacity
	void insert(int i, T_Entry<K, V> element); //insert data
	void remove(int i); //remove index
	T_Entry<K, V>& at(int i); //pointing 
	void set(int i, T_Entry<K, V>& element);
	T_Entry<K, V> getMin(int begin, int end); //get min index
	T_Entry<K, V> getMax(int begin, int end); //get max  index
	//function & tools --------------------------------------------
	void shuffle(); //suffle the array index
	int sequential_search(T_Entry<K, V> search_key); // search and return the index, if didn't find, return -1
	int binary_search(T_Entry<K, V> search_key); //search and return index
	void selection_sort(SortingDirection sd); //sorting algorithm
	void quick_sort(SortingDirection sd); //sorting algorithm
	void fprint(ofstream& fout, int elements_per_line); //printing in file
	void fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines); //printing sample
	bool isValidIndex(int i); //check the index is valid
	T_Entry<K, V>& operator[](int index) { return t_GA[index]; } //array operater
protected:
	T_Entry<K, V>* t_GA;
	int num_elements;
	int capacity;
	string name;
};


template<typename K, typename V>
void _partition(V* array, int size, int left, int right, int pivotIndex, SortingDirection sd);

template<typename K, typename V>
void _quick_sort(V* array, int size, int left, int right, SortingDirection sd);
//write source here

template<typename K, typename V>
TA_Entry<K, V>::TA_Entry(int n, string nm)
	: num_elements(n), name(nm)
{ 
	cout << "T array Entry was constucted" << endl;
	capacity = n;
	t_GA = new T_Entry<K, V>[capacity]; //init pointer
}

template<typename K, typename V>
TA_Entry<K, V>::~TA_Entry()
{
	cout << "T array destuctor was operated" << endl;
	delete t_GA;
}

template<typename K, typename V>
void TA_Entry<K, V>::reserve(int newCapacity)
{
	if (this->capacity >= newCapacity) //if don't needto reserve
		return;
	V* t_newGA = (V*) new V[newCapacity]; // allocate new memory
	if (t_newGA == NULL) //error print in console
	{
		cout << "ERROR : No More Memory" << endl;
		exit(0);
	}
	cout << this->name << "expands capacity to " << setw(3) << newCapacity << endl;
	for (int i = 0; i < this->num_elements; i++)
		t_newGA[i] = this->t_GA[i];
	delete[] this->t_GA; //free origin memory
	this->t_GA = t_newGA; //give new array
	this->capacity = newCapacity; //end of reserve
}

template<typename K, typename V>
void TA_Entry<K, V>::insert(int i, T_Entry<K, V> element)
{
	if (this->num_elements >= this->capacity) //check the capcity is full
	{
		cout << "ERROR : NO MORE MEMORY" << endl;
		exit(0);
	}
	if (this->isValidIndex(i))
	{
		for (int j = this->num_elements - 1; j >= i; j--)
			this->t_GA[j + 1] = this->t_GA[j]; //shift up the position
		this->t_GA[i] = element;
		this->num_elements++; //addition
	}
}

template<typename K, typename V>
void TA_Entry<K, V>::remove(int i)
{
	delete this->t_GA[i];
}

template<typename K, typename V>
T_Entry<K, V>& TA_Entry<K, V>:: at(int i)
{
	return this->t_GA[i];
}

template<typename K, typename V>
void TA_Entry<K, V>::set(int i, T_Entry<K, V>& element)
{
	
}

template<typename K, typename V>
T_Entry<K, V> TA_Entry<K, V>::getMin(int begin, int end)
{
	int minIndex = begin;

	for (int i = begin + 1; i < end; i++) //searching min data
	{
		if (this->t_GA[i] < this->t_GA[minIndex])
			minIndex = i; //change minIndex
	}
	return this->t_GA[minIndex]; 
}

template<typename K, typename V>
T_Entry<K, V> TA_Entry<K, V>::getMax(int begin, int end)
{
	int maxIndex = begin;

	for (int i = begin + 1; i < end; i++) //searching min data
	{
		if (this->t_GA[i] > this->t_GA[maxIndex])
			maxIndex= i; //change minIndex
	}
	return this->t_GA[maxIndex];

}

template<typename K, typename V>
void TA_Entry<K, V>::shuffle()
{

}

template<typename K, typename V>
int TA_Entry<K, V>::sequential_search(T_Entry<K, V> search_key)
{
	int index = 0; //searching index 
	for (int index = 0; index < this->num_elements; index++) //for element size
	{
		if (this->t_GA[index] == search_key) //each index matching with key
			return index; //if find, return index
	}
	return -1; //or return -1

}

template<typename K, typename V>
int TA_Entry<K, V>::binary_search(T_Entry<K, V> search_key)
{
	int low, mid, high; //index
	int loop = 1; // for count
	low = 0; //zero size
	high = this->num_elements - 1;
	while (low <= high) //loof at low is equal as high
	{
		cout << setw(2) << loop << "-th loop: current search range [" << setw(3)
			<< low << ", " << setw(3) << high << "]" << endl;

		mid = (low + high) / 2;
		if (this->t_GA[mid] == search_key) //searching in middle of the size
			return mid; //if middle index is key, return here
		else if (this->t_GA[mid] > search_key) //if middle data is higher than key
			high = mid - 1; //high be one less than the middle index
		else //or middle data is lower than key
			low = mid + 1;   //low be one more than the middle index
		loop++; //counting
	}
	return -1; //if could't find, return -1
}

template<typename K, typename V>
void TA_Entry<K, V>::selection_sort(SortingDirection sd)
{
	int maxIndex, minIndex;
	V temp;

	K compareKey;
	K key;

	for (int i = 0; i < this->num_elements - 1; i++)
	{
		if (sd == INCREASING)
		{
			minIndex = i; //setting
			//this->t_GA[i]->getKey(keyName, &key); //get init key
			this->t_GA[i]->getKey(); //get init key
			compareKey = (K)key; //setting min index
			for (int j = i + 1; j < this->num_elements; j++)
			{
				//this->t_GA[j]->getKey(keyName, &key); //get each index data
				this->t_GA[j]->getKey(); //get each index data
				if (key < compareKey)
				{
					minIndex = j; //new min index
					compareKey = (K)key; //new min data
				}
			}
			if (minIndex != i) //if smaller data exist, change them
			{
				temp = this->t_GA[minIndex];
				this->t_GA[minIndex] = this->t_GA[i];
				this->t_GA[i] = temp;
			}
		}
		else
		{
			maxIndex = i; //setting
			//this->t_GA[i]->getKye(keyName, &key); //get init key
			this->t_GA[i]->getKye(); //get init key
			compareKey = (K)key; //setting max index
			for (int j = i + 1; j < this->num_elements; j++)
			{
				//this->t_GA[j]->getKey(keyName, &key); //get each index data
				this->t_GA[j]->getKey(); //get each index data
				if (key > compareKey)
				{
					maxIndex = j; //new max index
					compareKey = (K)key; //new max data
				}
			}
			if (maxIndex != i) //if bigger data exist, change them
			{
				temp = this->t_GA[maxIndex];
				this->t_GA[maxIndex] = this->t_GA[i];
				this->t_GA[i] = temp;
			}
		}
	}
}

template<typename K, typename V>
void _partition(V* array, int size, int left, int right, int pivotIndex, SortingDirection sd)
{
	V pivotValue, temp; //pivot value
	int newPI; //new pivot index

	pivotValue = array[pivotIndex];
	array[pivotIndex] = array[right];
	array[right] = pivotValue; //move pivot value to right

	newPI = left; //searching start position

	for (int i = left; i <= (right - 1); i++)
	{
		if (sd == INCREASING)
		{
			if (array[i] <= pivotValue)
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp; //exchange the index
				newPI = newPI + 1;
			}
		}
		else //sorting in decreasing (non_increasing) order
		{
			if (array[i] > pivotValue)
			{
				temp = array[i];
				array[i] = array[newPI];
				array[newPI] = temp; //exchange the index
				newPI = newPI + 1;
			}
		}
		temp = array[newPI];
		array[newPI] = array[right];
		array[right] = temp;
		return newPI;
	}
}

template<typename K, typename V>
void _quick_sort(K* array, int size, int left, int right, SortingDirection sd)
{
	int pI, newPI; //pivot index
	if (left >= right)
	{
		return;
	}
	else
	{
		pI = (left + right) / 2; //finding middle
	}

	newPI = _partition(array, size, left, right, pI, sd); //partition and sorting

	if (left < (newPI - 1)) //left side
	{
		_quick_sort(array, size, left, newPI - 1, sd);
	}
	if ((newPI + 1) < right) //right side
	{
		_quick_sort(array, size, newPI + 1, right, sd);
	}
	//end of this recursive
}

template<typename K, typename V>
void TA_Entry<K, V>::quick_sort(SortingDirection sd)
{
	_quick_sort(this->t_GA, this->num_elements, 0, this->num_elements - 1, sd); //start of sorting
}


template<typename K, typename V>
void TA_Entry<K, V>::fprint(ofstream& fout, int elements_per_line)
{

}

template<typename K, typename V>
void TA_Entry<K, V>::fprintSample(ofstream& fout, int elements_per_line, int num_sample_lines)
{

}

template<typename K, typename V>
bool TA_Entry<K, V>::isValidIndex(int i)
{
	if (i < 0 || this->index >= this->capacity)
		return false;
	else
		return true;
}

#endif
