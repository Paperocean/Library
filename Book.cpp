#include "Book.h"

int Book::nextId = 1;
set<int> Book::deletedBookNums;
int Book::soldBooksInc = 0;
int Book::rentedBooksInc = 0;
int Book::returnedBooksInc = 0;

Book::Book(string title, string author, string genre)
    : title_{title}, author_{author}, genre_{genre}, id_{nextId++}, available_(true)
{}

Book::Book(string title, string author, string genre, bool available, int id)
    : title_{ title }, author_{ author }, genre_{ genre }, available_{ available }, id_{id}
{}

void Book::print(std::ostream& os) const {
    os << boolalpha;
    os << "+-----------------------------------+" << std::endl;
    os << "|             [BOOK DATA]           |" << std::endl;
    os << "+-----------------------------------+" << std::endl;
    os << "| ID:             " << id_ << std::endl;
    os << "| Title:          " << title_ << std::endl;
    os << "| Author:         " << author_ << std::endl;
    os << "| Genre:          " << genre_ << std::endl;
    os << "| Available:         " << available_ << std::endl;
    os << "+-----------------------------------+" << std::endl;
    os << std::endl;
}

string Book::getTitle() const { return title_; }
string Book::getAuthor() const { return author_; }
string Book::getGenre() const { return genre_; }

int Book::getId() const
{
    return id_;
}

bool Book::getAvailable() const
{
    return available_;
}

bool Book::rentBook(unique_ptr<Book>& book) {
    if (book->available_) {
        rentedBooksInc++;
        book->available_ = false;
        return true;
    }
    return false;
}

bool Book::returnBook(unique_ptr<Book>& book)
{
    if (!book->available_) {
        returnedBooksInc++;
        book->available_ = true;
        return true;
    }
    return false;
}

bool Book::addNewBook(map<int, unique_ptr<Book>>& books)
{
    for (const auto& it : books) {
        if (title_ == it.second->getTitle() && author_ == it.second->getAuthor() && genre_ == it.second->getGenre()) {
            nextId--;
            return false;
        }
    }
    return true;
}

bool Book::deleteBook(map<int, unique_ptr<Book>>& books, int id)
{
    if(books[id]->available_)
        for (auto& it : books) {
            if (it.first == id) {
                books.erase(id);
                return true;
            }
        }
    return false;
}

bool Book::buyBook(map<int, unique_ptr<Book>>& books, int id)
{
    if (books[id]->available_)
        for (auto& it : books) {
            if (it.first == id) {
                soldBooksInc++;
                return true;
            }
        }
    return false;
}

set<int>& Book::getDeletedBooks()
{
    return deletedBookNums;
}

string Book::getData() const
{
    return to_string(soldBooksInc) + " " + to_string(rentedBooksInc) + " " + to_string(returnedBooksInc);
}

void Book::saveData(ostream& os) const
{
    os << getId() << ";" << getTitle() << ";" << getAuthor() << ";" << getGenre() << ";" << (getAvailable() ? "true" : "false") << endl;
}

ostream& operator<<(ostream& os, const unique_ptr<Book>& book)
{
    book->print(os);
    return os;
}
