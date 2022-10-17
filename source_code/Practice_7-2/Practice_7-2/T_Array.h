#ifndef T_ARRAY_H
#define T_ARRAY_H
#include <iostream>
#include <iomanip>
#include "Student.h"
using namespace std;
enum SortingOrder{INCREASING = 0, DECREASING = 1};

template<typename T, typename K>
class T_Array
{
public:
	T_Array(); //default constructer
	T_Array(int capacity, string name); //constructor
	~T_Array(); //desturctor
	//inline_function ------------------------------------------------
	int getSize() { return num_elements; } //access to num_element
	string getName() { return name; } //access to Name member
	bool empty() { return num_elements == 0; } //if num_elements is zero, return true
	//util_function---------------------------------------------------
	void insert(int i, T element);   //inserting element in T_arry
	int sequential_search(K search_key); //search and return the index, if didn't find, return -1
	int binary_search(K search_key); //search and return the index 
	void selection_sort(string keyName, SortingOrder sortOrder); //sorting algorithm
	void merge_sort(string keyName, SortingOrder sortOrder);    //sorting algorithm
	void print(int elements_per_line); //printing
	bool isValidIndex(int index);  //check the index is valid
	T& operator [](int index) { return t_array[index]; } //array operator overloading
private:
	void _mergeSort(T* array, T* tmp_array, int left, int right, string keyName, SortingOrder sortOrder);
	T* t_array; //array
	int num_elements; //size of the array
	int capacity; //max size
	string name;
};

template<typename T, typename K>
T_Array<T,K>::T_Array()
{
	this->t_array = NULL; //poiting Null to init
	this->num_elements = 0; //zero elements
	this->capacity = 0; //zero capacity
	this->name = "ananymous"; //anaymous
}

template<typename T, typename K>
T_Array<T,K>::T_Array(int capacity, string name)
{
	this->capacity = capacity; 
	this->t_array = (T*) new T[this->capacity]; //allocate memory
	if (this->t_array == NULL) //error print in console
	{
		cout << "ERROR : No More Memory" << endl;
		exit(0);
	}
	this->num_elements = 0; //zero to init 
	this->name = name; //set name
}

template<typename T, typename K>
T_Array<T,K>::~T_Array()
{
	if (t_array != NULL) //free memory
		delete[] t_array;
}

template<typename T, typename K>
void T_Array<T,K>::insert(int i, T element) 
{
	if (this->num_elements >= this->capacity) //check the capcity is full
	{
		cout << "ERROR : NO MORE MEMORY" << endl;
		exit(0);
	}
	if (isValidIndex(i))
	{
		for (int j = num_elements - 1; j >= i; j--)
			t_array[j + 1] = t_array[j]; //shift up the position
		t_array[i] = element;
		this->num_elements++; //addition
	}
}

template<typename T, typename K>
int T_Array<T, K>::sequential_search(K search_key)
{
	int index = 0; //searching index 
	for (int index = 0; index < num_elements; index++) //for element size
	{
		if (t_array[index] == search_key) //each index matching with key
			return index; //if find, return index
	}
	return -1; //or return -1
}

template<typename T, typename K>
int T_Array<T, K>::binary_search(K search_key)
{
	int low, mid, high; //index
	int loop = 1; // for count
	low = 0; //zero size
	high = num_elements - 1;
	while (low <= high) //loof at low is equal as high
	{
		cout << setw(2) << loop << "-th loop: current search range [" << setw(3)
			<< low << ", " << setw(3) << high << "]" << endl;

		mid = (low + high) / 2;
		if (t_array[mid] == search_key) //searching in middle of the size
			return mid; //if middle index is key, return here
		else if (t_array[mid] > search_key) //if middle data is higher than key
			high = mid - 1; //high be one less than the middle index
		else //or middle data is lower than key
			low = mid + 1;   //low be one more than the middle index
		loop++; //counting
	}
	return -1; //if could't find, return -1
}

