// MeetingManager.cpp : �ܼ� ���� ���α׷��� ���� �������� �����մϴ�.
//

#include "stdafx.h"
#include "PersonList.h"
#include <iostream>
#include <list>
#include <string>
#include <vector>

using namespace std;

int main()
{
	PersonList People(100);
	People.setPerson(0, "Kim", "Kim@yahoo.com");
	cout << People.getPerson(0)->getEmail();
}

