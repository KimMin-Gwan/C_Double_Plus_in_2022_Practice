#ifndef BST_RB_H
#define BST_RB_H

#include <iostream>
#include <fstream>
#include "BSTN.h"
#include "T_Array.h"

template<typename K, typename V>
class T_BST
{
public:
	T_BST(string nm) : _root(NULL), num_entry(0), name(nm) {} // constructor
	string getName() { return name; }
	int size() const { return num_entry; }
	bool empty() const { return num_entry == 0; }
	void clear();
	//accessor------------------------------------------------------------------
	T_BSTN<K, V>* getRoot() { return _root; }
	T_BSTN<K, V>** getRootAddr() { return &_root; }
	T_Entry<K, V>& getRootEntry() { return _root->getEntry(); }
	//utility-------------------------------------------------------------------
	T_BSTN<K, V>* eraseBSTN(T_BSTN<K, V>** pp); //erase a node
	void insertInOrder(const T_Entry<K, V> entry); //inserting
	void insertAndRebalance(T_Entry<K, V> e); //ReBanlancing and inserting
	void traversal_inOrder(T_BSTN<K, V>* p, T_Array<V>& array_value);
	void traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	void traversal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value);
	//-----------------------------------------------
	T_BSTN<K, V>* searchBSTN(K k); //searching by key
	T_Entry<K, V>& minEntry(); //find min entry
	T_Entry<K, V>& maxEntry(); //find max entry
	//print------------------------------------------
	void fprint_with_Depth(ostream& fout); //print with depth
	void fprint_inOrder(ostream& fout); //print in order
protected:
	T_BSTN<K, V>* _maxBSTN(T_BSTN<K, V>* subRoot); //find max entry from sub root
	T_BSTN<K, V>* _minBSTN(T_BSTN<K, V>* subRoot); //find min entry from sub root
	T_BSTN<K, V>* _insertInOrder(T_BSTN<K, V>** p, T_BSTN<K, V>* parenPos, const T_Entry<K, V> e);
	T_BSTN<K, V>* _insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e);
	//rebalancing----------------------------------------------------
	T_BSTN<K, V>* _rotate_LL(T_BSTN<K, V>* pCurSubRoot); //rotate left-sided nodes
	T_BSTN<K, V>* _rotate_RR(T_BSTN<K, V>* pCurSubRoot); //rotate right-sided nodes
	T_BSTN<K, V>* _rotate_RL(T_BSTN<K, V>* pCurSubRoot); //rotate unstable nodes
	T_BSTN<K, V>* _rotate_LR(T_BSTN<K, V>* pCurSubRoot); //rotate unstable nodes
	//---------------------------------------------------------------
	int _getHeight(T_BSTN<K, V>* pTN);  //get height (recursive function)
	int _getHeightDiff(T_BSTN<K, V>* pTN); //get heigth difference
	T_BSTN<K, V>* _reBalance(T_BSTN<K, V>** ppTN); //rebalancing 
	T_BSTN<K, V>* _searchBSTN(T_BSTN<K, V>* pos, K k); //Binary search tree searching function
	//print------------------------------------------
	void _fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth); //print with depth
	void _fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout); //print in order
private:
	T_BSTN<K, V>* _root; // pointer to the root
	int num_entry; // number of tree nodes
	string name;
};

