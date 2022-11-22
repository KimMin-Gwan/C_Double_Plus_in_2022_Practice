#ifndef HASH_DICT_H
#define HASH_DICT_H
#include <iostream>
#include "HashMap.h"

using namespace std;

template <typename K, typename V>
class HashDict : public HashMap<K, V> 
{
public:
	typedef typename HashMap<K, V>::Iterator Iterator;
	typedef typename HashMap<K, V>::Entry Entry;

	class Range { 
	public:
		Range() {} // default constructor
		Range(const Iterator& b, const Iterator& e) //constructor
			: _begin(b), _end(e) { }
		//----------------------------------------------
		Iterator& begin() { return _begin; } // get begin
		Iterator& end() { return _end; } // get end
	private:
		Iterator _begin; // front 
		Iterator _end; // end 
	};
public:
	HashDict(string name, int capacity = DEFAULT_HASH_TABLE_SIZE); // constructor
	Range findAll(const K& k); // find all entry
	Iterator insert(const K& k, const V& v); //insert key and value 
};

template <typename K, typename V>
HashDict<K, V>::HashDict(string name, int capacity)
	:HashMap<K, V>(name, capacity)
{ }

template <typename K, typename V>
typename HashDict<K, V>::Range
HashDict<K, V>::findAll(const K& k)
{
	Iterator b = this->_find(k); // look up k
	Iterator p = b;
	while (p != this->end() && (*p).getKey() == k)
		++p;
	return Range(b, p); // return range of positions
}

template <typename K, typename V>
typename HashDict<K, V>::Iterator
HashDict<K, V>::insert(const K& k, const V& v)
{
	Iterator p = this->_find(k); // find key
	Iterator q = this->_insert(p, Entry(k, v)); // insert it here
	return q; // return its position
}

#endif
