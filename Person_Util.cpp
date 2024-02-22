#include "Person_Util.h"
using namespace std;

void display(const map<int, unique_ptr<Person>>& person) {
    cout << "=========================================" << endl;
    cout << "                 USER LIST               " << endl;
    cout << "=========================================" << endl;

    for (const auto& it : person) {
        cout << setw(20) << left << "Type: " << it.first << endl;
        cout << "-------------------------------------" << endl;
        if (it.second->getId() != 0) {
            cout << it.second << endl;
        }
    }
}

void displayReaders(map<int, unique_ptr<Person>>& person)
{
    cout << "=========================================" << endl;
    cout << "                 USER LIST               " << endl;
    cout << "=========================================" << endl;

    for (const auto& it : person) {
        if (it.first >= 1000)
            cout << *it.second << endl;
    }
}

void displayLibrarians(map<int, unique_ptr<Person>>& person)
{
    cout << "=========================================" << endl;
    cout << "                 USER LIST               " << endl;
    cout << "=========================================" << endl;

    for (const auto& it : person) {
        if (it.first >= 100 && it.first < 1000)
            cout << *it.second << endl;
    }
}

void displayAdmins(map<int, unique_ptr<Person>>& person)
{
    cout << "=========================================" << endl;
    cout << "                 ADMIN LIST              " << endl;
    cout << "=========================================" << endl;

    for (const auto& it : person) {
        if (it.first > 0 && it.first < 100)
            cout << *it.second << endl;
    }
}

void validatePhoneNumber(const map<int, unique_ptr<Person>>& person, const string& type) {
    cout << "\nPeople with invalid phone numbers:" << endl;
    for (const auto& it : person) {
        if (it.second->getPosition() == type) {
            string phoneNumber = it.second->getPhoneNumber();
            if (phoneNumber.size() < 8 || phoneNumber.size() > 9) {
                cout << *it.second << endl;
            }
        }
    }
}

bool validatePhoneNumber(const string& phone_number)
{
    return phone_number.size() >= 8 && phone_number.size() <= 9;
}

bool deletePerson(map<int, unique_ptr<Person>>& person, int id)
{
    if (!person.empty())
        for (auto& it : person) {
            if (it.first == id) {
                if (it.second->getPosition() == "READER" && it.second->deletePerson(person, id)) {
                    it.second->getDeletedReaders().insert(id);
                    return true;
                }
                else if (it.second->getPosition() == "LIBRARIAN" && it.second->deletePerson(person, id)) {
                    it.second->getDeletedLibrarians().insert(id);
                    return true;
                }
                else if (it.second->getPosition() == "ADMIN" && it.second->deletePerson(person, id)) {
                    it.second->getDeletedAdmins().insert(id);
                    return true;
                }
            }
        }
    return false;
}

bool addNewPerson(map<int, unique_ptr<Person>>& person, const string& type)
{
    string name{}, surname{}, address{}, phone_number{};
    int rented_books{};
    double salary{};

    try {
        cout << "Name: ";
        cin >> name;
        if (cin.fail()) {
            throw runtime_error{ "Invalid input for name" };
        }
        cout << "Surname: ";
        cin >> surname;
        if (cin.fail()) {
            throw runtime_error{ "Invalid input for surname" };
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Address: ";
        getline(cin, address);
        if (cin.fail()) {
            throw runtime_error{ "Invalid input for address" };
        }
        cout << "Phone number: ";
        getline(cin, phone_number);
        if (cin.fail() || !validatePhoneNumber(phone_number)) {
            throw runtime_error{ "Invalid input for phone number" };
        }
    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    for (auto& it : person) {
        if (type == "READER") {
            try {
                cout << "Rented books: ";
                cin >> rented_books;
                if (cin.fail()) {
                    throw runtime_error{ "Invalid input for rented books" };
                }
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            if (!it.second->getDeletedReaders().empty()) {
                int smallest = *it.second->getDeletedReaders().begin();
                Reader r{ name, surname, address, phone_number, rented_books, smallest };
                if (r.addNewPerson(person)) {
                    person[smallest] = make_unique<Reader>(r);
                    it.second->getDeletedReaders().erase(smallest);
                    return true;
                }
                else {
                    cout << "This user already exists!" << endl;
                    break;
                }
            }
            else {
                int lastNum = it.second->getLastId(person, type);
                Reader r{ name, surname, address, phone_number, rented_books, lastNum + 1 };
                if (r.addNewPerson(person)) {
                    person[r.getId()] = make_unique<Reader>(r);
                    return true;
                }
                else {
                    cout << "This user already exists!" << endl;
                    break;
                }
            }
        }
        else if (type == "LIBRARIAN") {
            try {
                cout << "Salary: ";
                cin >> salary;
                if (cin.fail()) {
                    throw runtime_error{ "Invalid input for salary" };
                }
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            if (!it.second->getDeletedLibrarians().empty()) {
                int smallest = *it.second->getDeletedLibrarians().begin();
                Librarian l{ name, surname, address, phone_number, salary, smallest };
                if (l.addNewPerson(person)) {
                    person[smallest] = make_unique<Librarian>(l);
                    it.second->getDeletedLibrarians().erase(smallest);
                    return true;
                }
                else {
                    cout << "This user already exists!" << endl;
                    break;
                }
            }
            else {
                int lastNum = it.second->getLastId(person, type);
                Librarian l{ name, surname, address, phone_number, salary, lastNum + 1 };
                if (l.addNewPerson(person)) {
                    person[l.getId()] = make_unique<Librarian>(l);
                    return true;
                }
                else {
                    cout << "This user already exists!" << endl;
                    break;
                }
            }
        }
        else if (type == "ADMIN") {
            try {
                cout << "Salary: ";
                cin >> salary;
                if (cin.fail()) {
                    throw runtime_error{ "Invalid input for salary" };
                }
            }
            catch (const exception& e) {
                cerr << "Error: " << e.what() << endl;
            }
            if (!it.second->getDeletedAdmins().empty()) {
                int smallest = *it.second->getDeletedAdmins().begin();
                Admin a{ name, surname, address, phone_number, salary, smallest };
                if (a.addNewPerson(person)) {
                    person[smallest] = make_unique<Admin>(a);
                    it.second->getDeletedAdmins().erase(smallest);
                    return true;
                }
                else {
                    cout << "This user already exists!" << endl;
                    break;
                }
            }
            else {
                int lastNum = it.second->getLastId(person, type);
                Admin a{ name, surname, address, phone_number, salary, lastNum + 1 };
                if (a.addNewPerson(person)) {
                    person[a.getId()] = make_unique<Admin>(a);
                    return true;
                }
                else {
                    cout << "This user already exists!" << endl;
                    break;
                }
            }
        }
        else {
            cout << "This type doesnt exist!" << endl;
        }
        break;
    }
    return false;
}
