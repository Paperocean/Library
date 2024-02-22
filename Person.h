#ifndef PERSON_H
#define PERSON_H

#include <iostream>
#include <iomanip>
#include <memory>
#include <map>
#include <set>
#include <vector>
#include "I_Printable.h"

using namespace std;
class Person : public I_Printable {
    friend std::ostream& operator<<(std::ostream& os, const unique_ptr<Person>& person);

private:
    static constexpr const char* def_name = "Unnamed";
    static constexpr const char* def_surname = "Unknown";
    static constexpr const char* def_address = "None";
    static constexpr const char* def_phone_number = "000000000";
    static constexpr const char* def_position = "Unclassified";
    static int nextId;

protected:
    static set<int> deletedAdminNums;
    static set<int> deletedLibrarianNums;
    static set<int> deletedReaderNums;
    int id_;
    string name_, surname_, address_, phone_number_, position_;

public:
    Person(std::string name = def_name, std::string surname = def_surname,
        std::string address = def_address, std::string phone_number = def_phone_number,
        std::string position = def_position, int id = nextId++);

    virtual void print(std::ostream& os) const override = 0;
    virtual ~Person() {}
    string getName() const;
    string getSurname() const;
    string getAddress() const;
    string getPhoneNumber() const;
    string getPosition() const;
    int getId() const;
    int getLastId(map<int, unique_ptr<Person>>& person, const string& type) const;
    bool addNewPerson(map<int, unique_ptr<Person>>& people);
    bool deletePerson(map<int, unique_ptr<Person>>& person, int id);
    static set<int>& getDeletedAdmins();
    static set<int>& getDeletedLibrarians();
    static set<int>& getDeletedReaders();
    virtual string makeReport() const = 0;
    virtual void saveData(ostream& os) const = 0;

};

#endif // PERSON_H
