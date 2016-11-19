// MeetingManager.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
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

