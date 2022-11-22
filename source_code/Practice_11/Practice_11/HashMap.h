#ifndef HASHMAP_H
#define HASHMAP_H

#include <string>
#include <list>
#include <vector>
#include <iomanip>
#include "Entry.h"
#include "MyVoca.h"
#include "CyclicShiftHashCode.h"
#define DEFAULT_HASH_TABLE_SIZE 101
//#include "Exceptions.h"

using namespace std;

template <typename K, typename V>
class HashMap
{
public:
	typedef Entry<const K, V> Entry; //Entry(key, value)
	typedef list<Entry> Bucket; // entry bucket 
	typedef vector<Bucket> BktArray; // bucket array
	typedef typename BktArray::iterator BItor; // bucket iterator
	typedef typename Bucket::iterator EItor; // entry iterator
	class Iterator;
public:
	HashMap(string name, int capacity = 101); //constructor
	//utils-------------------------------------------------------
	int size() const { return num_entry; } //size of hashmap 
	string getName() { return this->name; } //get name
	bool empty() const { return (size() == 0); } // if size is 0, return true
	//function---------------------------------------------------
	Iterator find(const K& k); // find Key
	Iterator insert(const K& k, const V& v); // insert 
	void erase(const K& k); // remove entry with key k
	void erase(const Iterator& p); // erase entry at p
	Iterator begin(); // iterator to first entry
	Iterator end(); // iterator to end entry
	//print------------------------------------------------------
	void fprintBucket(ostream& fout, BItor bkt);
	void fprintBucketSizes(ostream& fout);
protected:
	//utils---------------------------------------------------------
	Iterator _find(const K& k); // find
	Iterator _insert(const Iterator& p, const Entry& e); // insert
	void _erase(const Iterator& p); // remove
	static void _next(Iterator& p) { ++p.ent; } //next bucket
	static bool _endOfBkt(const Iterator& p) {return p.ent == p.bkt->end();} //end of bucket
private:
	int num_entry; // size of entry 
	BktArray B; // bucket array
	string name; //hash map name

public: 
	class Iterator { 
	public:
		Iterator() {} // default constructor
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
			: ent(q), bkt(b), ba(&a) { }
		//V getValue() { *this->ent->getValue(); }
		V getValue() { Entry& e = *ent; return e.getValue(); }

		//iterator utils-----------------------------------------------------
		Entry& operator*() const { return *ent; }
		//typename HashMap<K, V>::Entry& operator*() const;
		bool operator==(const Iterator& p) const; //equal comparative operator
		bool operator!=(const Iterator& p) const; //unequal comparative operator
		Iterator& operator++(); // advance
		Iterator& advanceEItor() { ++ent; return *this; } //advanced pointer
		friend class HashMap;
	protected:
		EItor ent; //entry
		BItor bkt; //bucket
		const BktArray* ba; //bucket array
	};
};

template <typename K, typename V> // constructor
HashMap<K, V>::HashMap(string name, int capacity)
	: num_entry(0), B(capacity) 
{ this->name = name; }

template <typename K, typename V> // iterator to front
typename HashMap<K, V>::Iterator 
HashMap<K, V>::begin()
{
	if (empty())  //check the size
		return end();  
	BItor bkt = this->B.begin(); //search for entry
	while (bkt->empty()) //check each element
		++bkt; 
	return Iterator(this->B, bkt, bkt->begin());
}

template <typename K, typename V> // iterator to end
typename HashMap<K, V>::Iterator 
HashMap<K, V>::end()
{
	return Iterator(this->B, this->B.end());
}

template <typename K, typename V> // find key
typename HashMap<K, V>::Iterator
HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k); //find key
	if (_endOfBkt(p)) //if not found
		return end(); // return end 
	else
		return p; // return position
}

template <typename K, typename V>
typename HashMap<K,V>::Iterator
HashMap<K, V>::insert(const K& k, const V& v)
{
	Iterator p = _find(k); // search for k
	if (_endOfBkt(p)) { // k not found?
		return _insert(p, Entry(k, v)); // insert at end of bucket
	}
	else
	{ // found it?
		p.ent->setValue(v); // replace value with v
		return p; // return this position
	}
}


