#include "Book_Util.h"

void displayBooks(const map<int, unique_ptr<Book>>& books)
{
    cout << "=====================================" << endl;
    cout << "             BOOK LIST               " << endl;
    cout << "=====================================" << endl;

    for (const auto& it : books) {
        if(it.first != 0)
            cout << it.second << endl;
    }
}

bool rentBook(map<int, unique_ptr<Book>>& books, int id)
{
    for (auto& it : books) {
        if (it.first == id) {
            return it.second->rentBook(books[id]);
        }
    }
    return false;
}

bool returnBook(map<int, unique_ptr<Book>>& books, int id)
{
    for (auto& it : books) {
        if (it.first == id) {
            cout << it.second << endl;
            return it.second->returnBook(books[id]);
        }
    }
    return false;
}

bool addNewBook(map<int, unique_ptr<Book>>& books)
{
    string title, author, genre;
    cout << "Title: ";
    cin.ignore();
    getline(cin, title);
    cout << "Author: ";
    getline(cin, author);
    cout << "Genre: ";
    getline(cin, genre);

    if (!books.empty()) {
        for (auto& it : books) {
            if (!it.second->getDeletedBooks().empty()){
                int smallest = *it.second->getDeletedBooks().begin();
                unique_ptr<Book> book = make_unique<Book>( title, author, genre, true, smallest );
                if (book->addNewBook(books)) {
                    books[book->getId()] = move(book);
                    it.second->getDeletedBooks().erase(smallest);
                    return true;
                }
            }
            break;
        }
        unique_ptr<Book> book = make_unique<Book>(title, author, genre);
        if (book->addNewBook(books)) {
            books[book->getId()] = move(book);
            return true;
        }
    }
    return false;
}

bool deleteBook(map<int, unique_ptr<Book>>& books, int id)
{
    for (auto& it : books) {
        if (it.second->deleteBook(books, id)) {
            it.second->getDeletedBooks().insert(id);
            return true;
        }
    }
    return false;
}

bool buyBook(map<int, unique_ptr<Book>>& books, int id)
{
    for (auto& it : books) {
        if (it.second->buyBook(books, id)) {
            return true;
        }
    }
    return false;
}
