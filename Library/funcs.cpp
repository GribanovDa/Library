#include "funcs.h"

// Возвращает количество книг
int GetBooksQuantity() {                      

	int quantity;

	fstream quantityfile("BookQuantity.txt", ios::in);

	if (quantityfile.is_open()) {             // Достаем из файла количество книг и записываем в переменную quantity
		string a;
		quantityfile >> a;
		quantity = stoi(a);
	}

	else {
		cout << "Не удается прочесть данные.";
		quantityfile.close();
		return 0;
	}
	quantityfile.close();
	return quantity;

}


// Заносит книгу в файл с изменением в файле BookQuantity.txt
void AddNewBook(Book& book, vector<Book>& allBooks) {

	// Считываем номер последней книги, чтобы задать номер новой
	auto iteratorLastBook = allBooks.size() - 1;
	int bookNumber;
	if (allBooks.size() == 0) {
		bookNumber = 1;
	}
	else {
		bookNumber = allBooks[iteratorLastBook].GetNumber() + 1;
	}
	int bookQuantity = GetBooksQuantity();
	string author = book.GetAuthor();
	string name = book.GetName();


	ofstream booksfile("books.txt", ofstream::app);
	ofstream quantityfile1("BookQuantity.txt", ios::out);

	// Заносим значения книги в файл
	if (booksfile.is_open() && quantityfile1.is_open()) {
		booksfile << bookNumber << endl << name << endl << author << endl << book.GetPublisher() << endl
			<< book.GetYear() << endl << book.GetIsOnStock() << endl;
		quantityfile1 << bookQuantity+1;
	}
	else {
		cout << "Не удается прочесть данные.";
		booksfile.close();
		return;
	}

	// Выводим сообщение об успешном выполнении
	cout << endl << "Добавлена книга:" << endl << "№ " << bookNumber+1 << endl << "Автор: " << author << endl << "Название: " << name
		<< endl << "Издательство: " << book.GetPublisher() << " - " << book.GetYear() << " год." << endl;
	if (book.GetIsOnStock())
		cout << "В наличии\n";
	else
		cout << "Нет в наличии\n";

	// Добавляем книгу в список книг с новым номером
	book.SetNuber(bookNumber + 1);
	allBooks.push_back(book);

	booksfile.close();
	quantityfile1.close();

}


// Заносит книгу в файл без изменений в файле BookQuantity.txt
void AddBook(Book& book, vector<Book>& allBooksNew) {

	// Добавляем книгу в список книг
	allBooksNew.push_back(book);

	int bookNumber = GetBooksQuantity();
	string author = book.GetAuthor();
	string name = book.GetName();

	ofstream booksfile("books.txt", ofstream::app);

	// Заносим значения книги в файл
	if (booksfile.is_open()) {
		booksfile << book.GetNumber() << endl << name << endl << author << endl << book.GetPublisher() << endl
			<< book.GetYear() << endl << book.GetIsOnStock() << endl;
	}
	else {
		cout << "Не удается прочесть данные.";
		booksfile.close();
		return;
	}
	booksfile.close();

}


// Достает все книги из файла и записывает в вектор
vector<Book> GetAllFromFile() {      

	const unsigned short quantity = GetBooksQuantity();

	string name, author, publisher, number, year, isOnStock;

	vector<Book> booksList;          // Создаем вектор
	booksList.reserve(quantity);     // Резервируем место в векторе под количество книг

	ifstream file("books.txt");

	// Достаем все книги из файла 
	while (getline(file, number)) {
		if (getline(file, name) && getline(file, author) && getline(file, publisher) && getline(file, year) && getline(file, isOnStock)) {
			// Добавляем книгу в вектор
			booksList.emplace_back(stoi(number), name, author, publisher, stoi(year), stoi(isOnStock));  
		}
	}
	file.close();
	return booksList;
}


// Функция-компаратор для поиска по имени
bool compareByName(const Book& book, const string& targetName) {   
	return book.name < targetName;
}


// Функция-компаратор для поиска по номеру
bool compareByNumber(const Book& book, const int& targetNumber) {
	return book.number < targetNumber;
}


// Функция-компаратор для поиска по автору
bool compareByAuthor(const Book& book, const string& targetAuthor) {
	return book.author < targetAuthor;
}


