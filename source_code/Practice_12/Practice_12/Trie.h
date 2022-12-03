#ifndef TRIE_H
#define TRIE_H
#include <iostream>
#include <string>
#include "TrieNode.h"
#define MAX_STR_LEN 50

using namespace std;

typedef list<MyVoca*> List_pVoca;
typedef list<MyVoca*>::iterator List_pVoca_Iter;
enum SearchMode {FULL_MATCH, PREFIX_MATCH};

template<typename E>
class Trie
{
public:
	Trie(string name); //constructor
	int size() { return num_keys; } //return size 
	void insert(string keyStr, E value); //insert node with value
	void insertExternalTN(TrieNode<E>* pTN, string keyStr, E value); //insert extenal Trie node
	TrieNode<E>* find(string keyStr); //search function
	void findPrefixMatch(string prefix, List_pVoca& predictWords); //serch function with prefix match
	void deleteKeyStr(string keyStr); //delete with key(string)
	void eraseTrie(); //erase node
	void fprintTrie(ostream& fout);  //print function
protected:
	TrieNode<E>* _find(string keyStr, SearchMode sm = FULL_MATCH); //search inner function
	void _traverse(TrieNode<E>* pTN, List_pVoca& list_keywords); //traverser inner function
	void _fprint(ostream& fout, TrieNode<E>* pTN, int indent);
private:
	TrieNode<E>* _root; //root node
	int num_keys; // size
	string trie_name; //trie name
};

template<typename E>
Trie<E>::Trie(string name)
{
	//init root point NULL
	this->trie_name = name;
	this->_root = new TrieNode<E>('\0', NULL);
	this->_root->setKey('\0');
	this->_root->setPrev(NULL);
	this->_root->setNext(NULL);
	this->_root->setParent(NULL);
	this->_root->setChild(NULL);
	this->num_keys = 0;
}

template<typename E>
void Trie<E>::insert(string keyStr, E value)
{
	TrieNode<E>* pTN = NULL, * pTN_New = NULL;
	char* keyPtr = (char*)keyStr.c_str();

	if (keyPtr == NULL) //check the key is empty
		return;

	if (_find(keyStr, FULL_MATCH) != NULL) //if keyStri is found same key
	{
		cout << "The given key string is already existing : " << keyStr << endl;
		return; //just return
	}
	//positioning-------------------------------------------------
	pTN = this->_root; // pTN == point tree root node
	while ((pTN != NULL) && (*keyPtr != '\0')) //last node or keyPtr is indent (visit target node)
	{
		if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0')) //no more next node
			break;

		while ((pTN->getKey() < *keyPtr) && (pTN->getNext() != NULL)) //find last next node in same depth
			pTN = pTN->getNext(); //pTN == point tree next node (go next)

		while ((pTN != NULL) && (pTN->getKey() == *keyPtr) && (*keyPtr != '\0')) //if find same parent key
		{
			pTN = pTN->getChild(); //pTN == point tree child node (go down)
			keyPtr++; //increase to change the key to next key
		}

		if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0')) //if reach the target node
			break;
	}

	//inserting----------------------------------------------------
	if ((pTN->getKey() != '\0') && (*keyPtr == '\0')) //insert value but already inserted before
	{
		/**
		* insert 'ab' to 'abc' trie
		*  root -- root->next(a)
		*              |
		*              |
		*	       pTN->parent(b)
		*              |
		*              |
		*            pTN_New('\0')  --  pTN(c)
		*              |
		*              |
		*/


		pTN_New = new TrieNode<E>('\0', value);
		pTN_New->setParent(pTN->getParent()); //new node is insert at pTN position
		(pTN->getParent())->setChild(pTN_New); //linking
		pTN_New->setNext(pTN); //pTN_New push pTN to next
		pTN->setPrev(pTN_New); //linking
		this->num_keys++;
		return; //end of insertion
	}
	else if ((pTN->getKey() < *keyPtr) && (pTN->getNext() == NULL) && (*keyPtr != '\0')) //inserting between pTN, pTN->parent
	{
		/**
		* insert 'ant' to 'abcd' trie
		*  root -- pTN->parent(a)
		*              |       ��
		*              |         ��
		*             pTN(b)  --  pTN_New(n)
		*              |             |
		*              |             |
		*/
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setParent(pTN->getParent());
		pTN_New->setPrev(pTN); //pTN push pTN_New to next node
		pTN->setNext(pTN_New); //linking
		pTN = pTN_New; //pTN = pTN->nextNode
		keyPtr++; //next key
		while (*keyPtr != '\0')
		{
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); //new node
			pTN->setChild(pTN_New); //new node became child
			(pTN->getChild())->setParent(pTN); //linking
			pTN = pTN->getChild(); //go down
			keyPtr++; //next key
		}
		if (*keyPtr == '\0') // if reach end of keyStr
		{
			insertExternalTN(pTN, keyStr, value); //add Null word next to last node
			this->num_keys++; //increase size
			return; //end of insertion
		}
	}
	else if ((pTN->getKey() > *keyPtr) && (*keyPtr != '\0')) 
	{
		/**
		* insert 'net' between 'quit' trie and 'abcd'
		*  root -- pTN->Prev(a) -- pTN_New(n) -- pTN(q)
		*              |             |            |
		*              |             |            |
		*           node(b)       child(e)     node(u)
		*              |             |            |
		*              |             |            |
		*/
		pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE);
		pTN_New->setNext(pTN); //pTN_New pushes pTN to next node
		pTN_New->setParent(pTN->getParent()); //linking

		if (pTN->getPrev() == NULL)  //if pTN's previous node did not exist yet
		{
			if (pTN->getParent() != NULL)  //pTN still have parent node == not a top node
				(pTN->getParent())->setChild(pTN_New); //liking with pTN_New and pTN->Parent
		}
		else  //if pTN already have previous node
			(pTN->getPrev())->setNext(pTN_New); //pTN_New's position is between pTN and pTN->Prev

		pTN_New->setPrev(pTN->getPrev()); //liking pTN->Prev with pTN_New
		pTN->setPrev(pTN_New); //linking
		pTN = pTN_New; //pTN == pTN->Prev
		keyPtr++; //next key

		while (*keyPtr != '\0') //go down and insert new node
		{ 
			pTN_New = new TrieNode<E>(*keyPtr, VALUE_INTERNAL_NODE); //new node
			pTN->setChild(pTN_New); //new node became childe
			(pTN->getChild())->setParent(pTN); //linking
			pTN = pTN->getChild(); //go down
			keyPtr++;  //next key
		}
		if (*keyPtr == '\0') //if reach end of keyStr
		{
			insertExternalTN(pTN, keyStr, value); //add Null word next to last node
			this->num_keys++; //increase size
			return; //end of insertion
		}
	}
}

