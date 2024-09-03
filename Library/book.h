#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
#include <conio.h>
using namespace std;


class Book
{
private: 
	string name;
	string author;
	string publisher;
	int year;
	int number;
	bool isOnStock;

public:
	Book() {};
	Book(string name, string author, string publisher, int year, bool isOnStock);
	Book(int number, string name, string author, string publisher, int year, bool isOnStock);
	Book(string name, string author, string publisher, int year) {
		this->name = name;
		this->author = author;
		this->publisher = publisher;
		this->year = year;
		isOnStock = true;
	}


	friend bool compareByName(const Book& book, const string& targetTitle);
	friend bool compareByNumber(const Book& book, const int& targetNumber);
	friend bool compareByAuthor(const Book& book, const string& targetAuthor);

	void SetNuber(int number) { this->number = number;}
	void SetName(string name) { this->name = name; }
	void SetAuthor(string author) { this->author = author; }
	void SetPublisher(string publisher) { this->publisher = publisher; }
	void SetName(int year) { this->year = year; }
	void SetIsOnStock(bool isOnStock) { this->isOnStock = isOnStock; }
	int GetNumber() const {return number;}
	int GetYear() const { return year;}
	bool GetIsOnStock() const { return isOnStock;}
	string GetName() const {return name;}
	string GetAuthor() const { return author; }
	string GetPublisher() const { return publisher; }
	void SetValues();
	void GetInfo();

	
};

