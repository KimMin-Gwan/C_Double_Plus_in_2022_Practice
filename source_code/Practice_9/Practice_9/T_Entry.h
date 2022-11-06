#ifndef T_ENTRY_H 
#define T_ENTRY_H
#include <iostream>
using namespace std;

template<typename K, typename V>
class T_Entry
{
	friend ostream& operator<<(ostream& fout, T_Entry<K, V>& entry)
	{
		fout << "[" << entry.getKey() << ", " << (entry.getValue()) << "]";
		return fout;
	}
public:
	T_Entry() { _key = 999; } // default constructor
	T_Entry(K key, V value) { _key = key; _value = value; } //constructor
	~T_Entry() {} //destructor
	//Inline_function----------------------------------------------------
	void setKey(const K& key) { _key = key; } //set key
	void setValue(const V& value) { _value = value; } // set value
	K getKey() const { return _key; } //get key
	V getValue() const { return _value; } //get value
	//overloading--------------------------------------------------------
	bool operator>(const T_Entry& right) { return (_key > right.getKey()); } //compare operator overloading
	bool operator>=(const T_Entry& right) { return (_key >= right.getKey()); } //compare operator overloading
	bool operator<(const T_Entry& right) { return (_key < right.getKey()); } //compare operator overloading
	bool operator<=(const T_Entry& right) { return (_key <= right.getKey()); } //compare operator overloading
	bool operator==(const T_Entry& right) { return ((_key == right.getKey()) && (_value == right.getValue())); } //compare operator overloading
	T_Entry& operator=(T_Entry& right); //assign operator overloading
	//function-----------------------------------------------------------
	void fprint(ostream& fout); //print in file
private:
	K _key;
	V _value;
};

template<typename K, typename V>
void T_Entry<K, V>::fprint(ostream& fout)
{
	fout << "[Key: " << this->getKey() << ", " << *(this->getValue()) << "]" << endl;
}


template<typename K, typename V>
T_Entry<K, V>& T_Entry<K, V>::operator=(T_Entry& right)
{
	this->_key = right._key;
	this->_value = right._value;
	return *this;
}
#endif