template<typename T, typename K>
void T_Array<T, K>::selection_sort(string keyName, SortingOrder sortOrder)
{
	int maxIndex, minIndex;
	T temp; // mininume

	K minKey; //min index
	K maxKey; //max index
	K key; //temp key
	for (int i = 0; i < this->num_elements - 1; i++)
	{
		if (sortOrder == INCREASING) //check the sort Order == increase
		{
			minIndex = i; //setting 
			this->t_array[i]->getKey(keyName, &key); //get init index
			minKey = (K)key; //setting  min index (conversion key type)
			for (int j = i + 1; j < this->num_elements; j++)
			{
				this->t_array[j]->getKey(keyName, &key); //get each index data
				if ((K)key < minKey)
				{
					minIndex = j;
					minKey = (K)key; //new min index
				}
			}
			if (minIndex != i) // if smaller data exist, change them
			{
				temp = this->t_array[minIndex];
				this->t_array[minIndex] = this->t_array[i];
				this->t_array[i] = temp; //update min data
			}
		}
		else // sort order== decrease
		{
			maxIndex = i; //setting
			this->t_array[i]->getKey(keyName, &key); //get init index 
			maxKey = (K)key; //setting min index (conversion key type)
			for (int j = i + 1; j < this->num_elements; j++)
			{
				this->t_array[j]->getKey(keyName, &key); //get each index data
				if ((K)key > maxKey)
				{
					maxIndex = j;
					maxKey = (K)key; //new max index
				}
			}
			if (maxIndex != i) // if bigger data exist, change them
			{
				temp = this->t_array[maxIndex];
				this->t_array[maxIndex] = this->t_array[i];
				this->t_array[i] = temp; //update max data
			}
		}
	}
}

template<typename T, typename K>
void T_Array<T,K>::_mergeSort (T* array, T* tmp_array, int left, int right, string keyName, SortingOrder sortOrder)
{
	//T entry; //is this variable usable???
	K key_i, key_j;
	if (left >= right) //If the element in this sequence is not remain
		return;  //return
	int i, j, k, mid;
	mid = (left + right) / 2; //divide left and right to get middle

	_mergeSort(array, tmp_array, left, mid, keyName, sortOrder); //recursive left part
	_mergeSort(array, tmp_array, mid + 1, right, keyName, sortOrder); //recursive right part 

	for (i = mid; i >= left; i--) //assign array to tmp_array in left part 
		tmp_array[i] = array[i];
	
	for (j = 1; j <= right - mid; j++) //assign array to tmp_array in right part 
		tmp_array[right - j + 1] = array[j + mid];
	
	for (i = left, j = right, k = left; k <= right; k++) //sorting here
	{
		tmp_array[i]->getKey(keyName, &key_i); //get i index
		tmp_array[j]->getKey(keyName, &key_j); //get j index
		if (key_i < key_j) //compare each data and if right part is bigger, 
			array[k] = tmp_array[i++];  
		else //or
			array[k] = tmp_array[j--]; 
	}
}

template<typename T, typename K>
void T_Array<T, K>::merge_sort(string keyName, SortingOrder sortOrder)
{
	T* tmp_array = new T[num_elements];
	if (tmp_array == NULL)
	{
		cout << "Error in creation of tmp_array (size = %d) in mergeSort() !!!" << endl;
		exit;
	}
	_mergeSort(t_array, tmp_array, 0, num_elements - 1, keyName, sortOrder); //sorting algorithm
	delete[] tmp_array;
}

template<typename T, typename K>
void T_Array<T, K>::print(int elements_per_line)
{
	int count = 0;
	while (count < num_elements) //until num_element
	{
		for (int i = 0; i < elements_per_line; i++)
		{
			cout << *t_array[count] << " "; //printing
			count++;
			if (count % elements_per_line == 0) //\n
				cout << endl;
		}
	}
	cout << endl; //\n
}

template<typename T, typename K>
bool T_Array<T,K>::isValidIndex(int index)
{
	if ((index < 0) || (index >= this->num_elements))
		return true;
	else
		return false;
}

#endif