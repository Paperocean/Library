#include <vector>
#include <iostream>
#include <memory>
#include <cctype>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <cctype>
#include <fstream>
#include <sstream>

#include "Person.h"
#include "Person_Util.h"
#include "Reader.h"
#include "Librarian.h"
#include "Admin.h"
#include "Book.h"
#include "Book_Util.h"

using namespace std;
const string adminFile = "adminData.csv";
const string librarianFile = "librarianData.csv";
const string readerFile = "readerData.csv";
const string userDeletedNums = "deletedUserNums.txt";
const string bookFile = "bookData.csv";
const string bookDeletedNums = "deletedBookNums.txt";

void clearScreen() {
    system("cls");
}
void displayMainMenu() {
    std::cout << " __  __       _       " << std::endl;
    std::cout << "|  \\/  | __ _(_)_ __  " << std::endl;
    std::cout << "| |\\/| |/ _` | | '_ \\ " << std::endl;
    std::cout << "| |  | | (_| | | | | |" << std::endl;
    std::cout << "|_|  |_|\\__,_|_|_| |_|" << std::endl;
    cout << endl;
    cout << "Choose who you are:" << endl;
    cout << "A - Admin" << endl;
    cout << "L - Librarian" << endl;
    cout << "R - Reader" << endl;
    cout << "=========================================" << endl;
}
void displayAdminMenu() {
    std::cout << " ____                  _      " << std::endl;
    std::cout << "|  _ \\ ___  ___  _ __ | | ___ " << std::endl;
    std::cout << "| |_) / _ \\/ _ \\| '_ \\| |/ _ \\" << std::endl;
    std::cout << "|  __/  __/ (_) | |_) | |  __/" << std::endl;
    std::cout << "|_|   \\___|\\___/| .__/|_|\\___|" << std::endl;
    std::cout << "                |_|            " << std::endl;
    cout << endl;
    cout << "L - Managing librarians" << endl;
    cout << "R - Managing readers" << endl;
    cout << "U - Add a new user" << endl;
    cout << "=========================================" << endl;
    std::cout << " ____              _        " << std::endl;
    std::cout << "| __ )  ___   ___ | | _____ " << std::endl;
    std::cout << "|  _ \\ / _ \\ / _ \\| |/ / __|" << std::endl;
    std::cout << "| |_) | (_) | (_) |   <\\__ \\" << std::endl;
    std::cout << "|____/ \\___/ \\___/|_|\\_\\___/" << std::endl;
    cout << endl;
    cout << "N - Navigate through the library" << endl;
    cout << "B - Rent a book" << endl;
    cout << "V - Return a book" << endl;
    cout << "A - Add a new book" << endl;
    cout << "D - Delete a book" << endl;
    cout << "=========================================" << endl;
}
void displayManagingLMenu() {
    std::cout << " _     _ _                    _                 " << std::endl;
    std::cout << "| |   (_) |__  _ __ __ _ _ __(_) __ _ _ __  ___ " << std::endl;
    std::cout << "| |   | | '_ \\| '__/ _` | '__| |/ _` | '_ \\/ __|" << std::endl;
    std::cout << "| |___| | |_) | | | (_| | |  | | (_| | | | \\__ \\" << std::endl;
    std::cout << "|_____|_|_.__/|_|  \\__,_|_|  |_|\\__,_|_| |_|___/" << std::endl;
    std::cout << std::endl;
    std::cout << "S - Show librarians" << std::endl;
    std::cout << "X - Delete a librarian" << std::endl;
    std::cout << "F - Find out if all numbers are correct" << std::endl;
    std::cout << "=========================================" << std::endl;
}
void displayManagingRMenu() {
    std::cout << " ____                _               " << std::endl;
    std::cout << "|  _ \\ ___  __ _  __| | ___ _ __ ___ " << std::endl;
    std::cout << "| |_) / _ \\/ _` |/ _` |/ _ \\ '__/ __|" << std::endl;
    std::cout << "|  _ <  __/ (_| | (_| |  __/ |  \\__ \\" << std::endl;
    std::cout << "|_| \\_\\___|\\__,_|\\__,_|\\___|_|  |___/" << std::endl;
    cout << endl;
    cout << "S - Show readers" << endl;
    cout << "X - Delete a reader" << endl;
    cout << "F - Find out if all numbers are correct" << endl;
    cout << "=========================================" << endl;
}
void displayLibrarianMenu() {
    std::cout << " ____              _        " << std::endl;
    std::cout << "| __ )  ___   ___ | | _____ " << std::endl;
    std::cout << "|  _ \\ / _ \\ / _ \\| |/ / __|" << std::endl;
    std::cout << "| |_) | (_) | (_) |   <\\__ \\" << std::endl;
    std::cout << "|____/ \\___/ \\___/|_|\\_\\___/" << std::endl;
    cout << endl;
    cout << "N - Navigate through the library" << endl;
    cout << "B - Rent a book" << endl;
    cout << "R - Return a book" << endl;
    cout << "S - Sell a book" << endl;
    cout << "A - Add a new book" << endl;
    cout << "D - Delete a book" << endl;
    cout << "M - Make a report" << endl;
    cout << "=========================================" << endl;
}
void displayReaderMenu() {
    std::cout << " ____              _        " << std::endl;
    std::cout << "| __ )  ___   ___ | | _____ " << std::endl;
    std::cout << "|  _ \\ / _ \\ / _ \\| |/ / __|" << std::endl;
    std::cout << "| |_) | (_) | (_) |   <\\__ \\" << std::endl;
    std::cout << "|____/ \\___/ \\___/|_|\\_\\___/" << std::endl;
    //cout << "BOOKS MENU" << endl;
    cout << endl;
    cout << "N - Navigate through the library" << endl;
    cout << "B - Rent a book" << endl;
    cout << "R - Return a book" << endl;
    cout << "X - Buy a book" << endl;
    cout << "=========================================" << endl;
}
string stringUpper(const string& str) {
    string temp{};
    for (const char& c : str) {
        temp += toupper(c);
    }
    return temp;
}

