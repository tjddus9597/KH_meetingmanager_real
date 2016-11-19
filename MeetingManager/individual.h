#pragma once
#include <string>

using namespace std;

class individual
{
private:
	string name;
	string email;

public:
	individual(string name_, string email_) : name{ name_ }, email{ email_ } {};
	~individual();
	void pi(string name);
	void di(string name);
};

