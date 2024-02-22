#ifndef PERSON_UTIL_H
#define PERSON_UTIL_H

#include <iostream>
#include <vector>
#include <memory>
#include <map>
#include <string>
#include <iomanip>

#include "Person.h"
#include "Reader.h"
#include "Librarian.h"
#include "Admin.h"

void display(const map<int, unique_ptr<Person>>& people);
void displayReaders(map<int, unique_ptr<Person>>& person);
void displayLibrarians(map<int, unique_ptr<Person>>& person);
void displayAdmins(map<int, unique_ptr<Person>>& person);
void validatePhoneNumber(const map<int, unique_ptr<Person>>& person, const string& type);
bool validatePhoneNumber(const string& phone_number);
bool deletePerson(map<int, unique_ptr<Person>>& person, int id);
bool addNewPerson(map<int, unique_ptr<Person>>& person, const string& type);
#endif