// Находит книгу по названию
vector<Book> FindBookName(string& name, vector<Book> allBooks) {

	name = Correcter(name);
	auto requiredBook = lower_bound(allBooks.begin(), allBooks.end(), name, compareByName);       // Находим итератор искомой книги по названию
	vector<Book> findedList;                                                                      // Список найденных книг


	sort(allBooks.begin(), allBooks.end(), [](const Book& a, const Book& b) {					  // Сортируем вектор по названию книги
		return compareByName(a, b.GetName()); });

	for (int i = 0; i < GetBooksQuantity(); i++) {												  // Составление списка найденных книг
		requiredBook = lower_bound(allBooks.begin(), allBooks.end(), name, compareByName);		  // Находим итератор искомой книги по названию
		if (requiredBook != allBooks.end() && requiredBook->GetName() == name) {			      // Если искомое совпадает с найденным
			Book temp(requiredBook->GetName(), requiredBook->GetAuthor(),
				requiredBook->GetPublisher(), requiredBook->GetYear(), requiredBook->GetIsOnStock());
			temp.SetNuber(requiredBook->GetNumber());
			findedList.push_back(temp);														      // Добавляем найденную книгу в список
			allBooks.erase(requiredBook);														  // Удаляем найденную книгу из списка книг, чтобы не наткнуться
		}																						  // на нее снова

	}
	return findedList;

}


// Находит книгу по номеру
vector<Book> FindBookNumber(int& number, vector<Book> allBooks) {

	auto requiredBook = lower_bound(allBooks.begin(), allBooks.end(), number, compareByNumber);   // Находим итератор искомой книги по названию
	vector<Book> findedList;                                                                      // Список найденных книг


	sort(allBooks.begin(), allBooks.end(), [](const Book& a, const Book& b) {					  // Сортируем вектор по названию книги
		return compareByNumber(a, b.GetNumber()); });

	for (int i = 0; i < GetBooksQuantity(); i++) {												  // Составление списка найденных книг
		requiredBook = lower_bound(allBooks.begin(), allBooks.end(), number, compareByNumber);		  // Находим итератор искомой книги по названию
		if (requiredBook != allBooks.end() && requiredBook->GetNumber() == number) {			      // Если искомое совпадает с найденным
			Book temp(requiredBook->GetName(), requiredBook->GetAuthor(),
				requiredBook->GetPublisher(), requiredBook->GetYear(), requiredBook->GetIsOnStock());
			temp.SetNuber(requiredBook->GetNumber());
			findedList.push_back(temp);														      // Добавляем найденную книгу в список
			allBooks.erase(requiredBook);														  // Удаляем найденную книгу из списка книг, чтобы не наткнуться
		}																						  // на нее снова
		else
			break;

	}
	return findedList;
}


// Находит книгу по автору
vector<Book> FindBookAuthor(string& author, vector<Book> allBooks) {

	author = Correcter(author);
	auto requiredBook = lower_bound(allBooks.begin(), allBooks.end(), author, compareByAuthor);    // Находим итератор искомой книги по названию
	vector<Book> findedList;                                                                       // Список найденных книг


	sort(allBooks.begin(), allBooks.end(), [](const Book& a, const Book& b) {                     // Сортируем вектор по названию книги
		return compareByAuthor(a, b.GetAuthor()); });

	for (int i = 0; i < GetBooksQuantity(); i++) {												  // Составление списка найденных книг
		requiredBook = lower_bound(allBooks.begin(), allBooks.end(), author, compareByAuthor);    // Находим итератор искомой книги по названию
		if (requiredBook != allBooks.end() && requiredBook->GetAuthor() == author) {			  // Если искомое совпадает с найденным
			Book temp(requiredBook->GetName(), requiredBook->GetAuthor(),
				requiredBook->GetPublisher(), requiredBook->GetYear(), requiredBook->GetIsOnStock());
			temp.SetNuber(requiredBook->GetNumber());
			findedList.push_back(temp);														      // Добавляем найденную книгу в список
			allBooks.erase(requiredBook);														  // Удаляем найденную книгу из списка книг, чтобы не наткнуться
		}																						  // на нее снова
		else
			break;
	}
	return findedList;
}


