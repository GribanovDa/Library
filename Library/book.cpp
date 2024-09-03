#include "book.h"

// Конструкторы
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


// Задает значения полей класса Book
void Book::SetValues() {  

	setlocale(LC_ALL, "RU");

	string name, nameCorrect, author, authorCorrect, publisher, stock;
	bool val;
	bool tryBool = true;
	bool tryInt = true;
	int year;

	cout << "Название книги: ";
	getline(cin, name);
	nameCorrect = Correcter(name);
	this->name = nameCorrect;
	cout << endl << "Автор книги: ";
	getline(cin, author);
	authorCorrect = Correcter(author);
	this->author = authorCorrect;
	cout << endl << "Издательство: ";
	getline(cin, publisher);
	this->publisher = publisher;
	
	// Проверка на некорректный ввод
	while (tryInt) {
		cout << endl << "Год: ";
		cin >> year;
		if (cin.fail()) {
			cin.clear(); // Очистка состояния потока
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем некорректный ввод
			cout << "Некорректный ввод! Попробуйте снова." << endl;
		}
		else {
			this->year = year;
			tryInt = false;
		}
	}

	// Проверка на некорректный ввод
	while (tryBool) {
		cout << endl << "Если книга в наличии, то введите \"1\", если нет, то \"0\": ";
		cin >> val;
		if (cin.fail()) {
			cin.clear(); // Очистка состояния потока
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Игнорируем некорректный ввод
			cout << "Некорректный ввод! Попробуйте снова." << endl;
		}
		else {
			isOnStock = val;
			tryBool = false;
		}
	}
}


// Выволит информацию о книге в консоль
void Book::GetInfo() {                    
	cout << endl << author << " - \"" << name << "\"";
	cout << endl << "Издательство: " << publisher << " - " << year << " год.";
	if (isOnStock)
		cout << endl << "В наличии. " << "№ " << number << endl;
	else
		cout << endl << "Нет в наличии. " << "№ " << number << endl;
}
