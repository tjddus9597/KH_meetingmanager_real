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
inline bool isCmNum(vector<string>& words, int validNum);																			//명령어 길이 확인 함수
bool qq_quit(vector<string>&, unordered_map<int, Room>&, unordered_map<string, Meeting>&, unordered_map<string, Person>&); //qq 명령어 처리 함수
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList
	, unordered_map<string, Person>& people);																		   //ar 명령어 처리 함수
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList
	, unordered_map<string, Person>& people);																		   //am 명령어 처리 함수
bool ai_insrtPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList
, unordered_map<string, Person>& people);																			   //ai 명령어 처리 함수

using namespace std;
int main()
{
	unordered_map<int,Room> roomList;
	unordered_map<string, Meeting> meetingList;
	unordered_map<string, Person> people;
	unordered_map<string, bool(*)(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList,
		unordered_map<string, Person>& people)> commandList;
	
	//commandList에 항목 만들기 대입
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
	//명령어 입력
	string command;
	cout << "Enter your command : ";
	getline(cin, command);
	if (command == "") { return false; }


	istringstream is{ command };
	vector<string> words{ istream_iterator<string> {is},istream_iterator<string> {} }; 	//명령어 토큰화

	
	bool isQuit;
	auto iter = commandList.find(words[0]); //명령어 해석
	
	
	if (iter != commandList.end()) {
		isQuit = (iter->second)(words, roomList, meetingList, people);		//명령어 함수 실행
	}
	else {
		cerr << "Invalid command \n";
		return false;
	}
	return isQuit;
}

//명령어 길이 확인 함수
inline bool isCmNum(vector<string>& words, int validNum)
{
	if ((words.end() - words.begin() == validNum)) {
		return true;
	}
	else {
		return false;
	}
}

//종료 명령어 함수
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

//방 추가 함수
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Meeting>& meetingList, unordered_map<string, Person>& people)
{
	int roomId;
	if (isCmNum(words,2)) {
		//roomId 해독 및 검사
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

	return false; //다시 명령어 입력 받음
}



//회의 추가 함수 : 현재 오류 수정중
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

	return false; //다시 명령어 입력 받음
}

//사람 추가 함수
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