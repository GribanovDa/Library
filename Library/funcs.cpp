#include "funcs.h"

// ���������� ���������� ����
int GetBooksQuantity() {                      

	int quantity;

	fstream quantityfile("BookQuantity.txt", ios::in);

	if (quantityfile.is_open()) {             // ������� �� ����� ���������� ���� � ���������� � ���������� quantity
		string a;
		quantityfile >> a;
		quantity = stoi(a);
	}

	else {
		cout << "�� ������� �������� ������.";
		quantityfile.close();
		return 0;
	}
	quantityfile.close();
	return quantity;

}


// ������� ����� � ���� � ���������� � ����� BookQuantity.txt
void AddNewBook(Book& book, vector<Book>& allBooks) {

	// ��������� ����� ��������� �����, ����� ������ ����� �����
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

	// ������� �������� ����� � ����
	if (booksfile.is_open() && quantityfile1.is_open()) {
		booksfile << bookNumber << endl << name << endl << author << endl << book.GetPublisher() << endl
			<< book.GetYear() << endl << book.GetIsOnStock() << endl;
		quantityfile1 << bookQuantity+1;
	}
	else {
		cout << "�� ������� �������� ������.";
		booksfile.close();
		return;
	}

	// ������� ��������� �� �������� ����������
	cout << endl << "��������� �����:" << endl << "� " << bookNumber+1 << endl << "�����: " << author << endl << "��������: " << name
		<< endl << "������������: " << book.GetPublisher() << " - " << book.GetYear() << " ���." << endl;
	if (book.GetIsOnStock())
		cout << "� �������\n";
	else
		cout << "��� � �������\n";

	// ��������� ����� � ������ ���� � ����� �������
	book.SetNuber(bookNumber + 1);
	allBooks.push_back(book);

	booksfile.close();
	quantityfile1.close();

}


// ������� ����� � ���� ��� ��������� � ����� BookQuantity.txt
void AddBook(Book& book, vector<Book>& allBooksNew) {

	// ��������� ����� � ������ ����
	allBooksNew.push_back(book);

	int bookNumber = GetBooksQuantity();
	string author = book.GetAuthor();
	string name = book.GetName();

	ofstream booksfile("books.txt", ofstream::app);

	// ������� �������� ����� � ����
	if (booksfile.is_open()) {
		booksfile << book.GetNumber() << endl << name << endl << author << endl << book.GetPublisher() << endl
			<< book.GetYear() << endl << book.GetIsOnStock() << endl;
	}
	else {
		cout << "�� ������� �������� ������.";
		booksfile.close();
		return;
	}
	booksfile.close();

}


// ������� ��� ����� �� ����� � ���������� � ������
vector<Book> GetAllFromFile() {      

	const unsigned short quantity = GetBooksQuantity();

	string name, author, publisher, number, year, isOnStock;

	vector<Book> booksList;          // ������� ������
	booksList.reserve(quantity);     // ����������� ����� � ������� ��� ���������� ����

	ifstream file("books.txt");

	// ������� ��� ����� �� ����� 
	while (getline(file, number)) {
		if (getline(file, name) && getline(file, author) && getline(file, publisher) && getline(file, year) && getline(file, isOnStock)) {
			// ��������� ����� � ������
			booksList.emplace_back(stoi(number), name, author, publisher, stoi(year), stoi(isOnStock));  
		}
	}
	file.close();
	return booksList;
}


// �������-���������� ��� ������ �� �����
bool compareByName(const Book& book, const string& targetName) {   
	return book.name < targetName;
}


// �������-���������� ��� ������ �� ������
bool compareByNumber(const Book& book, const int& targetNumber) {
	return book.number < targetNumber;
}


// �������-���������� ��� ������ �� ������
bool compareByAuthor(const Book& book, const string& targetAuthor) {
	return book.author < targetAuthor;
}


