#pragma once
#include "Person.h"
#include <string>
#include <vector>

using namespace std;

class PersonList
{
private:
	vector<Person> Per_Vector;

public:
	PersonList(int n);
	const Person* getPerson(int index);
	const Person* getPerson(string name_);
	void setPerson(int index, string name_, string email_);
	void delPerson(string name_);
	~PersonList();
};

