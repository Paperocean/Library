#include "Librarian.h"

int Librarian::nextId = 100;
int Librarian::soldBooksNum_ = 0;
int Librarian::rentedBooksNum_ = 0;
int Librarian::returnedBooksNum_ = 0;

Librarian::Librarian(string name, string surname, string address, string phone_number, double salary, int id)
	:Person(name, surname, address, phone_number, def_position, id), salary_{ salary }
{}

void Librarian::print(std::ostream& os) const {
    os << "+---------------------------------------+" << std::endl;
    os << "|             [PERSONAL DATA]           |" << std::endl;
    os << "+---------------------------------------+" << std::endl;
    os << "| Position:       " << std::setw(22) << std::left << position_ << "|" << std::endl;
    os << "| Card number:    " << std::setw(22) << std::left << id_ << "|" << std::endl;
    os << "|---------------------------------------|" << std::endl;
    os << "| Name:           " << std::setw(22) << std::left << name_ << "|" << std::endl;
    os << "| Surname:        " << std::setw(22) << std::left << surname_ << "|" << std::endl;
    os << "| Address:        " << std::setw(22) << std::left << address_ << "|" << std::endl;
    os << "| Phone number:   " << std::setw(22) << std::left << phone_number_ << "|" << std::endl;
    os << "| Salary: " << std::setw(30) << std::left << salary_ << "|" << std::endl;
    os << "+---------------------------------------+" << std::endl;
    os << std::endl;
}

// specify books that were sold / rented / returned
string Librarian::makeReport() const
{
    unique_ptr<Book> books;
    string data = books->getData();
    stringstream ss{data};
    ss >> soldBooksNum_ >> rentedBooksNum_ >> returnedBooksNum_;
	return "Sold: " + to_string(soldBooksNum_) + " Rented: " + to_string(rentedBooksNum_) + " Returned: " + to_string(returnedBooksNum_);
}

double Librarian::getSalary() const
{
    return salary_;
}

void Librarian::saveData(ostream& os) const
{
    os << getId() << ";" << getName() << ";" << getSurname() << ";" << getAddress()
        << ";" << getPhoneNumber() << ";" << getSalary() << endl;
}

