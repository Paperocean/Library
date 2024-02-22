#ifndef ADMIN_H
#define ADMIN_H

#include "Person.h"

using namespace std;

class Admin : public Person {
private:
	static constexpr const char* def_position = "ADMIN";
	static constexpr const double def_salary = 10000.0;
	static int nextId;

protected:
	static int soldBooksNum_, rentedBooksNum_, returnedBooksNum_;
	double salary_;

public:
	Admin(string name, string surname, string address, string phone_number,
		double salary = def_salary, int id = nextId++);
	virtual ~Admin() {};
	virtual void print(ostream& os) const override;
	virtual string makeReport() const override;
	double getSalary() const;
	virtual void saveData(ostream& os) const override;

};
#endif // !ADMIN_H
