#include <iomanip>
#include "Reader.h"

int Reader::nextId = 1000;

Reader::Reader(string name, string surname, string address, string phone_number, int rentedBooksNum, int cardNum)
    : Person(name, surname, address, phone_number, def_position, cardNum), rentedBooksNum_{ rentedBooksNum }{}

void Reader::print(std::ostream& os) const {
    os << "+---------------------------------------+" << std::endl;
    os << "|             [PERSONAL DATA]           |" << std::endl;
    os << "+---------------------------------------+" << std::endl;
    os << "| Position:       " << std::setw(18) << std::left << position_ << "|" << std::endl;
    os << "| Card number:    " << std::setw(18) << std::left << id_ << "|" << std::endl;
    os << "|---------------------------------------|" << std::endl;
    os << "| Name:           " << std::setw(18) << std::left << name_ << "|" << std::endl;
    os << "| Surname:        " << std::setw(18) << std::left << surname_ << "|" << std::endl;
    os << "| Address:        " << std::setw(18) << std::left << address_ << "|" << std::endl;
    os << "| Phone number:   " << std::setw(18) << std::left << phone_number_ << "|" << std::endl;
    os << "| Borrowed books: " << std::setw(18) << std::left << rentedBooksNum_ << "|" << std::endl;
    os << "+---------------------------------------+" << std::endl;
    os << std::endl;
}


int Reader::getRentedBooksNumber() const {
    return rentedBooksNum_;
}

string Reader::makeReport() const
{
    return string();
}

void Reader::saveData(ostream& os) const
{
    os << getId() << ";" << getName() << ";" << getSurname() << ";" << getAddress()
        << ";" << getPhoneNumber() << ";" << getRentedBooksNumber() << endl;
}
