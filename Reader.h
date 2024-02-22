#ifndef READER_H
#define READER_H

#include <iostream>
#include <map>
#include <vector>
#include "Person.h"

class Reader : public Person {
private:
	static constexpr const char* def_position = "READER";
	static constexpr int def_rentNum = 0;
	static int nextId;

protected:
	int rentedBooksNum_;

public:
	Reader(string name, string surname, string address, string phone_number, int rentedBooksNum = def_rentNum, int cardNum = nextId++);
	virtual void print(ostream& os) const override;
	int getRentedBooksNumber() const;
	virtual string makeReport() const override;
	virtual void saveData(ostream& os) const override;

};

#endif // !_READER_H_
