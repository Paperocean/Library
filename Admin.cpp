#include "Admin.h"

int Admin::nextId = 1;

Admin::Admin(string name, string surname, string address, string phone_number, double salary, int id)
	:Person(name, surname, address, phone_number, def_position, id), salary_{ salary }
{}

void Admin::print(ostream& os) const
{
    os << "+---------------------------------------+" << std::endl;
    os << "|             [ADMIN DATA]              |" << std::endl;
    os << "+---------------------------------------+" << std::endl;
    os << "| Position:       " << std::setw(22) << std::left << position_ << "|" << std::endl;
    os << "| ID:             " << std::setw(22) << std::left << id_ << "|" << std::endl;
    os << "|---------------------------------------|" << std::endl;
    os << "| Name:           " << std::setw(22) << std::left << name_ << "|" << std::endl;
    os << "| Surname:        " << std::setw(22) << std::left << surname_ << "|" << std::endl;
    os << "| Address:        " << std::setw(22) << std::left << address_ << "|" << std::endl;
    os << "| Phone number:   " << std::setw(22) << std::left << phone_number_ << "|" << std::endl;
    os << "| Salary: " << std::setw(30) << std::left << salary_ << "|" << std::endl;
    os << "+---------------------------------------+" << std::endl;
    os << std::endl;
}

string Admin::makeReport() const
{
    return string();
}

double Admin::getSalary() const
{
    return salary_;
}

void Admin::saveData(ostream& os) const
{
    os << getId() << ";" << getName() << ";" << getSurname() << ";" << getAddress()
        << ";" << getPhoneNumber() << ";" << getSalary() << endl;
}