template<typename E>
void Trie<E>::insertExternalTN(TrieNode<E>* pTN, string keyStr, E value)
{
	//to check the end of trie
	TrieNode<E>* pTN_New = NULL; //make node to insert 
	pTN_New = new TrieNode<E>('\0', value); 
	pTN->setChild(pTN_New); //new node will be child of this node
	(pTN->getChild())->setParent(pTN); //set new node's prarent
	//pTN_New->setParent(pTN);
	pTN_New->setValue(value); //set value
	//cout << "key (" << keyStr << ") is inserted \n";
}

template<typename E>
TrieNode<E>* Trie<E>::find(string keyStr)
{
	TrieNode<E>* pTN = NULL;

	pTN = _find(keyStr, FULL_MATCH); //call inner function
	return pTN;
}

template<typename E>
void Trie<E>::findPrefixMatch(string prefix, List_pVoca& predictWords)
{
	TrieNode<E>* pPtr = NULL;
	string keyPtr;
	TrieNode<E>* pTN = NULL;
	TrieNode<E>* found = NULL;
	keyPtr = prefix;
	if (prefix.empty())
		return;
	pTN = this->_root;
	pTN = _find(prefix, PREFIX_MATCH);
	_traverse(pTN, predictWords);
}

template<typename E>
void Trie<E>::deleteKeyStr(string keyStr)
{
	TrieNode<E>* pTN = NULL, * _root;
	TrieNode<E>* tmp = NULL;
	int trie_val;
	_root = this->_root;
	if (NULL == _root || keyStr.empty()) //if root is empty
		return;
	pTN = _find(keyStr, FULL_MATCH);
	if (pTN == NULL) {
		cout << "Key [" << keyStr << "] not found in trie" << endl;
		return;
	}
	while (1) {
		if (pTN == NULL)
			break;
		if (pTN->getPrev() && pTN->getNext()) {
			tmp = pTN; (pTN->getNext())->setPrev(pTN->getPrev()); (pTN->getPrev())->setNext(pTN->getNext());
			free(tmp);
			break;
		}
		else if (pTN->getPrev() && !(pTN->getNext()))
		{
			tmp = pTN;
			(pTN->getPrev())->setNext(NULL);
			free(tmp);
			break;
		}
		else if (!(pTN->getPrev()) && pTN->getNext())
		{
			tmp = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			pTN = pTN->getNext(); pTN->setPrev(NULL);
			free(tmp); break;
		}
		else
		{
			tmp = pTN;
			pTN = pTN->getParent();
			if (pTN != NULL) pTN->setChild(NULL);
			free(tmp);
			if ((pTN == _root) && (pTN->getNext() == NULL) && (pTN->getPrev() == NULL))
			{
				cout << "Now, the trie is empty !!" << endl;
				break;
			}
		}
	}
	this->num_keys--;
}

