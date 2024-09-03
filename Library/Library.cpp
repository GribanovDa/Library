#include "funcs.h"
#include <windows.h>

int main()
{
    setlocale(LC_ALL, "Russian_Russia.1251");
    SetConsoleCP(1251);                                 // Устанавливаем кодировку ввода (CP1251)
    SetConsoleOutputCP(1251);                           // Устанавливаем кодировку вывода (CP1251)
    
    

    DisplayInfo();
    vector<Book> allBooks = GetAllFromFile();           // Список из всех книг
    Book newBook;
    string bookName, bookAuthor, choice, quit;
    int bookNumber, ch;
    vector<Book> required, finded;
    bool exit = true;
    


    while (exit) {
        cout << endl << "Список возможных команд - цифра 7." << endl << "Введите необходимую команду: ";
        getline(cin, choice);
        if (choice != "1" && choice != "2" && choice != "3" && choice != "4" && choice != "5" && choice != "6" && choice != "7" && choice != "8" && choice != "0") {
            system("cls");
            cout << endl << "Неизвестная команда!" << endl;
            DisplayInfo();
        }
        else {
            ch = stoi(choice);
            switch (ch)
            {
            case 1:
                system("cls");
                cout << "Список книг:\n";
                for (int i = 0; i < GetBooksQuantity(); i++) {
                    allBooks[i].GetInfo();
                }
                break;
            case 2:
                system("cls");
                cout << "\nКниг в списке - " << GetBooksQuantity();
                break;
            case 3:
                system("cls");
                newBook.SetValues();
                AddNewBook(newBook, allBooks);
                cin.ignore();
                break;
            case 4:
                system("cls");
                cout << "\nКнигу можно найти по названию, по автору и по номеру.\nИскать по названию введите - 1.\nИскать по автору - 2.\nИскать по номеру - 3.\nВведите нужную цифру\n";
                cin >> ch;
                switch (ch)
                {
                case 1:
                    system("cls");
                    cout << "\nВведите название книги\n";
                    cin.ignore();
                    getline(cin, bookName);
                    finded = FindBookName(bookName, allBooks);
                    if (!finded.empty()) {																	  // Выводим сообщение, что книга найдена
                        cout << endl << "Книга найдена! \n";
                        for (int i = 0; i < finded.size(); i++) {											  // Выводим список найденных книг
                            finded[i].GetInfo();
                        }
                    }
                    else {
                        cout << "\nКнига \"" << bookName << "\" не найдена." << endl;						  // Выводим сообщение, что книга не найдена
                    }
                    break;
                case 2:
                    system("cls");
                    cout << "\nВведите автора книги\n";
                    cin.ignore();
                    getline(cin, bookAuthor);
                    finded = FindBookAuthor(bookAuthor, allBooks);
                    if (!finded.empty()) {																	  // Выводим сообщение, что книга найдена
                        cout << endl << "Книга найдена! \n";
                        for (int i = 0; i < finded.size(); i++) {											  // Выводим список найденных книг
                            finded[i].GetInfo();
                        }
                    }
                    else {
                        cout << "\nКнига \"" << bookAuthor << "\" не найдена." << endl;						  // Выводим сообщение, что книга не найдена
                    }
                    break;
                case 3:
                    system("cls");
                    cout << "\nВведите номер книги\n";
                    cin.ignore();
                    getline(cin, bookName);
                    bookNumber = stoi(bookName);
                    finded = FindBookNumber(bookNumber, allBooks);
                    if (!finded.empty()) {																	  // Выводим сообщение, что книга найдена
                        cout << endl << "Книга найдена! \n";
                        for (int i = 0; i < finded.size(); i++) {											  // Выводим список найденных книг
                            finded[i].GetInfo();
                        }
                    }
                    else {
                        cout << "\nКнига c номером \"" << bookNumber << "\" не найдена." << endl;			  // Выводим сообщение, что книга не найдена
                    }
                    break;
                }
                break;
            case 5:
                system("cls");
                cout << "\nКнигу можно удалить по названию, по автору и по номеру.\nУдалить по названию введите - 1.\nУдалить по автору - 2.\nУдалить по номеру - 3.\nВведите нужную цифру\n";
                cin >> ch;
                switch (ch)
                {
                case 1:
                    system("cls");
                    cout << "\nВведите название книги\n";
                    cin.ignore();
                    getline(cin, bookName);
                    required = FindBookName(bookName, allBooks);
                    DeleteBook(required, allBooks);
                    cin.ignore();
                    break;
                case 2:
                    system("cls");
                    cout << "\nВведите автора книги\n";
                    cin.ignore();
                    getline(cin, bookAuthor);
                    required = FindBookAuthor(bookAuthor, allBooks);
                    DeleteBook(required, allBooks);
                    cin.ignore();
                    break;
                case 3:
                    system("cls");
                    cout << "\nВведите номер книги\n";
                    cin.ignore();
                    cin >> bookNumber;
                    required = FindBookNumber(bookNumber, allBooks);
                    DeleteBook(required, allBooks);
                    cin.ignore();
                    break;
                }
                break;
            case 7:
                system("cls");
                DisplayInfo();
                break;
            case 6:
                system("cls");
                EditBook(allBooks);
                cin.ignore();
                break;
            case 0:
                system("cls");
                exit = false;
                break;
            default:
                system("cls");
                cout << endl << "Неизвестная команда!" << endl;
                DisplayInfo();
            }
        }
    }
}

