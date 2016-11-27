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

inline bool isCmNum(vector<string>& words, int validNum);																			//��ɾ� ���� Ȯ�� �Լ�
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList);												 	    //ar ��ɾ� ó�� �Լ�
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList);													//am ��ɾ� ó�� �Լ�
bool ai_insrtPerson(vector<string>& words, unordered_map<string, Person>& people);													//ai ��ɾ� ó�� �Լ�
bool ap_insrtParticipation(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);		//ap ��ɾ� ó�� �Լ�
bool pi_printPerson(vector<string>& words, unordered_map<string, Person>& people);
bool pr_printRoom(vector<string>& words, unordered_map<int, Room>& roomList);
bool pm_printMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
//bool ps_printEveryMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
//bool pg_printEveryPerson(vector<string>& words, unordered_map<string, Person>& people);
//bool pa_printAll(vector<string>& words, unordered_map<int, Room>& roomList);


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

//�� �߰� ��ɾ� �Լ�
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList)
{
	int roomId;
	if (isCmNum(words, 2)) {
		//roomId �ص� �� �˻�
		roomId = stoi(words[1]);
		roomList.emplace(roomId, Room(roomId));
		cout << "Room <" << roomId << "> (Added)\n";
	}
	else {
		cerr << "Invalid command : worng input number \n";
	}

	return false; //�ٽ� ��ɾ� �Է� ����
}



//ȸ�� �߰� �Լ� : ���� ���� ������
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
		cerr << "Invalid command : worng input number \n";
	}

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
			people.emplace(name, Person(name, email));
			cout << "Person <" << name << "> <" << email << "> (added)\n";
	}
	else {
		cerr << "Invalid command : worng input number \n";
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

bool ap_insrtParticipation(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	try {
		if (isCmNum(words, 5)) {
			int roomId = stoi(words[1]);
			string day = words[2];
			double time = stod(words[3]);
			string name = words[4];
			if (roomList.find(roomId)->second.getMeeting(day, time).addParticipation(people, name)) {
				return false;	// ���� �߻�
				cout << "Participation <" << roomId << "> <" << day << "> <" << time << "> <" << name << "> (added) \n";
			}
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
		for (auto meetingPtr = roomPtr->second.getMeetingList().begin(); meetingPtr != roomPtr->second.getMeetingList().end();++meetingPtr) {
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