template<typename K, typename V>
void T_BST<K, V>::clear()
{
	this->_root = NULL;
	this->num_entry = 0;
	this->name = "default";
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::eraseBSTN(T_BSTN<K, V>** pp)
{
	T_BSTN<K, V>* newSubRoot;
	T_BSTN<K, V>* toBeErased;
	toBeErased = *pp;
	if (toBeErased == NULL)
		return NULL;
	if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() == NULL)) // if no child
	{
		newSubRoot = NULL;
	}
	else if ((toBeErased->getpLc() != NULL) && (toBeErased->getpRc() == NULL)) // if has only left child
	{
		newSubRoot = toBeErased->getpLc();
		newSubRoot->setpPr(toBeErased->getpPr());
	}
	else if ((toBeErased->getpLc() == NULL) && (toBeErased->getpRc() != NULL)) // if has only right child
	{
		newSubRoot = toBeErased->getpRc();
		newSubRoot->setpPr(toBeErased->getpPr());
	}
	else
	{ /* tree node to be deleted has both left child and right child */
		int heightDiff = _getHeightDiff(toBeErased);
		T_BSTN<K, V>* parDel = toBeErased->getpPr();
		T_BSTN<K, V>* lChild = toBeErased->getpLc();
		T_BSTN<K, V>* rChild = toBeErased->getpRc();
		T_BSTN<K, V>* ioSs = NULL, * rcIoSs, * parIoSs;
		T_BSTN<K, V>* ioPd = NULL, * lcIoPd, * parIoPd;
		if (heightDiff > 0)
			// left subtree is higher, so put the ioPd in the place of the erased node
		{
			ioPd = _maxBSTN(lChild); // in-order predecessor (ioPd)
			lcIoPd = ioPd->getpLc();
			parIoPd = ioPd->getpPr();
			newSubRoot = ioPd;
			if (ioPd->getpPr() != toBeErased)
			{
				newSubRoot->setpLc(lChild);
				parIoPd->setpRc(lcIoPd);
				if (lcIoPd != NULL)
					lcIoPd->setpPr(parIoPd);
			}
			newSubRoot->setpRc(rChild);
			newSubRoot->setpPr(toBeErased->getpPr());
		}
		else
			// right subtree is higher, so put the ioSs in the place of the erased node
		{
			ioSs = _minBSTN(rChild); // in-order successor (ioSs)
			rcIoSs = ioSs->getpRc();
			parIoSs = ioSs->getpPr();
			newSubRoot = ioSs;
			if (ioSs->getpPr() != toBeErased)
			{
				newSubRoot->setpRc(rChild);
				parIoSs->setpLc(rcIoSs);
				if (rcIoSs != NULL)
					rcIoSs->setpPr(parIoSs);
			}
			newSubRoot->setpLc(lChild);
			newSubRoot->setpPr(toBeErased->getpPr());
		}
		if (lChild != ioPd)
			lChild->setpPr(newSubRoot);
		if (rChild != ioSs)
			rChild->setpPr(newSubRoot);
	}
	if (toBeErased == this->_root)
		this->_root = newSubRoot;
	this->num_entry--; // decrement the number of entries in the BST
	free(toBeErased);
	*pp = newSubRoot;
	return newSubRoot;

}

template<typename K, typename V>
void T_BST<K, V>::insertInOrder(const T_Entry<K, V> entry)
{
	_insertInOrder(&this->_root, NULL, entry);
}

template<typename K, typename V>
void T_BST<K, V>::insertAndRebalance(T_Entry<K, V> e)
{
	_insertAndRebalance(&this->_root, NULL, e);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_inOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();
	pRc = pos->getpRc();
	traversal_inOrder(pLc, array_value);
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);
	traversal_inOrder(pRc, array_value);
}

template<typename K, typename V>
void T_BST<K, V>::traversal_preOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
}

