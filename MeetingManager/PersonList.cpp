#include "stdafx.h"
#include "PersonList.h"
#include <string>
#include <vector>

using namespace std;

PersonList::PersonList(int n)
{
	Per_Vector.resize(n);
}

const Person* PersonList::getPerson(int index) {
	if (Per_Vector.size > index && Per_Vector.size > 0)
	{
		return &(Per_Vector[index]);
	}
	else
		return nullptr;
}

const Person* PersonList::getPerson(string name_) {
	vector<Person>::iterator iter = Per_Vector.begin();
	for (iter; iter != Per_Vector.end(); iter++) {
		if(iter->getName == name_)
			return 
	}
}

void PersonList::setPerson(int index, string name_, string email_) {
	Per_Vector[index].setName(name_);
	Per_Vector[index].setEmail(email_);
}

void PersonList::delPerson(string name_) {

}

PersonList::~PersonList()
{
}