void loadBookData(map<int, unique_ptr<Book>>& books) {
    ifstream in_file;

    in_file.open(bookFile);
    if (in_file) {
        int id;
        string title, author, genre, available_str;
        bool available;
        string line;
        getline(in_file, line);
        while (getline(in_file, line)) {
            stringstream ss(line);
            string field;
            if (getline(ss, field, ';')) {
                id = stoi(field);
                getline(ss, title, ';');
                getline(ss, author, ';');
                getline(ss, genre, ';');
                getline(ss, available_str, ';');
                available = (available_str == "true");

                books[id] = make_unique<Book>( title,author,genre,available,id );
            }
        }
    }
    else {
        cout << "File doesn't exist" << endl;
    }
    in_file.close();

    in_file.open(bookDeletedNums);
    if (in_file) {
        int num;
        for (auto& b : books) {
            while (in_file >> num) {
                b.second->getDeletedBooks().insert(num);
            }
            break;
        }
    }
    else {
        cout << "Creating file with deleted books..." << endl;
        ofstream new_file(bookDeletedNums);
        new_file.close();
    }
    in_file.close();
}
void saveBookData(map<int, unique_ptr<Book>>& books) {
    ofstream out_file;

    out_file.open(bookFile);
    out_file << "Id;Title;Author;Genre;Available" << endl;
    for (const auto& b : books) {
        b.second->saveData(out_file);
    }
    out_file.close();

    out_file.open(bookDeletedNums);
    for (const auto& b : books) {
        for (auto it = b.second->getDeletedBooks().begin(); it != b.second->getDeletedBooks().end(); it++) {
            out_file << *it << endl;
        }
        break;
    }
    out_file.close();
}
void loadUserData(map<int, unique_ptr<Person>>& person) {
    ifstream in_file;

    in_file.open(readerFile);
    if (in_file) {
        int id, rented_books = 0;
        string name, surname, address, phone_number, line;
        getline(in_file, line);
        while (getline(in_file, line)) {
            stringstream ss(line);
            string field;
            if (getline(ss, field, ';')) {
                id = stoi(field);
                getline(ss, name, ';');
                getline(ss, surname, ';');
                getline(ss, address, ';');
                getline(ss, phone_number, ';');
                if (getline(ss, field, ';')) {
                    rented_books = stoi(field);
                }
                person[id] = make_unique<Reader>(name, surname, address, phone_number, rented_books, id);
            }
        }
    }
    else {
        cout << "Reader file doesn't exist" << endl;
    }
    in_file.close();

    in_file.open(librarianFile);
    if (in_file) {
        int id, rented_books = 0;
        string name, surname, address, phone_number;
        double salary = 2000.0;
        string line;
        getline(in_file, line);
        while (getline(in_file, line)) {
            stringstream ss(line);
            string field;
            if (getline(ss, field, ';')) {
                id = stoi(field);
                getline(ss, name, ';');
                getline(ss, surname, ';');
                getline(ss, address, ';');
                getline(ss, phone_number, ';');
                if (getline(ss, field, ';')) {
                    salary = stod(field);
                }
                person[id] = make_unique<Librarian>(name, surname, address, phone_number, salary, id);
            }
        }
    }
    else {
        cout << "Librarian file doesn't exist" << endl;
    }
    in_file.close();

    in_file.open(adminFile);
    if (in_file) {
        int id, rented_books = 0;
        string name, surname, address, phone_number;
        double salary = 2000.0;
        string line;
        getline(in_file, line);
        while (getline(in_file, line)) {
            stringstream ss(line);
            string field;
            if (getline(ss, field, ';')) {
                id = stoi(field);
                getline(ss, name, ';');
                getline(ss, surname, ';');
                getline(ss, address, ';');
                getline(ss, phone_number, ';');
                if (getline(ss, field, ';')) {
                    salary = stod(field);
                }
                person[id] = make_unique<Admin>(name, surname, address, phone_number, salary, id);
            }
        }
    }
    else {
        cout << "Admin file doesn't exist" << endl;
    }
    in_file.close();

    in_file.open(userDeletedNums);
    if (in_file) {
        string line;
        for (auto& p : person) {
            while (getline(in_file, line)) {
                stringstream ss{ line };
                string field;
                if (getline(ss, field, ';')) {
                    if (field == "ADMIN") {
                        int num;
                        while (ss >> num) {
                            p.second->getDeletedAdmins().insert(num);
                        }
                    }
                    else if (field == "LIBRARIAN") {
                        int num;
                        while (ss >> num) {
                            p.second->getDeletedLibrarians().insert(num);
                        }
                    }
                    else if (field == "READER") {
                        int num;
                        while (ss >> num) {
                            p.second->getDeletedReaders().insert(num);
                        }
                    }
                }
            }
            break;
        }
    }
    else {
        cout << "Creating file with deleted users..." << endl;
        ofstream new_file(userDeletedNums);
        new_file.close();
    }
    in_file.close();
}
void saveUserData(map<int, unique_ptr<Person>>& person) {
    ofstream out_file;

    out_file.open(readerFile);
    out_file << "Id;Name;Surname;Address;Phone number;Rented books" << endl;
    out_file.close();

    out_file.open(adminFile);
    out_file << "Id;Name;Surname;Address;Phone number;Salary" << endl;
    out_file.close();

    out_file.open(librarianFile);
    out_file << "Id;Name;Surname;Address;Phone number;Salary" << endl;
    out_file.close();

    for (const auto& p : person) {
        if (p.second->getPosition() == "READER") {
            out_file.open(readerFile, ios::app);
            if (out_file) {
                p.second->saveData(out_file);
            }
            out_file.close();
        }
        else if (p.second->getPosition() == "LIBRARIAN") {
            out_file.open(librarianFile, ios::app);
            if (out_file) {
                p.second->saveData(out_file);
            }
            out_file.close();
        }
        else if (p.second->getPosition() == "ADMIN") {
            out_file.open(adminFile, ios::app);
            if (out_file) {
                p.second->saveData(out_file);
            }
            out_file.close();
        }
    }

    out_file.open(userDeletedNums);
    out_file << "ADMIN; ";
    for (const auto& p : person) {
        for (auto num : p.second->getDeletedAdmins()) {
            out_file << num << " ";
        }
        break;
    }
    out_file << "\nLIBRARIAN; ";
    for (const auto& p : person) {
        for (auto num : p.second->getDeletedLibrarians()) {
            out_file << num << " ";
        }
        break;
    }
    out_file << "\nREADER; ";
    for (const auto& p : person) {
        for (auto num : p.second->getDeletedReaders()) {
            out_file << num << " ";
        }
        break;
    }
    out_file.close();
}

