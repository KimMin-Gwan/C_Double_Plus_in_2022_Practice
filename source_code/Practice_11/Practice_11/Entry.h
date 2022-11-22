#ifndef ENTRY_H
#define ENTRY_H
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

template<typename K, typename V>
class Entry
{
	friend ostream& operator<<(ostream& fout, Entry<K, V>& entry)
	{
		fout << "[" << entry.getKey() << ", " << *(entry.getValue()) << "]";
		return fout;
	}
public:
	Entry(const K& k, const V& v) : _key(k), _value(v) {}; //constructor
	Entry() { } // default constructor
	~Entry() {} //destructor
	//utils---------------------------------------------------------
	void setKey(const K& key) { _key = key; } //set key
	void setValue(const V& value) { _value = value; } //set value
	K getKey() const { return _key; } //get key
	V getValue() const { return _value; } //get value
	//operator overloading------------------------------------------------
	bool operator>(const Entry<K, V>& right) const { return (_key > right.getKey()); } //compare operator overloading
	bool operator>=(const Entry<K, V>& right) const { return (_key >= right.getKey()); } //compare operator overloading
	bool operator<(const Entry<K, V>& right) const { return (_key < right.getKey()); } //compare operator overloading
	bool operator<=(const Entry<K, V>& right) const { return (_key <= right.getKey()); }//compare operator overloading
	bool operator==(const Entry<K, V>& right) const { return ((_key == right.getKey()) && (_value == right.getValue())); }//compare operator overloading
	Entry<K, V>& operator=(Entry<K, V>& right); //assign operator overloading
	void fprint(ostream fout); //print in file
private:
	K _key;
	V _value;
};

template<typename K, typename V>
Entry<K, V>& Entry<K, V>::operator=(Entry<K, V>& right)
{
	this->_key = right._key;
	this->_value = right._key;
	return *this;
}

template<typename K, typename V>
void Entry<K, V>::fprint(ostream fout)
{
	fout << "[Key: " << this->getKey() << ", " << *(this->getValue()) << "]" << endl;
}
#endif