// ������� ����� �� ��������
vector<Book> FindBookName(string& name, vector<Book> allBooks) {

	name = Correcter(name);
	auto requiredBook = lower_bound(allBooks.begin(), allBooks.end(), name, compareByName);       // ������� �������� ������� ����� �� ��������
	vector<Book> findedList;                                                                      // ������ ��������� ����


	sort(allBooks.begin(), allBooks.end(), [](const Book& a, const Book& b) {					  // ��������� ������ �� �������� �����
		return compareByName(a, b.GetName()); });

	for (int i = 0; i < GetBooksQuantity(); i++) {												  // ����������� ������ ��������� ����
		requiredBook = lower_bound(allBooks.begin(), allBooks.end(), name, compareByName);		  // ������� �������� ������� ����� �� ��������
		if (requiredBook != allBooks.end() && requiredBook->GetName() == name) {			      // ���� ������� ��������� � ���������
			Book temp(requiredBook->GetName(), requiredBook->GetAuthor(),
				requiredBook->GetPublisher(), requiredBook->GetYear(), requiredBook->GetIsOnStock());
			temp.SetNuber(requiredBook->GetNumber());
			findedList.push_back(temp);														      // ��������� ��������� ����� � ������
			allBooks.erase(requiredBook);														  // ������� ��������� ����� �� ������ ����, ����� �� ����������
		}																						  // �� ��� �����

	}
	return findedList;

}


// ������� ����� �� ������
vector<Book> FindBookNumber(int& number, vector<Book> allBooks) {

	auto requiredBook = lower_bound(allBooks.begin(), allBooks.end(), number, compareByNumber);   // ������� �������� ������� ����� �� ��������
	vector<Book> findedList;                                                                      // ������ ��������� ����


	sort(allBooks.begin(), allBooks.end(), [](const Book& a, const Book& b) {					  // ��������� ������ �� �������� �����
		return compareByNumber(a, b.GetNumber()); });

	for (int i = 0; i < GetBooksQuantity(); i++) {												  // ����������� ������ ��������� ����
		requiredBook = lower_bound(allBooks.begin(), allBooks.end(), number, compareByNumber);		  // ������� �������� ������� ����� �� ��������
		if (requiredBook != allBooks.end() && requiredBook->GetNumber() == number) {			      // ���� ������� ��������� � ���������
			Book temp(requiredBook->GetName(), requiredBook->GetAuthor(),
				requiredBook->GetPublisher(), requiredBook->GetYear(), requiredBook->GetIsOnStock());
			temp.SetNuber(requiredBook->GetNumber());
			findedList.push_back(temp);														      // ��������� ��������� ����� � ������
			allBooks.erase(requiredBook);														  // ������� ��������� ����� �� ������ ����, ����� �� ����������
		}																						  // �� ��� �����
		else
			break;

	}
	return findedList;
}


// ������� ����� �� ������
vector<Book> FindBookAuthor(string& author, vector<Book> allBooks) {

	author = Correcter(author);
	auto requiredBook = lower_bound(allBooks.begin(), allBooks.end(), author, compareByAuthor);    // ������� �������� ������� ����� �� ��������
	vector<Book> findedList;                                                                       // ������ ��������� ����


	sort(allBooks.begin(), allBooks.end(), [](const Book& a, const Book& b) {                     // ��������� ������ �� �������� �����
		return compareByAuthor(a, b.GetAuthor()); });

	for (int i = 0; i < GetBooksQuantity(); i++) {												  // ����������� ������ ��������� ����
		requiredBook = lower_bound(allBooks.begin(), allBooks.end(), author, compareByAuthor);    // ������� �������� ������� ����� �� ��������
		if (requiredBook != allBooks.end() && requiredBook->GetAuthor() == author) {			  // ���� ������� ��������� � ���������
			Book temp(requiredBook->GetName(), requiredBook->GetAuthor(),
				requiredBook->GetPublisher(), requiredBook->GetYear(), requiredBook->GetIsOnStock());
			temp.SetNuber(requiredBook->GetNumber());
			findedList.push_back(temp);														      // ��������� ��������� ����� � ������
			allBooks.erase(requiredBook);														  // ������� ��������� ����� �� ������ ����, ����� �� ����������
		}																						  // �� ��� �����
		else
			break;
	}
	return findedList;
}


