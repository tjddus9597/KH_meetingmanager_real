#include"stdafx.h"
#include<unordered_map>
#include"MeetingManager.h"

using namespace std;

int main()
{
	unordered_map<int, Room> roomList;
	unordered_map<string, Person> people;

	cout << "-------------------Start Scheduling-------------------\n\n";

	do {
		cout << "------------------------------------------------------" << endl;
	} while (!simulation(roomList, people));
}