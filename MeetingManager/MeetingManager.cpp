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

inline bool isCmNum(vector<string>& words, int validNum);																		//��ɾ� ���� Ȯ�� �Լ�
bool qq_Quit(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList);												 	    //ar ��ɾ� ó�� �Լ�
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList);													//am ��ɾ� ó�� �Լ�
bool am_insrtMeeting(int roomId_, string day_, double startTime_, double endTime_, string topic_, unordered_map<int, Room>& roomList);
bool ai_insrtPerson(vector<string>& words, unordered_map<string, Person>& people);													//ai ��ɾ� ó�� �Լ�
bool ap_insrtParticipation(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);		//ap ��ɾ� ó�� �Լ�
bool pi_printPerson(vector<string>& words, unordered_map<string, Person>& people);
bool pr_printRoom(vector<string>& words, unordered_map<int, Room>& roomList);
bool pm_printMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool ps_printEveryMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool pg_printEveryPerson(vector<string>& words, unordered_map<string, Person>& people);
bool pa_printAll(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool rm_replaceMeeting(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool di_delPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);				//di ��ɾ� ó�� �Լ�
bool dr_delRoom(vector<string>& words, unordered_map<int, Room>& roomList);															//dr ��ɾ� ó�� �Լ�
bool dm_delMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool dm_delMeeting(int roomId_, string day_, double startTime_, unordered_map<int, Room>& roomList);
bool dp_delParticipation(vector<string>& words, unordered_map<int, Room>& roomList);
bool ds_delAllMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool dg_delAllPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool da_deleteAll(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);


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
	//��ɾ� �Է�
	string command;
	cout << "Enter your command : ";
	getline(cin, command);
	if (command == "") { return false; }
	istringstream is{ command };
	vector<string> words{ istream_iterator<string> {is},istream_iterator<string> {} }; 	//��ɾ� ��ūȭ


	bool isQuit = false;
	//��ɾ� �ؼ� �� ����
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
	else {
		cerr << "Wrong command\n";
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

bool qq_Quit(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people)
{
	if (isCmNum(words, 1)) {
		da_deleteAll(words, roomList, people);
		pa_printAll(words, roomList, people);
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
		cout << "[Room " << roomId <<"]"<< endl;
		unordered_map<string, Meeting>& meetingList = roomPtr->second.getMeetingList();
		for (auto& meetingElement : meetingList) {
			cout << ": " << meetingElement.second.getDay() << " " << meetingElement.second.getStartTime() << " " <<
				meetingElement.second.getEndTime() << " " << meetingElement.second.getTopic() << endl;
		}
	}
	else {
		cerr << "Invalid command : worng input number \n";
	}
	return false;
}

bool pm_printMeeting(vector<string>& words, unordered_map<int, Room>& roomList)
{
	try {
		if (isCmNum(words, 4)) {
			int roomId = stoi(words[1]);
			string day = words[2];
			double startTime = stod(words[3]);
			unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
			if (roomPtr == roomList.end()) {
				cout << "There's no such room\n";
				return false;
			}
			Meeting& meeting = roomPtr->second.getMeeting(day, startTime);
			cout << meeting.getDay() << " " << meeting.getStartTime() << " " << meeting.getEndTime() << " " << meeting.getTopic() << endl;
			unordered_map<string, Person>& parList = meeting.getParticipation();
			for (auto& personElement : parList) {
				cout << ": " << personElement.second.getName() << " " << personElement.second.getEmail() << endl;
			}
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
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
		for (auto& roomElements : roomList) {
			meetingNum += roomElements.second.getMeetingList().size();
		}
		if (meetingNum == 0) {
			cout << "No meeting Exist" << endl;
			return false;
		}
		for (auto& roomElement : roomList) {
			cout << "[Room " << roomElement.second.getRoomId() << "]" << endl;
			for (auto& meetingElement : roomElement.second.getMeetingList()) {
				cout << meetingElement.second.getDay() << " " << meetingElement.second.getStartTime() << " " << meetingElement.second.getEndTime() <<
					" " << meetingElement.second.getTopic() << endl;
				unordered_map<string, Person>& parList = meetingElement.second.getParticipation();
				for (auto& personElement : parList) {
					cout << ": " << personElement.second.getName() << " " << personElement.second.getEmail() << endl;
				}
			}
			cout << endl;
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
			cout << "No person added" << endl;
			return false;
		}
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
		int PersonNum = people.size();
		int RoomNum = roomList.size();
		double meetingNum = 0;
		if (PersonNum == 0 && RoomNum == 0) {
			cout << "No data " << endl;
			return false;
		}
		for (auto& roomElement : roomList) {
			meetingNum += roomElement.second.getMeetingList().size();
		}
		cout << "# of person  : " << PersonNum << endl;
		cout << "# of room    : " << RoomNum << endl;
		cout << "# of meeting : " << meetingNum << endl;
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

//�� �߰� ��ɾ� �Լ�
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList)
{
	int roomId;
	try {
		if (isCmNum(words, 2)) {
			roomId = stoi(words[1]);
			unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
			if (roomPtr != roomList.end()) {
				cout << "Room is already exist\n";
				return false;
			}
			roomList.emplace(roomId, Room(roomId));
			cout << "Room <" << roomId << "> (Added)\n";
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
	}
	catch (out_of_range) {
		cerr << "RoomId out of range" << endl;
	}
	return false; //�ٽ� ��ɾ� �Է� ����
}

//ȸ�� �߰� �Լ�
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
		if (endTime <= startTime) {
			cout << "Endtime is faster (or same) as starttime" << endl;
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

	return false; //�ٽ� ��ɾ� �Է� ����
}

//�Լ� �߰� �Լ� �����ε�
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
	cout << "Meeting <" << roomId_ << "> <" << day_ << "> <" << startTime_ << "> <" << endTime_ << "> <" << topic_ << "> (added) \n";
	return false; //�ٽ� ��ɾ� �Է� ����
}

//��� �߰� �Լ�
bool ai_insrtPerson(vector<string>& words, unordered_map<string, Person>& people)
{
	if (isCmNum(words, 3)) {
			string name;
			string email;
			name = words[1];
			email = words[2];
			if (people.find(name) != people.end()) {
				cout << "This person is already added" << endl;
				return false;
			}
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
				return false;	// ���� �߻�
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
	catch (out_of_range) {
		cerr << "Room ID out of range" << endl;
	}
		
	return false;
}
//����, runtime(��������) ĳġ �ؾ��Ѵ�.
bool rm_replaceMeeting(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people)
{
	try {
		if (isCmNum(words, 7)) {
			int oldRoomId = stoi(words[1]);
			string oldDay = words[2];
			double oldStartTime = stod(words[3]);
			int newRoomId = stoi(words[4]);
			string newDay = words[5];
			double newStartTime = stod(words[6]);
			unordered_map<int, Room>::iterator oldRoomPtr = roomList.find(oldRoomId);
			if (oldRoomPtr == roomList.end()) {
				cout << "There is no such room\n";
				return false;
			}
			string Topic = oldRoomPtr->second.getMeeting(oldDay, oldStartTime).getTopic();
			int oldEndTime = oldRoomPtr->second.getMeeting(oldDay, oldStartTime).getEndTime();
			int meetingTime = oldEndTime - oldStartTime;
			int newEndTime = newStartTime + meetingTime;
			unordered_map<string, Person> ParList = oldRoomPtr->second.getMeeting(oldDay, oldStartTime).getParticipation();
			unordered_map<int, Room>::iterator newRoomPtr = roomList.find(newRoomId);
			if (newRoomPtr == roomList.end()) {
				cout << "There is no such room\n";
				return false;
			}
			dm_delMeeting(oldRoomId, oldDay, oldStartTime, roomList);
			if (newRoomPtr->second.addMeeting(newDay, newStartTime, newEndTime, Topic)) {
				oldRoomPtr->second.addMeeting(oldDay, oldStartTime, oldEndTime, Topic);
				oldRoomPtr->second.getMeeting(oldDay, oldStartTime).acceptParticipation(ParList);
				cout << "Meeting <" << oldRoomId << "> <" << oldDay << "> <" << oldStartTime << "> <" << oldEndTime << "> <" << Topic << "> (added) \n";
				return false;
			}
			else {
				newRoomPtr->second.getMeeting(newDay, newStartTime).acceptParticipation(ParList);
				cout << "Meeting <" << newRoomId << "> <" << newDay << "> <" << newStartTime << "> <" << newEndTime << "> <" << Topic << "> (added) \n";
				return false;
			}
		}
		else {
			cerr << "Invalid command : worng input number \n";
		}
	}
	catch (runtime_error) {
		;
	}
	catch (out_of_range) {
		cerr << "Input number out of range" << endl;
	}
	return false;

}

/* 
di name: Ư�� ����� � ȸ�ǿ��� �������� �ʾ��� ��� ����. ����: Ư�� �̸��� �ش��ϴ� ����� ���� ��, 1�� �̻� ȸ�ǿ� �������� ��
*/
bool di_delPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	if (isCmNum(words, 2)) {
		string name = words[1];
		if (people.find(name) != people.end()) {	// people �ȿ� �̸��� name�� person�� �����ϸ�
			for (auto roomPtr = roomList.begin(); roomPtr != roomList.end(); roomPtr++) {
				if (roomPtr->second.getMeetingList().begin() == roomPtr->second.getMeetingList().end()) {
					people.erase(name);
					cout << "Person <" << name << "> (deleted) \n";
				}
				for (auto meetingPtr = roomPtr->second.getMeetingList().begin(); meetingPtr != roomPtr->second.getMeetingList().end(); meetingPtr++) {
					auto PersonList = meetingPtr->second.getParticipation();
					if (PersonList.find(name) == PersonList.end()) {	// Ư�� ȸ�ǿ��� �������� �ʾ��� ���
					}
					else {
						cout << name << " �� ȸ�ǿ� ���� ���Դϴ�." << endl;
						return false;
					}
				}
			}
			people.erase(name);
			cout << "Person <" << name << "> (deleted) \n";
		}
		else {
			cerr << "�̸��� " << name << " �� Person�� People�ȿ� ���� ���� �ʽ��ϴ�." << endl;
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*
dr room: Ư�� ���ȣ ȸ�ǽǰ� �� �濡 �ִ� ��� ȸ�Ǹ� ����. ����: ���ȣ�� ������ ����� ��, ���ȣ�� �ش��ϴ� ȸ�ǽ��� ���� ��
*/

bool dr_delRoom(vector<string>& words, unordered_map<int, Room>& roomList) {
	try {
		if (isCmNum(words, 2)) {
			int roomId = stoi(words[1]);
			auto roomPtr = roomList.find(roomId);
			if (roomPtr != roomList.end()) {	//roomList�� ���ȣ�� roomId�� ���� �����ϸ�
				if (!roomPtr->second.getMeetingList().empty()) {	//�濡 meeting�� �����ϸ�
					roomPtr->second.getMeetingList().clear();
				}
				roomList.erase(roomId);
				cout << "Room <" << roomId << "> (deleted) \n";
			}
			else {
				cerr << "���ȣ�� " << roomId << " �� Room�� ���� ���� �ʽ��ϴ�." << endl;
			}
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
	}
	catch (out_of_range) {
		cerr << "Room ID out of range" << endl;
	}
	return false;
}

/*dm room day time: ���� ����. ����: ���ȣ ������ ��� ��, ���ȣ�� �ش��ϴ� ȸ�ǽ��� ���� ��, Ư�� �ð��� ȸ�ǰ� ���� ��*/

bool dm_delMeeting(vector<string>& words, unordered_map<int, Room>& roomList) {
	if (isCmNum(words, 4)) {
		int roomId = stoi(words[1]);
		string day = words[2];
		double time = stod(words[3]);
		auto roomPtr = roomList.find(roomId);
		if (roomPtr != roomList.end()) {	//roomList�� ���ȣ�� roomId�� ���� �����ϸ�
			auto& meetingList = roomPtr->second.getMeetingList();	//	���ø���Ʈ
			auto meetingId = roomPtr->second.getMeetingId(day, time);
			if (meetingList.find(meetingId) != meetingList.end()) {		// Ư�� �ð��� ȸ�ǰ� �ִٸ�
				meetingList.erase(meetingId);
				cout << "Meeting <" << roomId << "> <" << day << "> <" << time << "> (deleted) \n";
			}
			else {
				cerr << roomId << " �濡 Day: " << day << " Time: " << time << " �� ȸ�ǰ� �������� �ʽ��ϴ�." << endl;
			}
		}
		else {
			cerr << "���ȣ�� " << roomId << " �� Room�� ���� ���� �ʽ��ϴ�." << endl;
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}
/*dm �����ε� �Լ�. dm romm day startTime�� ���� �Է� �޴´�.
*/
bool dm_delMeeting(int roomId_, string day_, double startTime_, unordered_map<int, Room>& roomList) {
	int roomId = roomId_;
	string day = day_;
	double time = startTime_;
	auto roomPtr = roomList.find(roomId);
	if (roomPtr != roomList.end()) {	//roomList�� ���ȣ�� roomId�� ���� �����ϸ�
		auto& meetingList = roomPtr->second.getMeetingList();	//	���ø���Ʈ
		auto meetingId = roomPtr->second.getMeetingId(day, time);
		if (meetingList.find(meetingId) != meetingList.end()) {		// Ư�� �ð��� ȸ�ǰ� �ִٸ�
			meetingList.erase(meetingId);
			cout << "Meeting <" << roomId << "> <" << day << "> <" << time << "> (deleted) \n";
		}
		else {
			cerr << roomId << " �濡 Day: " << day << " Time: " << time << " �� ȸ�ǰ� �������� �ʽ��ϴ�." << endl;
		}
	}
	else {
		cerr << "���ȣ�� " << roomId << " �� Room�� ���� ���� �ʽ��ϴ�." << endl;
	}
	return false;
}

/*dp room day time name: Ư�� ����� ���� �����ڿ��� ����. 
����: ���ȣ ������ ��� ��, ���ȣ�� �ش��ϴ� ȸ�ǽ��� ���� ��,
Ư���ð��� ȸ�ǰ� ���� ��, Ư�� ����� ȸ�� �����ڰ� �ƴ� ��*/

bool dp_delParticipation(vector<string>& words, unordered_map<int, Room>& roomList) {
	try {
		if (isCmNum(words, 5)) {
			int roomId = stoi(words[1]);
			string day = words[2];
			double time = stod(words[3]);
			string name = words[4];
			auto roomPtr = roomList.find(roomId);
			if (roomPtr != roomList.end()) {									// roomList�� ���ȣ�� roomId�� ���� �����ϸ�
				auto& meetingList = roomPtr->second.getMeetingList();			// ���ø���Ʈ
				auto meetingId = roomPtr->second.getMeetingId(day, time);
				if (meetingList.find(meetingId) != meetingList.end()) {			// Ư�� �ð��� ȸ�ǰ� �ִٸ�
					auto& participation = meetingList.find(meetingId)->second.getParticipation();
					if (participation.find(name) != participation.end()) {		// �̸��� name�� participation�� �ִٸ�
						participation.erase(name);
						cout << "Participation <" << roomId << "> <" << day << "> <" << time << "> <" << name << "> (deleted) \n";
					}
					else {
						cerr << "�̸��� " << name << " �� Participation�� �������� �ʽ��ϴ�." << endl;
					}
				}
				else {
					cerr << roomId << " �濡 Day: " << day << " Time: " << time << " �� ȸ�ǰ� �������� �ʽ��ϴ�." << endl;
				}
			}
			else {
				cerr << "���ȣ�� " << roomId << " �� Room�� ���� ���� �ʽ��ϴ�." << endl;
			}
		}
		else {
			cerr << "Invalid command : wrong input number \n";
		}
	}
	catch (out_of_range) {
		cerr << "Room ID out of range" << endl;
	}
	return false;
}

/* ds: ��� ȸ�Ǹ� ����. ����: ���� */

bool ds_delAllMeeting(vector<string>& words, unordered_map<int, Room>& roomList) {
	if (isCmNum(words, 1)) {
		for (auto roomPtr = roomList.begin(); roomPtr != roomList.end(); roomPtr++) {
			roomPtr->second.getMeetingList().clear();		//��� ȸ�� ����
		}
		cout << "��� ȸ�� ���� �Ϸ�" << endl;
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*dg: ��� ������ � ȸ�ǿ��� �������� �ʴ� ���, ��� ������ ����. ����: �����ڰ� ���Ե� ������ �ִ� ���*/

bool dg_delAllPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	if (isCmNum(words, 1)) {
		bool noOneAttend = true;
		for (auto roomPtr = roomList.begin(); roomPtr != roomList.end(); roomPtr++) {
			for (auto meetingPtr = roomPtr->second.getMeetingList().begin(); meetingPtr != roomPtr->second.getMeetingList().end(); meetingPtr++) {
				auto PersonList = meetingPtr->second.getParticipation();
				if (PersonList.begin() != PersonList.end()) {	// Ư�� ȸ�� �ȿ� ����� �ִ� ���
					noOneAttend = false;
					cerr << "�����ڰ� ���Ե� ������ ���� �մϴ�." << endl;
					return false;
				}
			}
		}
		if (noOneAttend = true) {
			people.clear();		// ��� ���� ����
			cout << "��� ���� ���� �Ϸ�" << endl;
		}
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*da: ��� ȸ�ǽ�, ��� ����, ȸ�ǿ� ���� ���� ����. ����: ����*/

bool da_deleteAll(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	if (isCmNum(words, 1)) {
		roomList.clear();	// ��� ȸ�ǽ�, ȸ�� ����
		people.clear();		// ��� ���� ����
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}