template<typename K, typename V>
void T_BST<K, V>::traversal_postOrder(T_BSTN<K, V>* pos, T_Array<V>& array_value)
{
	T_BSTN<K, V>* pLc, * pRc;
	T_Entry<K, V> entry;
	V value;
	if (pos == NULL)
		return;
	pLc = pos->getpLc();
	pRc = pos->getpRc();
	traversal_postOrder(pLc, array_value);
	traversal_postOrder(pRc, array_value);
	entry = pos->getEntry();
	value = entry.getValue();
	array_value.insertBack(value);
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::searchBSTN(K k)
{
	T_BSTN<K, V>* pEntry;
	pEntry = _searchBSTN(this->_root, k); //search BST
	return pEntry;
}

template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::minEntry()
{
	T_BSTN<K, V>* pMin;
	pMin = _minBSTN(this->_root); //find min node
	return pMin->getEntry(); //return max node
}

template<typename K, typename V>
T_Entry<K, V>& T_BST<K, V>::maxEntry()
{
	T_BSTN<K, V>* pMax; 
	pMax = _maxBSTN(this->_root); //find max node
	return pMax->getEntry(); //return max node
}

template<typename K, typename V>
void T_BST<K, V>::fprint_with_Depth(ostream& fout)
{
	T_BSTN<K, V>* root = getRoot();
	if (this->num_entry == 0)
	{
		fout << getName() << " is empty now !!" << endl;
		return;
	}
	_fprint_with_Depth(root, fout, 0);
}

template<typename K, typename V>
void T_BST<K, V>::fprint_inOrder(ostream& fout)
{
	T_BSTN<K, V>* root = getRoot();
	if (this->num_entry == 0)
	{
		fout << getName() << " is empty now !!" << endl;
		return;
	}
	_fprint_inOrder(root, fout);
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_maxBSTN(T_BSTN<K, V>* subRoot)
{
	T_BSTN<K, V>* pos;
	if ((subRoot == NULL) ||
		(NULL == subRoot->getpRc()))
		return subRoot;
	pos = subRoot;
	while ((pos->getpRc()) != NULL)
		pos = pos->getpRc();
	return pos;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_minBSTN(T_BSTN<K, V>* subRoot)
{
	T_BSTN<K, V>* pos;
	if ((subRoot == NULL) ||
		(NULL == subRoot->getpLc()))
		return subRoot;
	pos = subRoot;
	while ((pos->getpLc()) != NULL)
		pos = pos->getpLc();
	return pos;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertInOrder(T_BSTN<K, V>** pp, T_BSTN<K, V>* parenPos, const T_Entry<K, V> e)
{
	T_BSTN<K, V>* newPos, ** pChildPos;
	T_BSTN<K, V>* pos;
	T_Entry<K, V> ent;
	if (pp == NULL) 
	{
		cout << "Error in creation of BinarySearchTree : ";
		cout << "address of the pointer to the Root Node is NULL !!" << endl;
		exit;
	}

	pos = *pp;
	if (pos == NULL) {
		pos = new T_BSTN<K, V>(this->num_entry);
		if (parenPos == NULL)
		{
			_root = pos; // initialize the root node }
			pos->setpPr(parenPos);
			*pp = pos;
			this->num_entry++; // increment the number of elements
			return pos;
		}
		ent = pos->getEntry();
		if (this->num_entry < ent)
		{
			pChildPos = pos->getppLc();
			newPos = _insertInOrder(pChildPos, pos, e);
			if (newPos != NULL)
				pos->setpLc(newPos);
			return NULL; // only the leaf child is set correctly, while the intermediate node is skipped
		}
		else if (this->num_entry >= ent)
		{
			pChildPos = pos->getppRc();
			newPos = _insertInOrder(pChildPos, pos, e);
			if (newPos != NULL)
				pos->setpRc(newPos);
			return NULL; // only the leaf child is set correctly, while the intermediate node is skipped
		}
	}
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_insertAndRebalance(T_BSTN<K, V>** ppTN, T_BSTN<K, V>* pPr, T_Entry<K, V> e)
{
	T_BSTN<K, V>* pTN, ** ppLc, ** ppRc;
	if (*ppTN == NULL) // attach a new tree node at the currently external node
	{
		pTN = new T_BSTN<K, V>(e);
		*ppTN = pTN;
		if (pPr != NULL) // if not root
			pTN->setpPr(pPr);
		(*ppTN)->setpLc(NULL);
		(*ppTN)->setpRc(NULL);
		this->num_entry++;
		return *ppTN;
	}
	T_Entry<K, V> bstn_entry;
	bstn_entry = (*ppTN)->getEntry();
	if (e < bstn_entry) // T_Entry<K, V> must provide < operator overloading !!
	{
		ppLc = (*ppTN)->getppLc();
		pTN = _insertAndRebalance(ppLc, *ppTN, e);
		if (ppTN != NULL)
		{
			(*ppTN)->setpLc(pTN);
			*ppTN = _reBalance(ppTN);
		}
	}
	else // entry >= bstn_entry
	{
		ppRc = (*ppTN)->getppRc();
		pTN = _insertAndRebalance(ppRc, *ppTN, e);
		if (ppTN != NULL)
		{
			(*ppTN)->setpRc(pTN);
			*ppTN = _reBalance(ppTN);
		}
	}
	return *ppTN;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LL(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBR, * pCurParent;

	pCurParent = pCurSubRoot->getpPr(); //now node's parent node
	pNewSubRoot = pCurSubRoot->getpLc(); //left child node is sub root
	pBR = pNewSubRoot->getpRc(); //sub root's right child node
	pCurSubRoot->setpLc(pBR); //se now node's left child to sub root's right child
	if (pBR != NULL) //if right child exist 
		pBR->setpPr(pCurSubRoot); //right child's parant is now node

	//pCurParent->getpLc() == *pCurSubRoot ? pCurParent->setpLc(pNewSubRoot) : pCurParent->setpRc(pNewSubRoot);
	//change current parent's child node pointer
	pNewSubRoot->setpRc(pCurSubRoot); //sub root's parent is now node's parent
	pNewSubRoot->setpPr(pCurParent); //sub root's right child is now node
	pCurSubRoot->setpPr(pNewSubRoot); //now node's parent is sub root

	return pNewSubRoot; //return new root
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RR(T_BSTN<K, V>* pCurSubRoot)
{
	T_BSTN<K, V>* pNewSubRoot, * pBL, * pCurParent;

	pCurParent = pCurSubRoot->getpPr(); //now node's parent node
	pNewSubRoot = pCurSubRoot->getpRc(); //left child node is sub root 
	pBL = pNewSubRoot->getpLc(); //sub root's left child node
	pCurSubRoot->setpRc(pBL); //se now node's right child to sub root's left child
	if (pBL != NULL) //if left child exist
		pBL->setpPr(pCurSubRoot); //left child's parant is now node

	//pCurParent->getpLc() == *pCurSubRoot ? pCurParent->setpLc(pNewSubRoot) : pCurParent->setpRc(pNewSubRoot);
	//change current parent's child node pointer
	pNewSubRoot->setpLc(pCurSubRoot); // sub root's left child is now node
	pNewSubRoot->setpPr(pCurParent); //sub root's parent is now node's parent
	pCurSubRoot->setpPr(pNewSubRoot); //now nodes parent is sub root

	return pNewSubRoot; //return new root
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_RL(T_BSTN<K, V>* pCurSubRoot)
{
	/*               new root
	*    pCurSubRoot            pR
	*  left        pRLL    pRLR       right
	*/
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pR, * pC; //* pRL, * pRLL, * pRLR;

	pC = pCurSubRoot;
	pCurParent = pCurSubRoot->getpPr();
	pR = pC->getpRc(); //curent root's right child (pR)
	//pRL = pR->getpLc(); //pR's left child (pRL) 
	//pRLL = pRL->getpLc(); //pBL's left child (pRLL)
	//pRLR = pRL->getpRc(); //pBL's right child (pRLR)

	//Left-sided rotation-----------
	pSubRoot = _rotate_LL(pR);
	pCurSubRoot->setpRc(pSubRoot);
	//Right-sided rotation----------
	pNewSubRoot = _rotate_RR(pC);
	pNewSubRoot->setpPr(pCurParent);

	//pA->setpPr(pNewSubRoot); //new root is curent root's 
	//pC->setpPr(pNewSubRoot);
	/*
	if (pBL != NULL)
		pBL->setpPr(pA);
	if (pBR != NULL)
		pBR->setpPr(pC);
	*/
	return pNewSubRoot;

}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_rotate_LR(T_BSTN<K, V>* pCurSubRoot)
{
	/*          new root
	*      pL            pCurSubRoot
	*  left  pLRL      pLRR      right
	*/
	T_BSTN<K, V>* pSubRoot, * pNewSubRoot, * pCurParent;
	T_BSTN<K, V>* pL, * pC;// *pLR, * pLRL, * pLRR;

	pC = pCurSubRoot;
	pCurParent = pCurSubRoot->getpPr();
	pL = pC->getpLc();  //curent roots left child (pL)
	//pLR = pL->getpRc();  //curent roots left chld's right child (pLR)
	//pLRL = pLR->getpLc(); //pB's left child (pLRL)
	//pLRR = pLR->getpRc(); //pB's right child (pLRR)
	//Right-sided rotation----------
	pSubRoot = _rotate_RR(pL);
	pCurSubRoot->setpLc(pSubRoot); //set root 
	//Left-sided rotation-----------
	pNewSubRoot = _rotate_LL(pC);
	pNewSubRoot->setpPr(pCurParent); //set new root

	//pA->setpPr(pNewSubRoot); //new root is curent root's left child parent
	//pC->setpPr(pNewSubRoot); //new root is curent root's parent
	/*
	if (pBL != NULL)
		pBL->setpPr(pA);
	if (pBR != NULL)
		pBR->setpPr(pC);
	*/
	return pNewSubRoot;
}

template<typename K, typename V>
int T_BST<K, V>::_getHeight(T_BSTN<K, V>* pTN)
{
	//recursive function
	int height = 0;
	int heightLC, heightRC;

	if (pTN != NULL)
	{
		heightLC = _getHeight(pTN->getpLc()); //get left child height
		heightRC = _getHeight(pTN->getpRc()); //get right child height
		if (heightLC > heightRC) //if left height is bigger than right height
			height = 1 + heightLC; //left hieght + 1 is now height
		else					//if right height is bigger than left height
			height = 1 + heightRC; //right hieght +1 is now height
	}
	return height; //escape this recursive and return now height
}

template<typename K, typename V>
int T_BST<K, V>::_getHeightDiff(T_BSTN<K, V>* pTN) 
{ 
	if (pTN == NULL) //check exception
		return 0;
	//get difference of right and left child
	return _getHeight(pTN->getpLc()) - _getHeight(pTN->getpRc()); 
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_reBalance(T_BSTN<K, V>** ppTN)
{
	int heightDiff = 0;
	heightDiff = _getHeightDiff(*ppTN);
	if (heightDiff > 1) // left subtree is higher
	{
		if (_getHeightDiff((*ppTN)->getpLc()) > 0)
			*ppTN = _rotate_LL(*ppTN);
		else
			*ppTN = _rotate_LR(*ppTN);
	}
	else if (heightDiff < -1) // right subtree is higher
	{
		if (_getHeightDiff((*ppTN)->getpRc()) < 0)
			*ppTN = _rotate_RR(*ppTN);
		else
			*ppTN = _rotate_RL(*ppTN);
	}
	return *ppTN;
}

template<typename K, typename V>
T_BSTN<K, V>* T_BST<K, V>::_searchBSTN(T_BSTN<K, V>* pos, K k)
{
	K ent_k;
	T_BSTN<K, V>* pos_result = NULL;
	if (pos == NULL)
		return NULL;
	ent_k = pos->getKey();
	if (ent_k == k)
		pos_result = pos;
	// given entry was found here !!
	else if (ent_k > k)
		pos_result = _searchBSTN(pos->getpLc(), k);
	else if (ent_k < k)
		pos_result = _searchBSTN(pos->getpRc(), k);
	return pos_result;
}

template<typename K, typename V>
void T_BST<K, V>::_fprint_with_Depth(T_BSTN<K, V>* pTN, ostream& fout, int depth)
{
	T_BSTN<K, V>* pRc, * pLc;

	if ((pRc = pTN->getpRc()) != NULL)
		_fprint_with_Depth(pRc, fout, depth + 1);
	for (int i = 0; i < depth; i++) 
	{
		fout << "    ";
	}
	fout << pTN->getEntry() << endl;
	if ((pLc = pTN->getpLc()) != NULL)
		_fprint_with_Depth(pLc, fout, depth + 1);
}

template<typename K, typename V>
void T_BST<K, V>::_fprint_inOrder(T_BSTN<K, V>* pTN, ostream& fout)
{
	T_BSTN<K, V>* pRc, * pLc;

	if ((pLc = pTN->getpLc()) != NULL) 
		_fprint_inOrder(pLc, fout);
	fout << pTN->getEntry() << endl;
	if ((pRc = pTN->getpRc()) != NULL) 
		_fprint_inOrder(pRc, fout);
}

#endif