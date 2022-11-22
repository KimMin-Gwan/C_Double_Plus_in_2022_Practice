#ifndef HASH_DICT_H
#define HASH_DICT_H
#include <iostream>
using namespace std;

template <typename K, typename V>
class HashDict : public HashMap<K, V> 
{
public:
	typedef typename HashMap<K, V>::Iterator Iterator;
	typedef typename HashMap<K, V>::Entry Entry;

	class Range { 
	private:
		Iterator _begin; // front of range
		Iterator _end; // end of range
	public:
		Range() {} // default constructor
		Range(const Iterator& b, const Iterator& e) // constructor
			: _begin(b), _end(e) { }
		Iterator& begin() { return _begin; } // get beginning
		Iterator& end() { return _end; } // get end
	};
public:
	HashDict(string name, int capacity = DEFAULT_HASH_TABLE_SIZE); // constructor
	Range findAll(const K& k); // find all entries with k
	Iterator insert(const K& k, const V& v); // insert pair (k,v)
};

template <typename K, typename V>
HashDict<K, V>::HashDict(string name, int capacity)
{

}

template <typename K, typename V>
typename HashDict<K, V>::Range
HashDict<K, V>::findAll(const K& k)
{
	Iterator b = _find(k); // look up k
	Iterator p = b;
	while (p != this->end() && (*p).key() == k)
	{ // find next entry with different key or end of bucket array
		++p;
	}
	return Range(b, p); // return range of positions
}

template <typename K, typename V>
typename HashDict<K, V>::Iterator
HashDict<K, V>::insert(const K& k, const V& v)
{
	Iterator p = _find(k); // find key
	Iterator q = _insert(p, Entry(k, v)); // insert it here
	return q; // return its position
}

#endif
