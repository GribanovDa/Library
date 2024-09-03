#pragma once
#include "book.h"

void AddBook(Book& book, vector<Book>& allBooksNew);
void AddNewBook(Book& book, vector<Book>& allBooks);
vector<Book> FindBookName(string& name, vector<Book> allBooks);
vector<Book> FindBookNumber(int& number, vector<Book> allBooks);
vector<Book> FindBookAuthor(string& author, vector<Book> allBooks);
void EditBook(vector<Book> &allBooks);
void DeleteBook(vector<Book> required, vector<Book> allBooks);
void GiveBook();
void TakeBook();
vector<Book> GetAllFromFile();
int GetBooksQuantity();
string Correcter(string& str);
void DisplayInfo();

