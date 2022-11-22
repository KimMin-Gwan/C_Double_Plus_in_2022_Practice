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

template <typename K, typename V>
class HashMap 
{
public:
	typedef std::list<Entry> Bucket; // a bucket of entries
	typedef std::vector<Bucket> BktArray; // a bucket array
	typedef typename BktArray::iterator BItor; // bucket iterator
	typedef typename Bucket::iterator EItor; // entry iterator
	typedef Entry<const K, V> Entry; // a (key,value) pair
	class Iterator;
public:
	HashMap(string name, int capacity = 101); // constructor
	int size() const; // number of entries
	string getName() { return name; }
	bool empty() const; // is the map empty?
	Iterator find(const K& k); // find entry with key k
	Iterator insert(const K& k, const V& v); // insert/replace (k,v)
	void erase(const K& k); // remove entry with key k
	void erase(const Iterator& p); // erase entry at p
	Iterator begin(); // iterator to first entry
	Iterator end(); // iterator to end entry
	void fprintBucket(ostream& fout, BItor bkt);
	void fprintBucketSizes(ostream& fout);
protected:
	// HashMap utilities here
	Iterator _find(const K& k); // find utility
	Iterator _insert(const Iterator& p, const Entry& e); // insert utility
	void _erase(const Iterator& p); // remove utility
	static void _next(Iterator& p) // bucket's next entry
	{
		++p.ent;
	}
	static bool _endOfBkt(const Iterator& p) // end of bucket?
	{
		return p.ent == p.bkt->end();
	}
private:
	int num_entry; // number of entries
	BktArray B; // bucket array
	string name;

public: 
	// Iterator class declaration
	class Iterator { // an iterator (& position)
	protected:
		EItor ent; // which entry
		BItor bkt; // which bucket
		const BktArray* ba; // which bucket array
	public:
		Iterator() {} // default constructor
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
			: ent(q), bkt(b), ba(&a) { }
		//Entry& operator*(); // get entry
		V getValue() { Entry& e = *ent; return e.value(); }
		typename HashMap<K, V>::Entry& operator*() const;
		bool operator==(const Iterator& p) const; // are iterators equal?
		bool operator!=(const Iterator& p) const; // are iterators different ?
		Iterator& operator++(); // advance to next entry
		Iterator& advanceEItor()
		{
			++ent;
			return *this;
		}
		friend class HashMap; // give HashMap access
	};
};

template <typename K, typename V> // constructor
HashMap<K, V>::HashMap(string name, int capacity) : num_entry(0), B(capacity) { this->name = name; }

template <typename K, typename V> // iterator to front
typename HashMap<K, V>::Iterator HashMap<K, V>::begin()
{
	if (empty()) return end(); // emtpty - return end
	BItor bkt = B.begin(); // else search for an entry
	while (bkt->empty()) ++bkt; // find nonempty bucket
	return Iterator(B, bkt, bkt->begin()); // return first of bucket
}
template <typename K, typename V> // iterator to end
typename HashMap<K, V>::Iterator HashMap<K, V>::end()
{
	return Iterator(B, B.end());
}

template <typename K, typename V>
typename HashMap<K, V>::Entry& HashMap<K, V>::Iterator::operator*() const
{
	return *ent;
}

/*
template <typename K, typename V> // get entry
typename HashMap<K, V>::Entry& HashMap<K, V>::Iterator::operator*() const
{
	return *ent;
}
*/

template <typename K, typename V> // are iterators equal?
bool HashMap<K, V>::Iterator::operator==(const Iterator& p) const
{
	if (ba != p.ba || bkt != p.bkt) return false; // ba or bkt differ?
	else if (bkt == ba->end()) return true; // both at the end?
	else return (ent == p.ent); // else use entry to decide
}
template <typename K, typename V> // are iterators equal?
bool HashMap<K, V>::Iterator::operator!=(const Iterator& p) const
{
	if (ba != p.ba || bkt != p.bkt) return true; // ba or bkt differ?
	else if (bkt == ba->end()) return false; // both at the end?
	else return (ent != p.ent); // else use entry to decide
}

template <typename K, typename V> // advance to next entry
typename HashMap<K, V>::Iterator& HashMap<K, V>::Iterator::operator++()
{
	++ent; // next entry in bucket
	if (_endOfBkt(*this)) { // at end of bucket?
		++bkt; // go to next bucket
		while (bkt != ba->end() && bkt->empty()) // find nonempty bucket
			++bkt;
		if (bkt == ba->end()) return *this; // end of bucket array?
		ent = bkt->begin(); // first nonempty entry
	}
	return *this; // return self
}

template <typename K, typename V> // find utility
typename HashMap<K, V>::Iterator HashMap<K, V>::_find(const K& k)
{
	CyclicShiftHashCode hash;
	int i = hash(k) % B.size(); // calculate hash value i, using CyclicShiftHashCode()
	BItor bkt = B.begin() + i; // the i-th bucket
	Iterator p(B, bkt, bkt->begin()); // start of i-th bucket
	while (!_endOfBkt(p) && (*p).key() != k) // linear search for k in the bucket
		++p.ent;
	return p; // return final position
}

template <typename K, typename V> // find key
typename HashMap<K, V>::Iterator HashMap<K, V>::find(const K& k)
{
	Iterator p = _find(k); // look for k
	if (_endOfBkt(p)) // if could not find the given key?
		return end(); // return end iterator
	else
		return p; // return its position
}
template <typename K, typename V> // insert utility
typename HashMap<K,V>::Iterator
HashMap<K, V>::_insert(const Iterator& p, const Entry& e) {
	EItor ins = p.bkt->insert(p.ent, e); // insert before p using insert() of list<Entry>
	num_entry++; // one more entry
	return Iterator(B, p.bkt, ins); // return this position
}

template <typename K, typename V> // insert/replace (v,k)
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

template <typename K, typename V> // remove utility
void HashMap<K, V>::_erase(const Iterator& p) 
{
	p.bkt->erase(p.ent); // remove entry from bucket
	num_entry--; // one fewer entry
}

template <typename K, typename V> // remove entry at p
void HashMap<K,V>::erase(const Iterator& p)
{ _erase(p); }

template <typename K, typename V> // remove entry with key k
void HashMap<K, V>::erase(const K& k) 
{
	Iterator p = _find(k); // find k
	if (_endOfBkt(p)) // not found?
		cout << "Erase of nonesistent" << endl;
		//throw NonexistentElement("Erase of nonexistent"); // ...error
	_erase(p); // remove it
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


#endif