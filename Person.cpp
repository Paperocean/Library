#include "Person.h"

int Person::nextId = 100;
set<int> Person::deletedAdminNums;
set<int> Person::deletedLibrarianNums;
set<int> Person::deletedReaderNums;

Person::Person(string name, string surname, string address, string phone_number, string position, int id)
	:name_{ name }, surname_{ surname }, address_{ address }, phone_number_{ phone_number }, position_{ position }, id_{ id }
{}

std::string Person::getName() const {
    return name_;
}

std::string Person::getSurname() const {
    return surname_;
}

std::string Person::getAddress() const {
    return address_;
}

std::string Person::getPhoneNumber() const {
    return phone_number_;
}

std::string Person::getPosition() const
{
    return position_;
}

int Person::getId() const
{
    return id_;
}

int Person::getLastId(map<int, unique_ptr<Person>>& person, const string& type) const
{
    int lastNum{ 0 };
    for (const auto& p : person) {
        if (p.second->getPosition() == type) {
            lastNum = p.second->getId();
        }
    }
    return lastNum;
}

bool Person::addNewPerson(map<int, unique_ptr<Person>>& person)
{
    for (auto& it : person) {
        if (this->name_ == it.second->getName() && this->surname_ == it.second->getSurname() && this->address_ == it.second->getAddress()) {
            return false;
        }
    }
    return true;
}

bool Person::deletePerson(map<int, unique_ptr<Person>>& person, int id)
{
    for (auto& it : person) {
        if (it.first == id) {
            person.erase(id);
            return true;
        }
    }
    return false;
}

set<int>& Person::getDeletedAdmins()
{
    return deletedAdminNums;
}

set<int>& Person::getDeletedLibrarians()
{
    return deletedLibrarianNums;
}

set<int>& Person::getDeletedReaders()
{
    return deletedReaderNums;
}

ostream& operator<<(ostream& os, const unique_ptr<Person>& person)
{
    person->print(os);
    return os;
}