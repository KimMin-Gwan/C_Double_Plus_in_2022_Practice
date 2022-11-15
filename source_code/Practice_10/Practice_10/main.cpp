#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <sstream> // for stringstream
#include "BST_RB.h"
#include "T_Entry.h"
#include "Book.h"
#include "T_Array.h"

using namespace std;
Book* fGetBookRecords(string fileName, int *pNumBook)
{
	int numBook;
	string bookTitle, author, dateStr;
	Date date;
	int isbn, year, month, day;

	ifstream fin(fileName);
	fin >> numBook;
	Book* books = new Book[numBook];
	*pNumBook = numBook;
	cout << "Number of books = " << numBook << endl;
	for (int i = 0; i < numBook; i++)
	{
		fin >> bookTitle >> author >> dateStr >> isbn;
		for (int i = 0; i < dateStr.size(); i++)
		{
			if (dateStr[i] == '-')
				dateStr[i] = ' ';
		}
		stringstream dateStrStream;
		dateStrStream.str(dateStr);
		dateStrStream >> year >> month >> day;

		cout << "input book record (" << bookTitle;
		cout << ", " << author;
		cout << ", (" << year << ", " << month << ", " << day;
		cout << "), " << isbn << ")" << endl;
		books[i] = Book(bookTitle, author, Date(year, month, day), isbn);
	}
	fin.close();
	return books;
}

int main(void)
{	
	//get books --------------------------------------------
	Book* books;
	int num_books;
	books = fGetBookRecords("books.txt", &num_books); // get book records from input data file
	//------------------------------------------------------
	ofstream fout("output.txt");
	if (fout.fail())
	{
		cout << "Fail to create output.txt for results !!" << endl;
		exit(0);
	}
	fout << "Input books[] array : " << endl;
	for (int i = 0; i < num_books; i++)
	{
		fout << books[i] << endl;
	}
	//--Get Title------------------------------------------
	fout << endl;
	fout << endl << "Balanced Binary Search Tree (BBST) with key book-title" << endl;
	T_Entry<string, Book*> entry_title_pBK; //entry title
	T_BST<string, Book*> BBST_BK_keyTitle("BBST_BK_keyTitle"); //BST Title
	T_BSTN<string, Book*>* pRoot, ** ppBBST_BK_root; 
	ppBBST_BK_root = BBST_BK_keyTitle.getRootAddr(); //get root address
	for (int i = 0; i < num_books; i++)
	{
		entry_title_pBK.setKey(books[i].getTitle()); //key as title
		entry_title_pBK.setValue(&books[i]); //books data as value
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyTitle.insertAndRebalance(entry_title_pBK); //insert BST and rebalance
	}
	fout << "\nEntries in " << BBST_BK_keyTitle.getName() << " (in order of Book Title) : " << endl;
	//BBST_BK_keyTitle.fprint_inOrder(fout);
	BBST_BK_keyTitle.fprint_with_Depth(fout); //print title with depth

	//--Get Author-----------------------------------------
	fout << endl << "Balanced Binary Search Tree (BBST) with key book-author" << endl;
	T_Entry<string, Book*> entry_Author_pBK; // entry author
	T_BST<string, Book*> BBST_BK_keyAuthor("BBST_BK_keyAuthor"); //BST author
	T_BSTN<string, Book*>** ppRoot_BBST_BK_keyAuthor, * pBBST_BK_keyAuthor; //node pointer
	ppRoot_BBST_BK_keyAuthor = BBST_BK_keyAuthor.getRootAddr(); //get root address
	for (int i = 0; i < num_books; i++)
	{
		entry_Author_pBK.setKey(books[i].getAuthor()); 
		entry_Author_pBK.setValue(&books[i]);
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyAuthor.insertAndRebalance(entry_Author_pBK);
	}
	fout << "\nEntries in " << BBST_BK_keyAuthor.getName() << " (in order of Book Author) : " << endl;
	//BBST_BK_keyAuthor.fprint_inOrder(fout);
	BBST_BK_keyAuthor.fprint_with_Depth(fout);

	// Testing Search on Binary Search Tree------------------------------------
	string author = books[0].getAuthor();
	Date d1, d2;
	Book* pBk;
	T_Array<Book*> array_pBook(1, string("Array_Book"));
	d1.setDate(2010, 1, 1);
	d2.setDate(2015, 12, 31);
	pBBST_BK_keyAuthor = BBST_BK_keyAuthor.searchBSTN(author);
	BBST_BK_keyAuthor.traversal_inOrder(pBBST_BK_keyAuthor, array_pBook);
	fout << "Books of author (" << author << ") published during " << d1 << " ~ " << d2 << ":" << endl;

	for (int i = 0; i < array_pBook.Size(); i++)
	{
		if (array_pBook[i]->getAuthor() == author)
		{
			pBk = array_pBook[i];
			if ((pBk->getPubDate() >= d1) && (pBk->getPubDate() <= d2))
				fout << *(array_pBook[i]) << endl;
		}
	}
	
	//--Get Date-------------------------------------------
	fout << endl << "Balanced Binary Search Tree (BBST) with key publication-date" << endl;
	T_Entry<Date, Book*> entry_PubDate_pBK;
	T_BST<Date, Book*> BBST_BK_keyPubDate("BBST_BK_keyPubDate");
	T_BSTN<Date, Book*>** ppRoot_BBST_BK_keyPubDate;
	ppRoot_BBST_BK_keyPubDate = BBST_BK_keyPubDate.getRootAddr();

	for (int i = 0; i < num_books; i++)
	{
		entry_PubDate_pBK.setKey(books[i].getPubDate());
		entry_PubDate_pBK.setValue(&books[i]);
		//fout << "Insert inOrder (" << setw(3) << books[i] << ") into " << BBST_BK_keyTitle.getName() << endl;
		BBST_BK_keyPubDate.insertAndRebalance(entry_PubDate_pBK);
		//BBST_BK_keyPubDate.fprint_with_Depth(cout);
		//cout << endl;
	}
	fout << "\nEntries in " << BBST_BK_keyPubDate.getName() << " (in order of Book Publication Date) : " << endl;
	BBST_BK_keyPubDate.fprint_inOrder(fout);
	BBST_BK_keyPubDate.fprint_with_Depth(fout);

	//erase---------------------------------------------------------
	fout << "\nRemoving the root entry in sequence ..." << endl;

	for (int i = 0; i < num_books; i++)
	{
		pRoot = BBST_BK_keyTitle.getRoot();
		entry_title_pBK = pRoot->getEntry();
		fout << "\nremove " << entry_title_pBK << endl;
		BBST_BK_keyTitle.eraseBSTN(&pRoot);
		BBST_BK_keyTitle.fprint_with_Depth(fout);
	}

	fout << "\nClearing BBST_BKs . . . " << endl;
	BBST_BK_keyTitle.clear();
	BBST_BK_keyAuthor.clear();
	//BBST_BK_keyPubDate.clear();
	fout << "All BBST_BKs cleared !! " << endl;
	fout.close();
	if (books != NULL)
		delete[] books;
	return 0;
}