// ������ ��� ����� � ������ ����������, � ������ ���� ����������
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


// ������� �����
void DeleteBook(vector<Book> required, vector<Book> allBooks) {

	vector<Book> allBooksNew;

	if (required.empty()) {											// ���������, ������� �� ���� ���� �����
		cout << "\n��������� ����� �� �������.";
		return;
	}

	short deletedBook;												// ������� ����������� ���������� � ������
	int bookQuantuty = GetBooksQuantity();

	for (int i = 0; i < required.size(); i++) {						// ������� ���������� � ��������� ������
		cout << "\n����� �" << i + 1;
		required[i].GetInfo();
	}

	cout << "\n������� " << required.size() << " ����. ����� �� ��������� ���� �� ������ �������? \n";
	cin >> deletedBook;												// ������������ �������� ����� ����� �������

	int deletedBookNumber = required[deletedBook-1].GetNumber();	// �������� ����� ��������� �����
	auto requiredBook = lower_bound(allBooks.begin(), allBooks.end(), deletedBookNumber, compareByNumber);   //���� ����� � ����� �������

	allBooks.erase(requiredBook);									// ������� ����� �� ������ ������ � ����������� ������
	allBooks.shrink_to_fit();

	ofstream booksfile("books.txt");
	ofstream quantityfile("BookQuantity.txt", ios::out);
	if (booksfile.is_open() && quantityfile.is_open()) {
		quantityfile << bookQuantuty - 1;							// ������� ����� ���������� ���� � ���� "BookQuantity.txt"
		quantityfile.close();

		for (int i = 0; i < bookQuantuty-1; i++) {					// ������� � ���� ����������� ������ ����
			AddBook(allBooks[i], allBooksNew);
		}
		allBooks.clear();
		allBooks = allBooksNew;
		booksfile.close();
	}
	else {
		cout << "�� ������� �������� ������.";
		booksfile.close();
		quantityfile.close();
		return;
	}
	cout << endl << "����� ������� �������." << endl;
}


// ���������� ��������� �������
void DisplayInfo() {
	cout << "\n������ ��������� ������:" << "\n1 - �������� ������ ���� ����;" << "\n2 - �������� ���������� ����;" << "\n3 - �������� ����� �����;"
		<< "\n4 - ����� �����;" << "\n5 - ������� �����;" << "\n6 - ������������� �����;\n";
}


void EditBook(vector<Book>& allBooks) {

	int number;
	Book N;
	int bookQuantuty = GetBooksQuantity();
	if (bookQuantuty == 1) 
		bookQuantuty = 2;
	
	vector<Book> allBooksNew;

	cout << "\n������� ����� �����, ������� ������ ��������: ";
	cin >> number;
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	vector<Book> finded = FindBookNumber(number, allBooks);

	if (!finded.empty()) {																	  // ������� ���������, ��� ����� �������
			finded[0].GetInfo();

			auto findedBook = lower_bound(allBooks.begin(), allBooks.end(), number, compareByNumber);   //���� ����� � ����� �������

			cout <<  endl << "��������� ���� ������ ����������:" << endl;
			N.SetValues();
			N.SetNuber(number);



			ofstream booksfile("books.txt");
			if (booksfile.is_open()) {
														
				allBooks.erase(findedBook);
				allBooks.push_back(N);
				allBooks.shrink_to_fit();

				sort(allBooks.begin(), allBooks.end(), [](const Book& a, const Book& b) {	// ��������� ������ �� �������� �����
					return compareByNumber(a, b.GetNumber()); });

				for (int i = 0; i < bookQuantuty; i++) {									// ������� � ���� ����������� ������ ����
					AddBook(allBooks[i], allBooksNew);
				}
				allBooks.clear();
				allBooks = allBooksNew;
				booksfile.close();

			}
			else {
				cout << "�� ������� �������� ������.";
				booksfile.close();
				return;
			}
			cout << endl << "����� ������� ��������." << endl;
	}
	else {
		cout << "\n����� �\"" << number << "\" �� �������." << endl;					 // ������� ���������, ��� ����� �� �������
		return;
	}


}