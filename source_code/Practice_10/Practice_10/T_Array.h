
#ifndef T_ARRAY_H
#define T_ARRAY_H
#include <iostream>
#include <iomanip>
using namespace std;
enum SortingOrder{INCREASING = 0, DECREASING = 1};

template<typename T>
class T_Array
{
public:
	T_Array(); //default constructer
	T_Array(int capacity, string name); //constructor
	~T_Array(); //desturctor
	//inline_function ------------------------------------------------
	int Size() { return num_elements; } //access to num_element
	string getName() { return name; } //access to Name member
	bool empty() { return num_elements == 0; } //if num_elements is zero, return true
	void insertBack(T element);
	//util_function---------------------------------------------------
	void reserve(int newCapacity); //reserve memory
	//void insert(int i, T element);   //inserting element in T_arry
	void print(int elements_per_line); //printing
	bool isValidIndex(int index);  //check the index is valid
	T& operator [](int index) { return t_array[index]; } //array operator overloading
private:
	T* t_array; //array
	int num_elements; //size of the array
	int capacity; //max size
	string name;
};

template<typename T>
T_Array<T>::T_Array()
{
	this->t_array = NULL; //poiting Null to init
	this->num_elements = 0; //zero elements
	this->capacity = 0; //zero capacity
	this->name = "ananymous"; //anaymous
}

template<typename T>
T_Array<T>::T_Array(int capacity, string name)
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

template<typename T>
T_Array<T>::~T_Array()
{
	if (t_array != NULL) //free memory
		delete[] t_array;
}

template<typename T>
void T_Array<T>::insertBack(T element)
{
	if (this->num_elements >= this->capacity)
	{
		int newCapacity;
		newCapacity = ((2 * this->capacity) > 1) ? 2 * capacity : 1;
		reserve(newCapacity);
	}
	if (isValidIndex(this->num_elements))
	{
		this->t_array[num_elements] = element;
		this->num_elements++;
	}
}

template<typename T>
void T_Array<T>::reserve(int newCapacity)
{
	if (this->capacity >= newCapacity) //if don't need to reserve
		return;
	T* t_newGA = (T*) new T[newCapacity]; // allocate new memory
	if (t_newGA == NULL) //error print in console
	{
		cout << "ERROR : No More Memory" << endl;
		exit(0);
	}
	cout << this->getName() << "expands capacity to " << setw(3) << newCapacity << endl;
	for (int i = 0; i < this->num_elements; i++)
		t_newGA[i] = t_array[i]; //assign each index data

	delete[] this->t_array; //free origin memory
	this->t_array = t_newGA; //give new array
	this->capacity = newCapacity;
}


/*
template<typename T>
void T_Array<T>::insert(int i, T element) 
{
	if (this->num_elements >= this->capacity) //check the capcity is full
	{
		int newCapacity;
		newCapacity = ((2 * this->capacity) > 1) ? 2 * capacity : 1;
		reserve(newCapacity);
	}
	if (isValidIndex(i))
	{
		//for (int j = num_elements - 1; j >= i; j--)
		//	t_array[j + 1] = t_array[j]; //shift up the position
		t_array[i] = element;
		this->num_elements++; //addition
	}
}
*/
template<typename T>
void T_Array<T>::print(int elements_per_line)
{
	int count = 0;
	while (count < this-> num_elements) //until num_element
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

template<typename T>
bool T_Array<T>::isValidIndex(int index)
{
	//int check_elements = this-> num_elements + 1;
	if ((index < 0) || (index >= capacity))
		return false;
	else
		return true;
}

#endif