template<typename E>
void Trie<E>::eraseTrie()
{
	TrieNode<E>* pTN;
	TrieNode<E>* pTN_to_be_deleted = NULL;
	if (this->_root == NULL)
		return;
	pTN = this->_root;
	/* delete the last key word first */
	while (pTN != NULL) {
		while ((pTN != NULL) && (pTN->getNext()))
			pTN = pTN->getNext();
		while (pTN->getChild()) 
		{
			if (pTN->getNext()) 
				break;
			pTN = pTN->getChild();
		}
		if (pTN->getNext()) 
			continue;
		if (pTN->getPrev() && pTN->getNext()) 
		{
			pTN_to_be_deleted = pTN;
			(pTN->getNext())->setPrev(pTN->getPrev());
			(pTN->getPrev())->setNext(pTN->getNext());
			pTN = pTN->getNext();
			free(pTN_to_be_deleted); //free the memory
		}

		else if (pTN->getPrev() && !(pTN->getNext()))
		{
			pTN_to_be_deleted = pTN;
			(pTN->getPrev())->setNext(NULL);
			pTN = pTN->getPrev();
			free(pTN_to_be_deleted); //free the memory
		}
		else if (!(pTN->getPrev()) && pTN->getNext())
		{
			pTN_to_be_deleted = pTN;
			(pTN->getParent())->setChild(pTN->getNext());
			(pTN->getNext())->setPrev(NULL);
			pTN = pTN->getNext();
			free(pTN_to_be_deleted); //free the memory
		}
		else
		{
			pTN_to_be_deleted = pTN;
			if (pTN == this->_root)
			{
				/* _root */
				this->num_keys = 0;
				return;
			}
			if (pTN->getParent() != NULL)
			{
				pTN = pTN->getParent();
				pTN->setChild(NULL);
			}
			else
			{
				pTN = pTN->getPrev();
			}
			free(pTN_to_be_deleted);//free the memory
		} 
	}

}

template<typename E>
void Trie<E>::fprintTrie(ostream& fout)
{
	TrieNode<E>* pTN;
	int line = 1, indent = 0;
	fout << "trie ( " << this->trie_name << ") with "
		<< this->num_keys << " trie_nodes\n";
	if (this->num_keys == 0) {
		fout << "Empty trie !" << endl;
		return;
	}
	pTN = this->_root;
	pTN->_fprint(fout, pTN, indent);
}

//protected--------------------
template<typename E>
TrieNode<E>* Trie<E>::_find(string keyStr, SearchMode sm)
{
	const char* keyPtr;
	TrieNode<E>* pTN = NULL;
	TrieNode<E>* found = NULL;
	if (keyStr.empty())
		return NULL;
	keyPtr = (char*)keyStr.c_str();
	pTN = this->_root; 
	while ((pTN != NULL) && (*keyPtr != '\0'))
	{
		while ((pTN != NULL) && (pTN->getKey() < *keyPtr))
		{
			if (pTN->getNext() == NULL)
				return NULL;
			pTN = pTN->getNext();
		}
		if ((pTN != NULL) && (pTN->getKey() > *keyPtr))
		{
			// key not found
			return NULL;
		}
		else if ((pTN == NULL) && (*keyPtr != '\0'))
		{
			// key not found
			return NULL;
		}
		else if ((pTN->getKey() == *keyPtr) && (*keyPtr != '\0'))
		{
			pTN = pTN->getChild();
			keyPtr++;
			if (*keyPtr == '\0')
			{
				/* key or prefix found */
				if (sm == FULL_MATCH)
				{
					if (pTN->getKey() == '\0')
					{
						/* found the key string as a full-match */
						return pTN;
					}
					else // (pTN->getKey() != '\0')
					{
						/* found the key string as a substring of a longer existing string */
						return NULL;
					}
				}
				else if (sm == PREFIX_MATCH)
				{
					/* found the key string as a full-match or as a substring of a longer existing string */
					return pTN;
				}
			}
			else if ((pTN->getKey() == '\0') && (*keyPtr != '\0'))
			{
				if (pTN->getNext() != NULL)
				{
					pTN = pTN->getNext(); continue;
				}
				else
					return NULL;
			}
			else
			{
				continue;
			}
		}
	}

}

template<typename E>
void Trie<E>::_fprint(ostream& fout, TrieNode<E>* pTN, int indent)
{
	if (pTN == NULL)  //end of downword
	{
		fout << endl;
		return;
	}
	else {
		fout << pTN->key;
		_fprint(fout, pTN->child, indent + 1); //recursive
		if (pTN->next == NULL) //end of same depth
			return;
		for (int i = 0; i < indent; i++)
			fout << " "; // indent
		_fprint(fout, pTN->next, indent); //recursive
	}
}

template<typename E>
void Trie<E>::_traverse(TrieNode<E>* pTN, List_pVoca& list_keywords)
{
	if (pTN == NULL) //if reach end of node, escape this recursive
		return;
	if (pTN->getChild() == NULL)
	{
		list_keywords.push_back(pTN->getValue());
	}
	else
	{
		_traverse(pTN->getChild(), list_keywords); //recursive here
	}
	if (pTN->getNext() != NULL)
	{
		_traverse(pTN->getNext(), list_keywords); //recursive here
	}
}

#endif