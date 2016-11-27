#include "stdafx.h"
#include "Person.h"
#include <string>
Person::Person() {}

Person::Person(string name_, string email_) {
	name = name_;
	email = email_;
}

string Person::getName() const {
	return name;
}

string Person::getEmail() const {
	return email;
}

void Person::setName(const string new_name) {
	name = new_name;
}

void Person::setEmail(const string new_email) {
	email = new_email;
}

Person::~Person()
{
}