int main() {
    map<int, unique_ptr<Person>> person;
    map<int, unique_ptr<Book>> books;
    
    loadUserData(person);
    loadBookData(books);
    
    displayMainMenu();
    char choice;
    cout << "Enter your choice: ";
    cin >> choice;
    choice = toupper(choice);
    if (choice == 'A') {
        clearScreen();
        char action{};
        char action2{};
        do {
            string type{};
            char c{};
            int num{};
            for (const auto& p : person) {
                if (p.second->getPosition() == "ADMIN")
                    cout << *p.second << endl;
            }
            displayAdminMenu();
            cout << "Q - Quit" << endl;
            cout << "Enter an option: ";
            cin >> action;
            action = toupper(action);
            switch (action) {
            case 'L':
                clearScreen();
                do {
                    displayManagingLMenu();
                    cout << "Q - Quit" << endl;
                    cout << "Enter an option: ";
                    cin >> action2;
                    action2 = toupper(action2);
                    switch (action2) {
                    case 'S':
                        clearScreen();
                        do {
                            displayLibrarians(person);
                            cout << "To leave type 'Q': ";
                            cin >> c;
                            c = toupper(c);
                        } while (c != 'Q');
                        clearScreen();
                        break;
                    case 'X':
                        clearScreen();
                        cout << "Which user you want to delete? ";
                        cin >> num;
                        if (person.find(num) != person.end()) {
                            if (person.find(num)->second->getPosition() == "LIBRARIAN") {
                                if (deletePerson(person, num)) {
                                    clearScreen();
                                    cout << "\n*User " << num << " deleted* \n" << endl;
                                }
                                else {
                                    clearScreen();
                                    cout << "\n*The user is no longer here!* \n" << endl;
                                }
                            }
                            else {
                                cout << "You can only delete librarian here!" << endl;
                            }
                        }
                        else {
                            cout << "Number out of scope" << endl;
                        }
                        break;
                    case 'F':
                        clearScreen();
                        do {
                            validatePhoneNumber(person, type);
                            cout << "To leave type 'Q': ";
                            cin >> c;
                            c = toupper(c);
                        } while (c != 'Q');
                        clearScreen();
                        break;
                    case 'Q':
                        break;
                    default:
                        clearScreen();
                        cout << "\nInvalid option. Please enter a valid option.\n" << endl;
                        break;
                    }
                } while (action2 != 'Q');
                clearScreen();
                break;
            case 'R':
                clearScreen();
                do {
                    displayManagingRMenu();
                    cout << "Q - Quit" << endl;
                    cout << "Enter an option: ";
                    cin >> action2;
                    action2 = toupper(action2);
                    switch (action2) {
                    case 'S':
                        clearScreen();
                        do {
                            displayReaders(person);
                            cout << "To leave type 'Q': ";
                            cin >> c;
                            c = toupper(c);
                        } while (c != 'Q');
                        clearScreen();
                        break;
                    case 'X':
                        clearScreen();
                        cout << "Which user you want to delete? ";
                        cin >> num;
                        if (person.find(num) != person.end()) {
                            if (person.find(num)->second->getPosition() == "READER") {
                                if (deletePerson(person, num)) {
                                    clearScreen();
                                    cout << "\n*User " << num << " deleted* \n" << endl;
                                }
                                else {
                                    clearScreen();
                                    cout << "\n*The user is no longer here!* \n" << endl;
                                }
                            }
                            else {
                                cout << "You can only delete librarian here!" << endl;
                            }
                        }
                        else {
                            cout << "Number out of scope" << endl;
                        }
                        break;
                    case 'F':
                        clearScreen();
                        do {
                            validatePhoneNumber(person, type);
                            cout << "To leave type 'Q': ";
                            cin >> c;
                            c = toupper(c);
                        } while (c != 'Q');
                        clearScreen();
                        break;
                    case 'Q':
                        break;
                    default:
                        clearScreen();
                        cout << "\nInvalid option. Please enter a valid option.\n" << endl;
                        break;
                    }
                } while (action2 != 'Q');
                clearScreen();
                break;
            case 'U':
                clearScreen();
                cout << "Welcome to the Library Management System!" << endl;
                cout << "=========================================" << endl;
                cout << "Write the type of user to add:" << endl;
                cout << "* Librarian" << endl;
                cout << "* Reader" << endl;
                cout << "* Admin" << endl;
                cout << "=========================================" << endl;
                cout << "Type: ";
                cin >> type;
                type = stringUpper(type);
                if (type == "READER") {
                    if (addNewPerson(person, type)) {
                        clearScreen();
                        cout << "\n*New reader added*\n" << endl;
                    }
                }
                else if (type == "LIBRARIAN") {
                    if (addNewPerson(person, type)) {
                        clearScreen();
                        cout << "\n*New librarian added*\n" << endl;
                    }
                    else {
                        clearScreen();
                        cout << "\n*ERROR*\n" << endl;
                    }
                }
                else if (type == "ADMIN") {
                    if (addNewPerson(person, type)) {
                        clearScreen();
                        cout << "\n*New admin added*\n" << endl;
                    }
                    else {
                        clearScreen();
                        cout << "\n*ERROR*\n" << endl;
                    }
                }
                else {
                    clearScreen();
                    cout << "That type doesn't exist!" << endl;
                }
                break;
            case 'N':
                clearScreen();
                do {
                    displayBooks(books);
                    cout << "To leave type 'Q': ";
                    cin >> c;
                    c = toupper(c);
                } while (c != 'Q');
                clearScreen();
                break;
            case 'B':
                clearScreen();
                cout << "Which book you want to rent? ";
                cin >> num;
                if (rentBook(books, num)) {
                    cout << "\n*Book " << num << " rented* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*Book already rented!* \n" << endl;
                }
                break;
            case 'V':
                clearScreen();
                cout << "Which book you want to return? ";
                cin >> num;
                if (returnBook(books, num)) {
                    clearScreen();
                    cout << "\n*Book " << num << " returned* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*Book already returned!* \n" << endl;
                }
                break;
            case 'A':
                clearScreen();
                if (addNewBook(books)) {
                    clearScreen();
                    cout << "\n*Book added* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*Book already added!* \n" << endl;
                }
                break;
            case 'D':
                clearScreen();
                cout << "Which book you want to delete? ";
                cin >> num;
                if (deleteBook(books, num)) {
                    clearScreen();
                    cout << "\n*Book deleted* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*The book is no longer here!* \n" << endl;
                }
                break;
            case 'Q':
                break;
            default:
                clearScreen();
                cout << "\nInvalid option. Please enter a valid option.\n" << endl;
                break;
            }
        } while (action != 'Q');
    }
    else if (choice == 'L') {
        clearScreen();
        char action{};
        do {
            string type{};
            char c{};
            int num{};
            displayLibrarianMenu();
            cout << "Q - Quit" << endl;
            cout << "Enter an option: ";
            cin >> action;
            action = toupper(action);
            switch (action) {
            case 'N':
                clearScreen();
                do {
                    displayBooks(books);
                    cout << "To leave type 'Q': ";
                    cin >> c;
                    c = toupper(c);
                } while (c != 'Q');
                clearScreen();
                break;
            case 'B':
                clearScreen();
                cout << "Which book you want to rent? ";
                cin >> num;
                if (rentBook(books, num)) {
                    cout << "\n*Book " << num << " rented* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*Book already rented!* \n" << endl;
                }
                break;
            case 'R':
                clearScreen();
                cout << "Which book you want to return? ";
                cin >> num;
                if (returnBook(books, num)) {
                    clearScreen();
                    cout << "\n*Book " << num << " returned* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*Book already returned!* \n" << endl;
                }
                break;
            case 'S':
                clearScreen();
                cout << "Which book you want to sell? ";
                cin >> num;
                if (buyBook(books, num)) {
                    clearScreen();
                    cout << "\n*Book \""<< books[num]->getTitle() << "\" sold*\n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*The book is no longer here!* \n" << endl;
                }
                break;
            case 'A':
                clearScreen();
                if (addNewBook(books)) {
                    clearScreen();
                    cout << "\n*Book added* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*Book already added!* \n" << endl;
                }
                break;
            case 'D':
                clearScreen();
                cout << "Which book you want to delete? ";
                cin >> num;
                if (deleteBook(books, num)) {
                    clearScreen();
                    cout << "\n*Book deleted* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*The book is no longer here!* \n" << endl;
                }
                break;
            case 'M':
                clearScreen(); 
                cout << "------------ Report ------------" << endl;
                if (!person.empty()) {
                    for (const auto& it : person) {
                        if (it.second->getPosition() == "LIBRARIAN") {
                            cout << it.second->makeReport() << endl;
                            break;
                        }
                    }
                }
                else {
                    cout << "No librarians in the system." << endl;
                }
                break;
            case 'Q':
                break;
            default:
                clearScreen();
                cout << "\nInvalid option. Please enter a valid option.\n" << endl;
                break;
            }
        } while (action != 'Q');
    }
    else if (choice == 'R') {
        clearScreen();
        char action{};
        do {
            string type{};
            char c{};
            int num{};
            displayReaderMenu();
            cout << "Q - Quit" << endl;
            cout << "Enter an option: ";
            cin >> action;
            action = toupper(action);
            switch (action) {
            case 'N':
                clearScreen();
                do {
                    displayBooks(books);
                    cout << "To leave type 'Q': ";
                    cin >> c;
                    c = toupper(c);
                } while (c != 'Q');
                clearScreen();
                break;
            case 'B':
                clearScreen();
                cout << "Which book you want to rent? ";
                cin >> num;
                if (rentBook(books, num)) {
                    cout << "\n*Book " << num << " rented* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*Book already rented!* \n" << endl;
                }
                break;
            case 'R':
                clearScreen();
                cout << "Which book you want to return? ";
                cin >> num;
                if (returnBook(books, num)) {
                    clearScreen();
                    cout << "\n*Book " << num << " returned* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*Book already returned!* \n" << endl;
                }
                break;
            case 'X':
                clearScreen();
                cout << "Which book you want to buy? ";
                cin >> num;
                if (buyBook(books, num)) {
                    clearScreen();
                    cout << "\n*Book bought* \n" << endl;
                }
                else {
                    clearScreen();
                    cout << "\n*The book is no longer here!* \n" << endl;
                }
                break;
            case 'Q':
                break;
            default:
                clearScreen();
                cout << "\nInvalid option. Please enter a valid option.\n" << endl;
                break;
            }
        } while (action != 'Q');
    }
    else {
        cout << "This class doesnt exist" << endl;
    }

    saveUserData(person);
    saveBookData(books);
}
