#include <string>
#pragma once

using namespace std;

class Person
{
private:
	string name;
	string email;

public:
	Person(string name_, string email_) {};
	string getName() const {return name;}
	string getEmail() const { return email; }
	void setName(const string new_name) {};
	void setEmail(const string new_email) {};
	~Person() {};
};

