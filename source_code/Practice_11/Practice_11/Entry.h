#ifndef ENTRY_H
#define ENTRY_H
#include <iostream>

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
	Entry(K key, V value) { _key = key; _value = value; }
	Entry() { } // default constructor
	~Entry() {}
	void setKey(const K& key) { _key = key; }
	void setValue(const V& value) { _value = value; }
	K getKey() const { return _key; }
	V getValue() const { return _value; }
	bool operator>(const Entry<K, V>& right) const { return (_key > right.getKey()); }
	bool operator>=(const Entry<K, V>& right) const { return (_key >= right.getKey()); }
	bool operator<(const Entry<K, V>& right) const { return (_key < right.getKey()); }
	bool operator<=(const Entry<K, V>& right) const { return (_key <= right.getKey()); }
	bool operator==(const Entry<K, V>& right) const { return ((_key == right.getKey()) && (_value == right.getValue())); }
	Entry<K, V>& operator=(Entry<K, V>& right);
	void fprint(ostream fout);
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