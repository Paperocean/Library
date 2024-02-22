#ifndef BOOK_UTIL_H
#define BOOK_UTIL_H

#include <vector>
#include <map>
#include <string>
#include <memory>
#include "Book.h"

void displayBooks(const map<int, unique_ptr<Book>>& book);
bool rentBook(map<int, unique_ptr<Book>>& books, int id);
bool returnBook(map<int, unique_ptr<Book>>& books, int id);
bool addNewBook(map<int, unique_ptr<Book>>& books);
bool deleteBook(map<int, unique_ptr<Book>>& books, int id);
bool buyBook(map<int, unique_ptr<Book>>& books, int id);

#endif // !BOOK_UTIL_H
