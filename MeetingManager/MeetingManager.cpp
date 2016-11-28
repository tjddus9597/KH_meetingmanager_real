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

bool simulation(unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);

inline bool isCmNum(vector<string>& words, int validNum);																			//명령어 길이 확인 함수
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList);												 	    //ar 명령어 처리 함수
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList);													//am 명령어 처리 함수
bool ai_insrtPerson(vector<string>& words, unordered_map<string, Person>& people);													//ai 명령어 처리 함수
bool ap_insrtParticipation(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);		//ap 명령어 처리 함수
bool pi_printPerson(vector<string>& words, unordered_map<string, Person>& people);
bool pr_printRoom(vector<string>& words, unordered_map<int, Room>& roomList);
//bool pm_printMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
//bool ps_printEveryMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
//bool pg_printEveryPerson(vector<string>& words, unordered_map<string, Person>& people);
//bool pa_printAll(vector<string>& words, unordered_map<int, Room>& roomList);
bool di_delPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);				//di 명령어 처리 함수
bool dr_delRoom(vector<string>& words, unordered_map<int, Room>& roomList);															//dr 명령어 처리 함수
bool dm_delMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool dp_delParticipation(vector<string>& words, unordered_map<int, Room>& roomList);

using namespace std;
int main()
{
	unordered_map<int,Room> roomList;
	unordered_map<string, Person> people;

	cout << "-------------------Start Scheduling-------------------\n\n";
	
	do {

	} while(!simulation(roomList,people));
}

bool simulation(unordered_map<int, Room>& roomList, unordered_map<string, Person>& people)
{
	//명령어 입력
	string command;
	cout << "Enter your command : ";
	getline(cin, command);
	if (command == "") { return false; }


	istringstream is{ command };
	vector<string> words{ istream_iterator<string> {is},istream_iterator<string> {} }; 	//명령어 토큰화

	
	bool isQuit = false;
	//명령어 해석 및 실행
	if (words[0] == "qq") {
		isQuit = true;
	}
	else if(words[0] == "ar"){
		isQuit = ar_insrtRoom(words, roomList);
	}
	else if (words[0] == "am") {
		isQuit = am_insrtMeeting(words, roomList);
	}
	else if (words[0] == "ai") {
		isQuit = ai_insrtPerson(words, people);
	}
	else if (words[0] == "ap") {
		isQuit = ap_insrtParticipation(words, roomList, people);
	}
	else if (words[0] == "pi") {
		isQuit = pi_printPerson(words, people);
	}
	else if (words[0] == "pr") {
		isQuit = pr_printRoom(words, roomList);
	}
	else if (words[0] == "di") {
		isQuit = di_delPerson(words, roomList, people);
	}
	else if (words[0] == "dr") {
		isQuit = dr_delRoom(words, roomList);
	}
	else if (words[0] == "dm") {
		isQuit = dm_delMeeting(words, roomList);
	}
	else if (words[0] == "dp") {
		isQuit = dp_delParticipation(words, roomList);
	}
	else {
		cerr << "Wrong command\n";
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

bool pi_printPerson(vector<string>& words, unordered_map<string, Person>& people)
{
	if (isCmNum(words, 2)) {
		string name;
		name = words[1];
		auto thisPerson = people.find(name);
		if (thisPerson != people.end()) {
			cout << "Name : " << thisPerson->second.getName() << "\n";
			cout << "Email : " << thisPerson->second.getEmail() << "\n";
		}
		else {
			cout << "There no such person \n";
		}
	}
	else {
		cerr << "Incalid command : worng input number \n";
	}
	return false;
}

bool pr_printRoom(vector<string>& words, unordered_map<int, Room>& roomList)
{
	if (isCmNum(words, 2)) {
		int roomId = stoi(words[1]);
		unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
		if (roomPtr == roomList.end()) {
			cout << "There's no such room\n";
			return false;
		}
		cout << "RoomId : " << roomId << endl;
		cout << "\t<Meeting List>" << endl;
		for (auto meetingPtr = roomPtr->second.getMeetingList().begin(); meetingPtr != roomPtr->second.getMeetingList().end(); ++meetingPtr) {
			cout << "Meeting at <" << meetingPtr->second.getDay() << ">, From <" << meetingPtr->second.getStartTime() << "> to <" <<
				meetingPtr->second.getEndTime() << ">" << endl;
			cout << "  Topic : " << meetingPtr->second.getTopic() << "\n" << endl;
		}
	}
	else {
		cerr << "Invalid command : worng input number \n";
	}
	return false;
}

//방 추가 명령어 함수
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList)
{
	int roomId;
	if (isCmNum(words, 2)) {
		//roomId 해독 및 검사
		roomId = stoi(words[1]);
		roomList.emplace(roomId, Room(roomId));
		cout << "Room <" << roomId << "> (Added)\n";
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}

	return false; //다시 명령어 입력 받음
}



//회의 추가 함수 : 현재 오류 수정중
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList)
{
	int roomId;
	string day;
	double startTime;
	double endTime;
	string topic;
	if (isCmNum(words, 6)) {
		roomId = stoi(words[1]);
		day = words[2];
		startTime = stod(words[3]);
		endTime = stod(words[4]);
		topic = words[5];
		unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
		if (roomPtr == roomList.end()) {
			cout << "There's no such room\n";
			return false;
		}
		if (roomPtr->second.addMeeting(day, startTime, endTime, topic)) {
			return false;
		}
		cout << "Meeting <" << roomId << "> <" << day << "> <" << startTime << "> <" << endTime << "> <" << topic << "> (added) \n";
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}

	return false; //다시 명령어 입력 받음
}