// Делает все буквы в словах заглавными, а внутри слов прописными
string Correcter(string& str) {
	string result = "";

	for (int i = 0; i < str.length(); i ++) {
		if ((str[i] == ' ' && i == 0) || (str[i] == ' ' && i == str.length()-1) || (str[i] == ' ' && str[i-1] == ' '))
			continue;
		else if (i != 0 && str[i - 1] == ' ')
			result += toupper(str[i]);
		else if (i == 0 && str[i] != ' ')
			result += toupper(str[i]);
		else if (i != 0 && i != str.length()-1 && str[i + 1] != ' ' && str[i - 1] != ' ')
			result += tolower(str[i]);
		else 
			result += tolower(str[i]);
	}

	return result;
}


// Удаляет книгу
void DeleteBook(vector<Book> required, vector<Book> allBooks) {

	vector<Book> allBooksNew;

	if (required.empty()) {											// Проверяем, нашлась ли хоть одна книга
		cout << "\nУказанная книга не найдена.";
		return;
	}

	short deletedBook;												// Создаем необходимые переменные и списки
	int bookQuantuty = GetBooksQuantity();

	for (int i = 0; i < required.size(); i++) {						// Выводим информацию о найденных книгах
		cout << "\nКнига №" << i + 1;
		required[i].GetInfo();
	}

	cout << "\nНайдено " << required.size() << " книг. Какую из найденных книг вы хотите удалить? \n";
	cin >> deletedBook;												// Пользователь выбирает какую книгу удалить

	int deletedBookNumber = required[deletedBook-1].GetNumber();	// Получаем номер удаляемой книги
	auto requiredBook = lower_bound(allBooks.begin(), allBooks.end(), deletedBookNumber, compareByNumber);   //Ищем книгу с таким номером

	allBooks.erase(requiredBook);									// Удаляем книгу из общего списка и освобождаем память
	allBooks.shrink_to_fit();

	ofstream booksfile("books.txt");
	ofstream quantityfile("BookQuantity.txt", ios::out);
	if (booksfile.is_open() && quantityfile.is_open()) {
		quantityfile << bookQuantuty - 1;							// Заносим новое количество книг в файл "BookQuantity.txt"
		quantityfile.close();

		for (int i = 0; i < bookQuantuty-1; i++) {					// Заносим в файл обновленный список книг
			AddBook(allBooks[i], allBooksNew);
		}
		allBooks.clear();
		allBooks = allBooksNew;
		booksfile.close();
	}
	else {
		cout << "Не удается прочесть данные.";
		booksfile.close();
		quantityfile.close();
		return;
	}
	cout << endl << "Книга успешно удалена." << endl;
}


// Отображает возможные команды
void DisplayInfo() {
	cout << "\nСписок доступных команд:" << "\n1 - Получить список всех книг;" << "\n2 - Получить количество книг;" << "\n3 - Добавить новую книгу;"
		<< "\n4 - Найти книгу;" << "\n5 - Удалить книгу;" << "\n6 - Редактировать книгу;\n";
}


void EditBook(vector<Book>& allBooks) {

	int number;
	Book N;
	int bookQuantuty = GetBooksQuantity();
	if (bookQuantuty == 1) 
		bookQuantuty = 2;
	
	vector<Book> allBooksNew;

	cout << "\nВведите номер книги, которую хотите изменить: ";
	cin >> number;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vector<Book> finded = FindBookNumber(number, allBooks);

	if (!finded.empty()) {																	  // Выводим сообщение, что книга найдена
			finded[0].GetInfo();

			auto findedBook = lower_bound(allBooks.begin(), allBooks.end(), number, compareByNumber);   //Ищем книгу с таким номером

			cout <<  endl << "Заполните поля новыми значениями:" << endl;
			N.SetValues();
			N.SetNuber(number);



			ofstream booksfile("books.txt");
			if (booksfile.is_open()) {
														
				allBooks.erase(findedBook);
				allBooks.push_back(N);
				allBooks.shrink_to_fit();

				sort(allBooks.begin(), allBooks.end(), [](const Book& a, const Book& b) {	// Сортируем вектор по названию книги
					return compareByNumber(a, b.GetNumber()); });

				for (int i = 0; i < bookQuantuty; i++) {									// Заносим в файл обновленный список книг
					AddBook(allBooks[i], allBooksNew);
				}
				allBooks.clear();
				allBooks = allBooksNew;
				booksfile.close();

			}
			else {
				cout << "Не удается прочесть данные.";
				booksfile.close();
				return;
			}
			cout << endl << "Книга успешно изменена." << endl;
	}
	else {
		cout << "\nКнига №\"" << number << "\" не найдена." << endl;					 // Выводим сообщение, что книга не найдена
		return;
	}


}