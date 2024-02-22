#ifndef LIBRARIAN_H
#define LIBRARIAN_H

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include "Person.h"
#include "Book.h"

using namespace std;
class Librarian : public Person{
private:
	static constexpr const char* def_position = "LIBRARIAN";
	static constexpr const double def_salary = 3000.0;
	static int nextId;

protected:
	static int soldBooksNum_, rentedBooksNum_, returnedBooksNum_;
	double salary_;
	vector<Book> books;

public:
	Librarian(string name, string surname, string address, string phone_number, 
		double salary = def_salary, int id = nextId++);
	virtual ~Librarian() {};
	virtual void print(ostream& os) const override;
	virtual string makeReport() const override;
	double getSalary() const;
	virtual void saveData(ostream& os) const override;

};

#endif // !_LIBRARIAN_H