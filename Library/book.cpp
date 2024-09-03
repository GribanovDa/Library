#include "book.h"

// ������������
Book::Book(string name, string author, string publisher, int year, bool isOnStock) {
	this->name = name;
	this->author = author;
	this->publisher = publisher;
	this->year = year;
	this->number = NULL;
	this->isOnStock = isOnStock;
	}
Book::Book(int number, string name, string author, string publisher, int year, bool isOnStock) {
	this->name = name;
	this->author = author;
	this->publisher = publisher;
	this->year = year;
	this->number = number;
	this->isOnStock = isOnStock;
}


string Correcter(string& str);


// ������ �������� ����� ������ Book
void Book::SetValues() {  

	setlocale(LC_ALL, "RU");

	string name, nameCorrect, author, authorCorrect, publisher, stock;
	bool val;
	bool tryBool = true;
	bool tryInt = true;
	int year;

	cout << "�������� �����: ";
	getline(cin, name);
	nameCorrect = Correcter(name);
	this->name = nameCorrect;
	cout << endl << "����� �����: ";
	getline(cin, author);
	authorCorrect = Correcter(author);
	this->author = authorCorrect;
	cout << endl << "������������: ";
	getline(cin, publisher);
	this->publisher = publisher;
	
	// �������� �� ������������ ����
	while (tryInt) {
		cout << endl << "���: ";
		cin >> year;
		if (cin.fail()) {
			cin.clear(); // ������� ��������� ������
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ������������ ����
			cout << "������������ ����! ���������� �����." << endl;
		}
		else {
			this->year = year;
			tryInt = false;
		}
	}

	// �������� �� ������������ ����
	while (tryBool) {
		cout << endl << "���� ����� � �������, �� ������� \"1\", ���� ���, �� \"0\": ";
		cin >> val;
		if (cin.fail()) {
			cin.clear(); // ������� ��������� ������
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // ���������� ������������ ����
			cout << "������������ ����! ���������� �����." << endl;
		}
		else {
			isOnStock = val;
			tryBool = false;
		}
	}
}


// ������� ���������� � ����� � �������
void Book::GetInfo() {                    
	cout << endl << author << " - \"" << name << "\"";
	cout << endl << "������������: " << publisher << " - " << year << " ���.";
	if (isOnStock)
		cout << endl << "� �������. " << "� " << number << endl;
	else
		cout << endl << "��� � �������. " << "� " << number << endl;
}
