#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <iomanip>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <memory>
#include "I_Printable.h"
using namespace std;

class Book: public I_Printable {
    friend ostream& operator<<(std::ostream& os, const unique_ptr<Book>& book);
private:
    int id_;
    static int nextId;
    string title_;
    string author_;
    string genre_;
    bool available_;

protected:
    static set<int> deletedBookNums;
    static int soldBooksInc;
    static int rentedBooksInc;
    static int returnedBooksInc;

public:
    //Book();
    Book(string title, string author, string genre);
    Book(string title, string author, string genre, bool available, int id);
    virtual void print(ostream& os) const override;
    virtual ~Book() {};
    string getTitle() const;
    string getAuthor() const;
    string getGenre() const;
    int getId() const;
    bool getAvailable() const;
    bool rentBook(unique_ptr<Book>& bookPtr);
    bool returnBook(unique_ptr<Book>& bookPtr);
    bool addNewBook(map<int, unique_ptr<Book>>& books);
    bool deleteBook(map<int, unique_ptr<Book>>& books, int id);
    bool buyBook(map<int, unique_ptr<Book>>& books, int id);
    static set<int>& getDeletedBooks();
    string getData() const;
    void saveData(ostream& os) const;

};

#endif