template <typename K, typename V>
void HashMap<K,V>::erase(const Iterator& p)
{
	_erase(p); 
}

template <typename K, typename V> 
void HashMap<K, V>::erase(const K& k) 
{
	Iterator p = _find(k); // find key
	if (_endOfBkt(p)) //if not found
		return;
	_erase(p); // remove it
}

//potected memeber---------------------------------------------------------------

template <typename K, typename V> // find utility
typename HashMap<K, V>::Iterator HashMap<K, V>::_find(const K& k)
{
	CyclicShiftHashCode hash;
	int i = hash(k) % B.size(); // calculate hash value i, using CyclicShiftHashCode()
	BItor bkt = B.begin() + i; // the i-th bucket
	Iterator p(B, bkt, bkt->begin()); // start of i-th bucket
	while (!_endOfBkt(p) && (*p).getKey() != k) // linear search for k in the bucket
		++p.ent;
	return p; // return final position
}

template <typename K, typename V> 
typename HashMap<K,V>::Iterator
HashMap<K, V>::_insert(const Iterator& p, const Entry& e) {
	EItor ins = p.bkt->insert(p.ent, e); // insert before p using insert() of list<Entry>
	num_entry++; // one more entry
	return Iterator(B, p.bkt, ins); // return this position
}

template <typename K, typename V>
void HashMap<K, V>::_erase(const Iterator& p) 
{
	p.bkt->erase(p.ent); 
	num_entry--; 
}

template <typename K, typename V>
void HashMap<K, V>::fprintBucket(ostream& fout, BItor bkt) 
{
	Iterator p(B, bkt, bkt->begin());
	MyVoca* pVoca;
	while (p.ent != bkt->end()) {
		pVoca = p.getValue();
		fout << *pVoca << endl;
		++p.ent;
	}
}

template <typename K, typename V>
void HashMap<K, V>::fprintBucketSizes(ostream& fout) 
{
	int bkt_size;
	int max_ent, min_ent, total;
	int num_bkts, max_bkt = 0;
	double avg = 0.0;
	max_ent = min_ent = B[0].size();
	total = 0;
	num_bkts = B.size();
	for (int bkt = 0; bkt < num_bkts; bkt++)
	{
		bkt_size = B[bkt].size();
		fout << "Bucket[" << setw(3) << bkt << "] : " << bkt_size << " entries" << endl;
		if (bkt_size > max_ent)
		{
			max_ent = bkt_size;
			max_bkt = bkt;
		}
		if (bkt_size < min_ent)
			min_ent = bkt_size;
		total += bkt_size;
	}
	avg = total / num_bkts;
	fout.precision(2);
	fout << "\nMax_ent(" << setw(2) << max_ent << "), min_ent(" << setw(2) << min_ent
		<< "), avg (" << setw(5) << avg << ")" << endl;
	fout << "Bucket with maximum (" << max_ent << ") entries : " << endl;
	BItor bkt = B.begin() + max_bkt;// the ith bucket
	fprintBucket(fout, bkt);
}


template <typename K, typename V>
bool HashMap<K, V>::Iterator::operator==(const Iterator& p) const
{
	if (ba != p.ba || bkt != p.bkt) //compare
		return false; 
	else if (bkt == ba->end())
		return true; 
	else 
		return (ent == p.ent); 
}

template <typename K, typename V>
bool HashMap<K, V>::Iterator::operator!=(const Iterator& p) const
{
	if (ba != p.ba || bkt != p.bkt) //compare
		return true; 
	else if (bkt == ba->end()) 
		return false;
	else
		return (ent != p.ent);
}

template <typename K, typename V> 
typename HashMap<K, V>::Iterator& HashMap<K, V>::Iterator::operator++()
{
	++ent; 
	if (_endOfBkt(*this))
	{
		++bkt; 
		while (bkt != ba->end() && bkt->empty())  //valid index
			++bkt;
		if (bkt == ba->end())
			return *this; 
		ent = bkt->begin(); 
	}
	return *this; 
}

#endif
