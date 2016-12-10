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
#include<fstream>

bool simulation(unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);

inline bool isCmNum(vector<string>& words, int validNum);																		//명령어 길이 확인 함수
bool qq_Quit(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList);												 	    //ar 명령어 처리 함수
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList);													//am 명령어 처리 함수
bool am_insrtMeeting(int roomId_, string day_, double startTime_, double endTime_, string topic_, unordered_map<int, Room>& roomList);
bool ai_insrtPerson(vector<string>& words, unordered_map<string, Person>& people);													//ai 명령어 처리 함수
bool ap_insrtParticipation(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);		//ap 명령어 처리 함수
bool pi_printPerson(vector<string>& words, unordered_map<string, Person>& people);
bool pr_printRoom(vector<string>& words, unordered_map<int, Room>& roomList);
bool pm_printMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool ps_printEveryMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool pg_printEveryPerson(vector<string>& words, unordered_map<string, Person>& people);
bool pa_printAll(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool rm_replaceMeeting(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool di_delPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);				//di 명령어 처리 함수
bool dr_delRoom(vector<string>& words, unordered_map<int, Room>& roomList);															//dr 명령어 처리 함수
bool dm_delMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool dm_delMeeting(int roomId_, string day_, double startTime_, unordered_map<int, Room>& roomList);
bool dp_delParticipation(vector<string>& words, unordered_map<int, Room>& roomList);
bool ds_delAllMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool dg_delAllPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool da_deleteAll(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool sd_saveFile(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool ld_loadFile(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);


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

bool simulation(unordered_map<int, Room>& roomList, unordered_map<string, Person>& people)
{
	//명령어 입력
	string command;
	cout << "Enter a command : ";
	getline(cin, command);
	if (command == "") { return false; }
	istringstream is{ command };
	vector<string> words{ istream_iterator<string> {is},istream_iterator<string> {} }; 	//명령어 토큰화


	bool isQuit = false;
	//명령어 해석 및 실행
	if (words[0] == "qq") {
		isQuit = qq_Quit(words, roomList, people);
	}
	else if (words[0] == "ar") {
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
	else if (words[0] == "pm") {
		isQuit = pm_printMeeting(words, roomList);
	}
	else if (words[0] == "ps") {
		isQuit = ps_printEveryMeeting(words, roomList);
	}
	else if (words[0] == "pg") {
		isQuit = pg_printEveryPerson(words, people);
	}
	else if (words[0] == "pa") {
		isQuit = pa_printAll(words, roomList, people);
	}
	else if (words[0] == "rm") {
		isQuit = rm_replaceMeeting(words, roomList, people);
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
	else if (words[0] == "ds") {
		isQuit = ds_delAllMeeting(words, roomList);
	}
	else if (words[0] == "dg") {
		isQuit = dg_delAllPerson(words, roomList,people);
	}
	else if (words[0] == "da") {
		isQuit = da_deleteAll(words, roomList, people);
	}
	else if (words[0] == "sd") {
		isQuit = sd_saveFile(words, roomList, people);
	}
	else if (words[0] == "ld") {
		isQuit = ld_loadFile(words, roomList, people);
	}
	else {
		cerr << "Unrecognized command!\n";
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

inline bool isDay(string& day)
{
	if (day == "M") { return false; }
	else if (day == "T") { return false; }
	else if (day == "TW") { return false; }
	else if (day == "Th") { return false; }
	else if (day == "F") { return false; }
	else if (day == "Sa") { return false; }
	else if (day == "Su") { return false; }
	else { return true; }
}

inline bool isTime(double time)
{
	if (0 <= time && time <= 24) { return false; }
	else { return true; }
}

bool qq_Quit(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people)
{
	if (isCmNum(words, 1)) {
		da_deleteAll(words, roomList, people);
		cout << "Done" << endl;
		return true;
	}
	else {
		cerr << "Incalid command : wrong input number \n";
	}
	return false;
}

bool pi_printPerson(vector<string>& words, unordered_map<string, Person>& people)
{
	if (isCmNum(words, 2)) {
		string name;
		name = words[1];
		auto thisPerson = people.find(name);
		if (thisPerson != people.end()) {
			cout << thisPerson->second.getName() << " " << thisPerson->second.getEmail() << endl;
		}
		else {
			cout << "No person with that name!\n";
		}
	}
	else {
		cerr << "Incalid command : worng input number \n";
	}
	return false;
}

bool pr_printRoom(vector<string>& words, unordered_map<int, Room>& roomList)
{
	try{
	if (isCmNum(words, 2)) {
		int roomId = stoi(words[1]);
		unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
		if (roomPtr == roomList.end()) {
			cout << "There's no such room\n";
			return false;
		}
		cout << "--- Room " << roomId << " ---" << endl;
		unordered_map<string, Meeting>& meetingList = roomPtr->second.getMeetingList();
		if (meetingList.size() == 0) {
			cout << "No meetings are scheduled" << endl;
			return false;
		}
		for (auto& meetingElement : meetingList) {
			cout << "Meeting time: " << meetingElement.second.getDay() << " " << meetingElement.second.getStartTime() << ", Topic: " <<
				meetingElement.second.getTopic() << endl;
			unordered_map<string, Person>& parList = meetingElement.second.getParticipation();
			cout << "Participatns: ";
			for (auto& personElement : parList) {
				cout << endl << personElement.second.getName();
			}
			if (parList.size() == 0)
				cout << "None";
			cout << endl;
		}
	}
	else {
		cerr << "Invalid command : worng input number \n";
	}
	}
	catch (out_of_range) {
		cerr << "Room number is not in range!" << endl;
	}
	catch (invalid_argument) {
		cerr << "Invalid argument" << endl;
	}
	return false;
}

bool pm_printMeeting(vector<string>& words, unordered_map<int, Room>& roomList)
{
	try {
		if (isCmNum(words, 4)) {
			int roomId = stoi(words[1]);
			if (roomId < 0) { throw out_of_range("Minus"); }
			string day = words[2];
			if (isDay(day)) { throw invalid_argument("day"); }
			double startTime = stod(words[3]);
			if(isTime(startTime)) { throw invalid_argument("Time"); }
			unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
			if (roomPtr == roomList.end()) {
				cout << "There's no such room\n";
				return false;
			}
			Meeting& meeting = roomPtr->second.getMeeting(day, startTime);
			unordered_map<string, Person>& parList = meeting.getParticipation();
			cout << "Meeting time: " << meeting.getDay() << " " << meeting.getStartTime() << ", Topic: " << meeting.getTopic() << endl;
			cout << "Participatns: ";
			for (auto& personElement : parList) {
				cout << endl << personElement.second.getName();
			}
			if (parList.size() == 0)
				cout << "None";
			cout << endl;
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
	}
	catch (out_of_range) {
		cerr << "Room number is not in range!" << endl;
	}
	catch (invalid_argument) {
		cerr << "Invalid argument" << endl;
	}
	catch (runtime_error) {
		return false;
	}
	return false;
}

bool ps_printEveryMeeting(vector<string>& words, unordered_map<int, Room>& roomList)
{	
	if (isCmNum(words, 1)) {
		double meetingNum = 0;
		double roomNum = 0;
		for (auto& roomElements : roomList) {
			meetingNum += roomElements.second.getMeetingList().size();
			roomNum++;
		}
		if (roomNum == 0) {
			cout << "List of rooms is empty" << endl;
			return false;
		}
		cout << "Information for " << roomNum << " rooms: " << endl;
		for (auto& roomElement : roomList) {
			cout << "--- Room " << roomElement.second.getRoomId() << " ---" << endl;
			unordered_map<string, Meeting>& meetingList = roomElement.second.getMeetingList();
			if (meetingList.size() == 0) {
				cout << "No meetings are scheduled" << endl;
				return false;
			}
			for (auto& meetingElement : meetingList) {
				cout << "Meeting time: " << meetingElement.second.getDay() << " " << meetingElement.second.getStartTime() << ", Topic: " <<
					meetingElement.second.getTopic() << endl;
				unordered_map<string, Person>& parList = meetingElement.second.getParticipation();
				cout << "Participatns: ";
				for (auto& personElement : parList) {
					cout << endl << personElement.second.getName();
				}
				if (parList.size() == 0)
					cout << "None";
				cout << endl;
			}
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

bool pg_printEveryPerson(vector<string>& words, unordered_map<string, Person>& people)
{
	if (isCmNum(words, 1)) {
		if (people.size() == 0) {
			cout << "List of people is empty" << endl;
			return false;
		}
		cout << "Information for " << people.size() << " people:" << endl;
		for (auto& personElement : people) {
			cout << personElement.second.getName() << " " << personElement.second.getEmail() << endl;
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

bool pa_printAll(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people)
{
	if (isCmNum(words, 1)) {
		int PersonNum = static_cast<int>(people.size());
		int RoomNum = static_cast<int>(roomList.size());
		double meetingNum = 0;
		//if (PersonNum == 0 && RoomNum == 0) {
		//	cout << "No data " << endl;
		//	return false;
		//}
		for (auto& roomElement : roomList) {
			meetingNum += roomElement.second.getMeetingList().size();
		}
		cout << "Persons : " << PersonNum << endl;
		cout << "Meetings : " << meetingNum << endl;
		cout << "Rooms : " << RoomNum << endl;
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

//방 추가 명령어 함수
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList)
{
	int roomId;
	try {
		if (isCmNum(words, 2)) {
			roomId = stoi(words[1]);
			if (roomId < 0) { throw out_of_range("Minus"); }
			unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
			if (roomPtr != roomList.end()) {
				cout << "There is already a room with this number!\n";
				return false;
			}
			roomList.emplace(roomId, Room(roomId));
			cout << "Room " << roomId << " added\n";
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
	}
	catch (out_of_range) {
		cerr << "Room number is not in range!" << endl;
	}
	catch (invalid_argument) {
		cerr << "Invalid argument" << endl;
	}
	return false; //다시 명령어 입력 받음
}

//회의 추가 함수
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList)
{
	int roomId;
	string day;
	double startTime;
	double endTime;
	string topic;
	try {
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
			if (endTime <= startTime) {
				cout << "Endtime is faster (or same) as starttime" << endl;
				return false;
			}
			if (roomPtr->second.addMeeting(day, startTime, endTime, topic)) {
				return false;
			}
			cout << "Meeting added at " << day << " " << startTime << endl;
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
	}
	catch (out_of_range) {
		cerr << "Room number is not in range!" << endl;
	}
	catch (invalid_argument) {
		cerr << "Invalid argument" << endl;
	}

	return false; //다시 명령어 입력 받음
}

//함수 추가 함수 오버로딩
bool am_insrtMeeting(int roomId_, string day_, double startTime_, double endTime_,string topic_, unordered_map<int, Room>& roomList)
{
	unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId_);
	if (roomPtr == roomList.end()) {
		cout << "There's no such room\n";
		return false;
	}
	if (roomPtr->second.addMeeting(day_, startTime_, endTime_, topic_)) {
		return false;
	}
	cout << "Meeting added at" << day_ << " " << startTime_ << endl;
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
			if (people.find(name) != people.end()) {
				cout << "There is already a person with this name!" << endl;
				return false;
			}
			people.emplace(name, Person(name, email));
			cout << "Person " << name << " added\n";
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
			if (roomId < 0) { throw out_of_range("Minus"); }
			string day = words[2];
			if (isDay(day)) { throw invalid_argument("day"); }
			double time = stod(words[3]);
			if (isTime(time)) { throw invalid_argument("Time"); }
			string name = words[4];
			unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
			if (roomPtr == roomList.end()) {
				cout << "There's no such room\n";
				return false;
			}
			if (roomPtr->second.getMeeting(day, time).addParticipation(people, name)) {
				return false;	// 오류 발생
			}
			cout << "Participation "<< name << " added \n";
		}
		else {
			cerr << "Invalid command : worng input number \n";
		}
	}
	catch (runtime_error) {
		;
	}
	catch (out_of_range) {
		cerr << "Room number is not in range!" << endl;
	}
	catch (invalid_argument) {
		cerr << "Invalid argument" << endl;
	}
	return false;
}


bool rm_replaceMeeting(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people)
{
	try {
		if (isCmNum(words, 7)) {
			int oldRoomId = stoi(words[1]);
			if (oldRoomId < 0) { throw out_of_range("Minus"); }
			string oldDay = words[2];
			if (isDay(oldDay)) { throw invalid_argument("day"); }
			double oldStartTime = stod(words[3]);
			if (isTime(oldStartTime)) { throw invalid_argument("Time"); }
			int newRoomId = stoi(words[4]);
			if (newRoomId < 0) { throw out_of_range("Minus"); }
			string newDay = words[5];
			if (isDay(newDay)) { throw invalid_argument("day"); }
			double newStartTime = stod(words[6]);
			if (isTime(newStartTime)) { throw invalid_argument("Time"); }
			unordered_map<int, Room>::iterator oldRoomPtr = roomList.find(oldRoomId);
			if (oldRoomPtr == roomList.end()) {
				cout << "There is no such room\n";
				return false;
			}
			string Topic = oldRoomPtr->second.getMeeting(oldDay, oldStartTime).getTopic();
			int oldEndTime = static_cast<int>(oldRoomPtr->second.getMeeting(oldDay, oldStartTime).getEndTime());
			int meetingTime = static_cast<int>(oldEndTime - oldStartTime);
			int newEndTime = static_cast<int>(newStartTime + meetingTime);
			if (isTime(newEndTime)) { throw invalid_argument("Time"); }
			unordered_map<string, Person> ParList = oldRoomPtr->second.getMeeting(oldDay, oldStartTime).getParticipation();
			unordered_map<int, Room>::iterator newRoomPtr = roomList.find(newRoomId);
			if (newRoomPtr == roomList.end()) {
				cout << "There is no such room\n";
				return false;
			}

			if ((newRoomPtr->second.isMeetingEx(oldDay, oldStartTime, newDay, newStartTime, newEndTime))) {
					cerr << "There is already a meeting at that time!\n";
					return false;
			}
			
			//실제 방 추가 제거 Code
			dm_delMeeting(oldRoomId, oldDay, oldStartTime, roomList);
			newRoomPtr->second.addMeeting(newDay, newStartTime, newEndTime, Topic);
			newRoomPtr->second.getMeeting(newDay, newStartTime).acceptParticipation(ParList);
			cout << "Meeting rescheduled to room " << newRoomId << " at " << newDay << " " << newStartTime << endl;
			return false;
		}
		else {
			cerr << "Invalid command : worng input number \n";
		}
	}
	catch (runtime_error) {
		;
	}
	catch (out_of_range) {
		cerr << "Room number is not in range!" << endl;
	}
	catch (invalid_argument) {
		cerr << "Invalid argument" << endl;
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
			for (auto roomPtr = roomList.begin(); roomPtr != roomList.end(); roomPtr++) {
				for (auto meetingPtr = roomPtr->second.getMeetingList().begin(); meetingPtr != roomPtr->second.getMeetingList().end(); meetingPtr++) {
					auto PersonList = meetingPtr->second.getParticipation();
					if (PersonList.find(name) == PersonList.end()) {	// 특정 회의에도 참석하지 않았을 경우
					}
					else {
						cout << "Cannot clear people list unless there are no meetings!" << endl;
						return false;
					}
				}
			}
			people.erase(name);
			cout << "Person " << name << " deleted" << endl;
		}
		else {
			cerr << "No person with that name!" << endl;
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
	try {
		if (isCmNum(words, 2)) {
			int roomId = stoi(words[1]);
			if (roomId < 0) { throw out_of_range("Minus"); }
			auto roomPtr = roomList.find(roomId);
			if (roomPtr != roomList.end()) {	//roomList에 방번호가 roomId인 방이 존재하면
				if (!roomPtr->second.getMeetingList().empty()) {	//방에 meeting이 존재하면
					roomPtr->second.getMeetingList().clear();
				}
				roomList.erase(roomId);
				cout << "Room " << roomId << " deleted \n";
			}
			else {
				cerr << "No room with that number!" << endl;
			}
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
	}
	catch (out_of_range) {
		cerr << "Room number is not in range!" << endl;
	}
	catch (invalid_argument) {
		cerr << "Invalid argument" << endl;
	}
	return false;
}

/*dm room day time: 미팅 삭제. 오류: 방번호 범위가 벗어날 때, 방번호에 해당하는 회의실이 없을 때, 특정 시간에 회의가 없을 때*/

bool dm_delMeeting(vector<string>& words, unordered_map<int, Room>& roomList) {
	try {
		if (isCmNum(words, 4)) {
			int roomId = stoi(words[1]);
			string day = words[2];
			double time = stod(words[3]);
			auto roomPtr = roomList.find(roomId);
			if (roomPtr != roomList.end()) {	//roomList에 방번호가 roomId인 방이 존재하면
				auto& meetingList = roomPtr->second.getMeetingList();	//	미팅리스트
				auto meetingId = roomPtr->second.getMeetingId(day, time);
				if (meetingList.find(meetingId) != meetingList.end()) {		// 특정 시간에 회의가 있다면
					meetingList.erase(meetingId);
					cout << "Meeting at " << day << " " << time << " deleted \n";
				}
				else {
					cerr << "No meeting at that time!" << endl;
				}
			}
			else {
				cerr << "No room with that number!" << endl;
			}
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
	}
	catch (out_of_range) {
		cerr << "Room number is not in range!" << endl;
	}
	catch (invalid_argument) {
		cerr << "Invalid argument" << endl;
	}
	return false;
}
/*dm 오버로딩 함수. dm romm day startTime을 직접 입력 받는다.
*/
bool dm_delMeeting(int roomId_, string day_, double startTime_, unordered_map<int, Room>& roomList) {
	int roomId = roomId_;
	string day = day_;
	double time = startTime_;
	auto roomPtr = roomList.find(roomId);
	if (roomPtr != roomList.end()) {	//roomList에 방번호가 roomId인 방이 존재하면
		auto& meetingList = roomPtr->second.getMeetingList();	//	미팅리스트
		auto meetingId = roomPtr->second.getMeetingId(day, time);
		if (meetingList.find(meetingId) != meetingList.end()) {		// 특정 시간에 회의가 있다면
			meetingList.erase(meetingId);
		}
		else {
			cerr << "No meeting at that time!" << endl;
		}
	}
	else {
		cerr << "No room with that number!" << endl;
	}
	return false;
}

/*dp room day time name: 특정 사람을 미팅 참석자에서 삭제. 
오류: 방번호 범위가 벗어날 때, 방번호에 해당하는 회의실이 없을 때,
특정시간에 회의가 없을 때, 특정 사람이 회의 참석자가 아닐 때*/

bool dp_delParticipation(vector<string>& words, unordered_map<int, Room>& roomList) {
	try {
		if (isCmNum(words, 5)) {
			int roomId = stoi(words[1]);
			if (roomId < 0) { throw out_of_range("Minus"); }
			string day = words[2];
			if (isDay(day)) { throw invalid_argument("day"); }
			double time = stod(words[3]);
			if (isTime(time)) { throw invalid_argument("Time"); }
			string name = words[4];
			auto roomPtr = roomList.find(roomId);
			if (roomPtr != roomList.end()) {									// roomList에 방번호가 roomId인 방이 존재하면
				auto& meetingList = roomPtr->second.getMeetingList();			// 미팅리스트
				auto meetingId = roomPtr->second.getMeetingId(day, time);
				if (meetingList.find(meetingId) != meetingList.end()) {			// 특정 시간에 회의가 있다면
					auto& participation = meetingList.find(meetingId)->second.getParticipation();
					if (participation.find(name) != participation.end()) {		// 이름이 name인 participation이 있다면
						participation.erase(name);
						cout << "Participation " << name << " deleted"<<endl;
					}
					else {
						cerr << "This person is not a participant in the meeting!" << endl;
					}
				}
				else {
					cerr << "No meeting at that time!" << endl;
				}
			}
			else {
				cerr << "No room with that number!" << endl;
			}
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
	}
	catch (out_of_range) {
		cerr << "Room number is not in range!" << endl;
	}
	catch (invalid_argument) {
		cerr << "Invalid argument" << endl;
	}
	return false;
}

/* ds: 모든 회의를 삭제. 오류: 없음 */

bool ds_delAllMeeting(vector<string>& words, unordered_map<int, Room>& roomList) {
	if (isCmNum(words, 1)) {
		for (auto roomPtr = roomList.begin(); roomPtr != roomList.end(); roomPtr++) {
			roomPtr->second.getMeetingList().clear();		//모든 회의 삭제
		}
		cout << "All meetngs deleted" << endl;
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*dg: 모든 개인이 어떤 회의에도 참석하지 않는 경우, 모든 개인을 삭제. 오류: 참석자가 포함된 미팅이 있는 경우*/

bool dg_delAllPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	if (isCmNum(words, 1)) {
		bool noOneAttend = true;
		for (auto roomPtr = roomList.begin(); roomPtr != roomList.end(); roomPtr++) {
			for (auto meetingPtr = roomPtr->second.getMeetingList().begin(); meetingPtr != roomPtr->second.getMeetingList().end(); meetingPtr++) {
				auto PersonList = meetingPtr->second.getParticipation();
				if (PersonList.begin() != PersonList.end()) {	// 특정 회의 안에 사람이 있는 경우
					noOneAttend = false;
					cerr << "Cannot clear people list unless there are no meetings!" << endl;
					return false;
				}
			}
		}
		if (noOneAttend = true) {
			people.clear();		// 모든 개인 삭제
			cout << "All persons deleted" << endl;
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*da: 모든 회의실, 모든 개인, 회의에 관한 정보 삭제. 오류: 없음*/

bool da_deleteAll(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	if (isCmNum(words, 1)) {
		roomList.clear();	// 모든 회의실, 회의 삭제
		people.clear();		// 모든 개인 삭제
		cout << "All rooms are deleted \nAll meetngs deleted\nAll persons deleted" << endl;
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*sd filename: 현재 회의실, 사람, 회의에 관한 정보를 파일에 저장. 오류: 파일이름에 해당하는 파일이 열리지 않을 때*/

bool sd_saveFile(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	if (isCmNum(words, 2)) {
		string filename = words[1]+".txt";
		ofstream os(filename);

		//사람 정보 출력
		cout << "[People]" << endl;
		os << "[People]" << endl;
		if (people.size() == 0) {
			cout << "No Person added" << endl;
			os << "No Person added" << endl;
		}
		else {
			for (auto& personElement : people) {
				cout << "<Person> " << personElement.second.getName() << " " << personElement.second.getEmail() << endl;
				os << "<Person> " << personElement.second.getName() << " " << personElement.second.getEmail() << endl;
			}
		}
		//회의실 정보 출력
		if (roomList.size() == 0)
		{
			cout << "[Room]" << endl;
			cout << "No Room Exist" << endl;
			os << "[Room]" << endl;
			os << "No Room Exist" << endl;
			return false;
		}
		for (auto& roomElement : roomList) {
			cout << "[Room " << roomElement.second.getRoomId() << "]" << endl;
			os << "[Room " << roomElement.second.getRoomId() << "]" << endl;
		//회의 정보 출력
			if (roomElement.second.getMeetingList().size() == 0) {
				cout << "No Meeting Exist" << endl;
				os << "No Meeting Exist" << endl;
			}
			else {
				for (auto& meetingElement : roomElement.second.getMeetingList()) {
					cout << "<Meeting> " << meetingElement.second.getDay() << " " << meetingElement.second.getStartTime() << " " << meetingElement.second.getEndTime() <<
						" " << meetingElement.second.getTopic() << endl;
					os << "<Meeting> " << meetingElement.second.getDay() << " " << meetingElement.second.getStartTime() << " " << meetingElement.second.getEndTime() <<
						" " << meetingElement.second.getTopic() << endl;
					unordered_map<string, Person>& parList = meetingElement.second.getParticipation();
					for (auto& personElement : parList) {
						cout << "<Participation> " << personElement.second.getName() << " " << personElement.second.getEmail() << endl;
						os << "<Participation> " << personElement.second.getName() << " " << personElement.second.getEmail() << endl;
					}
				}
			}
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

bool ld_loadFile(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	if (isCmNum(words, 2)) {
		string filename = words[1] + ".txt";
		string command;
		ifstream is(filename);
		vector<pair<string, vector<string>>> lines;
		while (!is.eof()) {
			getline(is, command);
			istringstream is{ command };
			vector<string> tokens{ istream_iterator<string> {is},istream_iterator<string> {} }; 	//명령어 토큰화
			lines.push_back({ command,tokens });
		}
		vector<pair<string, vector<string>>> ::iterator linesPtr = lines.begin();
		if (linesPtr->first != "[People]") {
			cout << "불러올 파일이 저장 형식과 맞지 않습니다." << endl;
			return false;
		}
		string Person_name, Person_email;
		string roomId, day, startTime, endTime, topic, name, email;
		vector<string> words_ai, words_ar, words_am, words_ap;
		for (linesPtr++; linesPtr!=lines.end(); linesPtr++) {
			if (linesPtr->first != "") {
				//Person 삽입
				if (linesPtr->second[0] == "<Person>" ) {
					Person_name = linesPtr->second[1];
					Person_email = linesPtr->second[2];
					words_ai = { "ai",Person_name,Person_email };
					ai_insrtPerson(words_ai, people);
				}
				else if(linesPtr->first == "No Person added") {
					cout << "No Person added" << endl;
				}
				//Room 삽입
				else if (linesPtr->second[0] == "[Room") {
					roomId = linesPtr->second[1];
					roomId.erase(roomId.find("]"));
					words_ar = { "ar",roomId };
					ar_insrtRoom(words_ar, roomList);
				}
				else if (linesPtr->first == "No Room Exist") {
					cout << "No Room Exist" << endl;
				}
				//Meeting 삽입
				else if (linesPtr->second[0] == "<Meeting>") {	
					day = linesPtr->second[1];
					startTime = linesPtr->second[2];
					endTime = linesPtr->second[3];
					topic = linesPtr->second[4];
					words_am = { "am",roomId, day,startTime,endTime,topic };
					am_insrtMeeting(words_am, roomList);
				}
				//Participation 삽입
				else if (linesPtr->second[0] == "<Participation>") {	
					name = linesPtr->second[1];
					email = linesPtr->second[2];
					words_ap = { "ap",roomId,day,startTime,name };
					ap_insrtParticipation(words_ap, roomList, people);
				}
			}
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}