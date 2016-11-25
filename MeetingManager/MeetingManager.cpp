#include"stdafx.h"
#include"Meeting.h"
#include"Person.h"
#include"Room.h"
#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<iterator>
#include<sstream>
#include<stdexcept>

bool simulation(unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList, unordered_map<string, Person>& people,
	unordered_map<string, bool(*)(vector<string>&, unordered_map<int, Room>&, unordered_map<string, Meeting>&, unordered_map<string, Person>&)>& commandList);
inline bool isCmNum(vector<string>& words, int validNum);																			//��ɾ� ���� Ȯ�� �Լ�
bool qq_quit(vector<string>&, unordered_map<int, Room>&, unordered_map<string, Meeting>&, unordered_map<string, Person>&); //qq ��ɾ� ó�� �Լ�
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList
	, unordered_map<string, Person>& people);																		   //ar ��ɾ� ó�� �Լ�
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList
	, unordered_map<string, Person>& people);																		   //am ��ɾ� ó�� �Լ�
bool ai_insrtPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList
, unordered_map<string, Person>& people);																			   //ai ��ɾ� ó�� �Լ�

using namespace std;
int main()
{
	unordered_map<int,Room> roomList;
	unordered_map<string, Meeting> meetingList;
	unordered_map<string, Person> people;
	unordered_map<string, bool(*)(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList,
		unordered_map<string, Person>& people)> commandList;
	
	//commandList�� �׸� ����� ����
	commandList.emplace("qq",qq_quit);
	commandList.emplace("ar", ar_insrtRoom);
	commandList.emplace("am", am_insrtMeeting);
	commandList.emplace("ai", ai_insrtPerson);

	cout << "-------------------Start Scheduling-------------------\n\n";
	
	do {		
	} while(!simulation(roomList,meetingList,people,commandList));
}

bool simulation(unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList, unordered_map<string, Person>& people,
	unordered_map<string, bool(*)(vector<string>&, unordered_map<int, Room>&, unordered_map<string, Meeting>&, unordered_map<string, Person>&)>& commandList)
{
	//��ɾ� �Է�
	string command;
	cout << "Enter your command : ";
	getline(cin, command);
	if (command == "") { return false; }


	istringstream is{ command };
	vector<string> words{ istream_iterator<string> {is},istream_iterator<string> {} }; 	//��ɾ� ��ūȭ

	
	bool isQuit;
	auto iter = commandList.find(words[0]); //��ɾ� �ؼ�
	
	
	if (iter != commandList.end()) {
		isQuit = (iter->second)(words, roomList, meetingList, people);		//��ɾ� �Լ� ����
	}
	else {
		cerr << "Invalid command \n";
		return false;
	}
	return isQuit;
}

//��ɾ� ���� Ȯ�� �Լ�
inline bool isCmNum(vector<string>& words, int validNum)
{
	if ((words.end() - words.begin() == validNum)) {
		return true;
	}
	else {
		return false;
	}
}

//���� ��ɾ� �Լ�
bool qq_quit(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList, unordered_map<string, Person>& people)
{
	if (isCmNum(words,1)) {
		return true;
	}
	else {
		cerr << "Invalid command \n";
		return false;
	}
}

//�� �߰� �Լ�
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList, unordered_map<string, Person>& people)
{
	int roomId;
	if (isCmNum(words,2)) {
		//roomId �ص� �� �˻�
		try {
			roomId = stoi(words[1]);
			roomList.emplace(roomId, Room(roomId));
			cout << "Room <" << roomId << "> (Added)\n";
		}
		catch (...) {
			std::cerr << "Invalid Room ID. please use valid range, interger number " << endl;
		}
	}
	else {
		cerr << "Invalid command : worng input number \n";
	}

	return false; //�ٽ� ��ɾ� �Է� ����
}



//ȸ�� �߰� �Լ� : ���� ���� ������
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList
	, unordered_map<string, Person>& people)
{
	int roomId;
	string day;
	double startTime;
	double endTime;
	string topic;
	if (isCmNum(words,6)) {
		try {
			roomId = stoi(words[1]);
			day = words[2];
			startTime = stod(words[3]);
			endTime = stod(words[4]);
			topic = words[5];
			roomList.find(roomId)->second.addMeeting(day, startTime, endTime, topic);
			cout << "Meeting <" << roomId << "> <" << day << "> <" << startTime << "> <" << endTime << "> <" << topic << "> (added) \n";
		}
		catch (...) {
			cerr << "Invalid Input. Check if :\n1) Room ID is valid-range integer\n2)start time is valid-range number\n3)end time is valid-range number\n4)Input order\n\n";
		}
	}
	else {
		cerr << "Invalid command : worng input number \n";
	}

	return false; //�ٽ� ��ɾ� �Է� ����
}

//��� �߰� �Լ�
bool ai_insrtPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList
	, unordered_map<string, Person>& people)
{
	if (isCmNum(words, 3)) {
			string name;
			string email;
			name = words[1];
			email = words[2];
			people.emplace(name, Person(name, email));
			cout << "Person <" << name << "> <" << email << "> (added)\n";
	}
	else {
		cerr << "Invalid command : worng input number \n";
	}
	return false;
}