//사람 추가 함수
bool ai_insrtPerson(vector<string>& words, unordered_map<string, Person>& people)
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
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

bool ap_insrtParticipation(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	try {
		if (isCmNum(words, 5)) {
			int roomId = stoi(words[1]);
			string day = words[2];
			double time = stod(words[3]);
			string name = words[4];
			unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
			if (roomPtr == roomList.end()) {
				cout << "There's no such room\n";
				return false;
			}
			if (roomPtr->second.getMeeting(day, time).addParticipation(people, name)) {
				return false;	// 오류 발생
			}
			cout << "Participation <" << roomId << "> <" << day << "> <" << time << "> <" << name << "> (added) \n";
		}
		else {
			cerr << "Invalid command : worng input number \n";
		}
	}
	catch (runtime_error) {
		;
	}
		
	return false;
}

/* 
di name: 특정 사람이 어떤 회의에도 참석하지 않았을 경우 삭제. 오류: 특정 이름에 해당하는 사람이 없을 때, 1개 이상 회의에 참석자일 때
*/
bool di_delPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	if (isCmNum(words, 2)) {
		string name = words[1];
		if (people.find(name) != people.end()) {	// people 안에 이름이 name인 person이 존재하면
			if (roomList.size() == 0) {
				people.erase(name);
				cout << "Person <" << name << "> (deleted) \n";
			}
			else {
				for (auto roomPtr = roomList.begin(); roomPtr != roomList.end(); roomPtr++) {
					for (auto meetingPtr = roomPtr->second.getMeetingList().begin(); meetingPtr != roomPtr->second.getMeetingList().end(); meetingPtr++) {
						auto PersonList = meetingPtr->second.getParticipation();
						if (PersonList.find(name) == PersonList.end()) {	// 어떤 회의에도 참석하지 않았을 경우
							people.erase(name);
							cout << "Person <" << name << "> (deleted) \n";
						}
						else {
							cout << name << " 은 회의에 참석 중입니다." << endl;
						}
					}
				}
			}
		}
		else {
			cerr << "이름이 " << name << " 인 Person이 People안에 존재 하지 않습니다." << endl;
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*
dr room: 특정 방번호 회의실과 그 방에 있는 모든 회의를 삭제. 오류: 방번호가 범위를 벗어났을 때, 방번호에 해당하는 회의실이 없을 때
*/

bool dr_delRoom(vector<string>& words, unordered_map<int, Room>& roomList) {
	if (isCmNum(words, 2)) {
		int roomId = stoi(words[1]);
		auto roomPtr = roomList.find(roomId);
		if (roomPtr != roomList.end())  {	//roomList에 방번호가 roomId인 방이 존재하면
			if (!roomPtr->second.getMeetingList().empty()) {	//방에 meeting이 존재하면
				roomPtr->second.getMeetingList().clear();
			}
			roomList.erase(roomId);
			cout << "Room <" << roomId << "> (deleted) \n";
		}
		else {
			cerr << "방번호가 " << roomId << " 인 Room이 존재 하지 않습니다." << endl;
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*dm room day time: 미팅 삭제. 오류: 방번호 범위가 벗어날 때, 방번호에 해당하는 회의실이 없을 때, 특정 시간에 회의가 없을 때*/

bool dm_delMeeting(vector<string>& words, unordered_map<int, Room>& roomList) {
	if (isCmNum(words, 4)) {
		int roomId = stoi(words[1]);
		string day = words[2];
		double time = stod(words[3]);
		auto roomPtr = roomList.find(roomId);
		if (roomPtr != roomList.end()) {	//roomList에 방번호가 roomId인 방이 존재하면
			auto meetingList = roomPtr->second.getMeetingList();	//	미팅리스트
			auto meetingId = roomPtr->second.getMeetingId(day, time);
			if (meetingList.find(meetingId) != meetingList.end()) {		// 특정 시간에 회의가 있다면
				meetingList.erase(meetingId);
				cout << "Meeting <" << roomId << "> <" << day << "> <" << time << "> (deleted) \n";
			}
			else {
				cerr << roomId << " 방에 Day: " << day << " Time: " << time << " 에 회의가 존재하지 않습니다." << endl;
			}
		}
		else {
			cerr << "방번호가 " << roomId << " 인 Room이 존재 하지 않습니다." << endl;
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*dp room day time name: 특정 사람을 미팅 참석자에서 삭제. 
오류: 방번호 범위가 벗어날 때, 방번호에 해당하는 회의실이 없을 때,
특정시간에 회의가 없을 때, 특정 사람이 회의 참석자가 아닐 때*/

bool dp_delParticipation(vector<string>& words, unordered_map<int, Room>& roomList) {
	if (isCmNum(words, 5)) {
		int roomId = stoi(words[1]);
		string day = words[2];
		double time = stod(words[3]);
		string name = words[4];
		auto roomPtr = roomList.find(roomId);
		if (roomPtr != roomList.end()) {									// roomList에 방번호가 roomId인 방이 존재하면
			auto meetingList = roomPtr->second.getMeetingList();			// 미팅리스트
			auto meetingId = roomPtr->second.getMeetingId(day, time);
			if (meetingList.find(meetingId) != meetingList.end()) {			// 특정 시간에 회의가 있다면
				auto participation = meetingList.find(meetingId)->second.getParticipation();
				if (participation.find(name) != participation.end()) {		// 이름이 name인 participation이 있다면
					participation.erase(name);
					cout << "Participation <" << roomId << "> <" << day << "> <" << time << "> <" << name << "> (deleted) \n";
				}
				else {
					cerr << "이름이 " << name << " 인 Participation이 존재하지 않습니다." << endl;
				}
			}
			else {
				cerr << roomId<< " 방에 Day: "<< day << " Time: " << time << " 에 회의가 존재하지 않습니다." << endl;
			}
		}
		else {
			cerr << "방번호가 " << roomId << " 인 Room이 존재 하지 않습니다." << endl;
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}
