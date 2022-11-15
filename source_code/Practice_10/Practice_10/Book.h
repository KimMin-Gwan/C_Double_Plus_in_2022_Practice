#ifndef BOOK_H
#define BOOK_H
#include "Date.h"

class Book
{
	friend ostream& operator<<(ostream& fout, Book& bk)
	{
		fout.setf(ios::left);
		fout << "[" << setw(8) << bk.title << ", " << setw(8) << bk.author << ", " << bk.pubDate;
		fout << ", " << bk.isbn << "]";
		return fout;
	}
public:
	Book() : 
		title("default"), author("ananymous"), pubDate(), isbn(0) {} //default constructor
	Book(string bk_title, string bk_author, Date pd, int bn) : //constructor
		title(bk_title), author(bk_author), pubDate(pd), isbn(bn) {}
	//accesser and mutator -------------------------------------
	string& getTitle() { return title; } //get title
	string getAuthor() { return author; } //get author
	Date getPubDate() { return pubDate; } //get published date
	int getISBN() { return isbn; } //get ISBN
	void setTitle(string bk_title) { title = bk_title; } //set title
	void setAuthor(string bk_author) { author = bk_author; } //set author
	void setPubDate(Date pd) { pubDate = pd; } //set date
	void setISBN(int bn) { isbn = bn; } //set ISBN
private:
	string title;
	string author;
	Date pubDate; // date of publish
	int isbn; // international standard book number
};

#endif