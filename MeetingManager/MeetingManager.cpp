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
#include"MeetingManager.h"
#include<time.h>

bool simulation(unordered_map<int, Room>& roomList, unordered_map<string, Person>& people, int MaximumMeeting)
{
	//��ɾ� �Է�
	string command;
	cout << "Enter a command : ";
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
		isQuit = am_insrtMeeting(words, roomList,MaximumMeeting);
	}
	else if (words[0] == "ai") {
		isQuit = ai_insrtPerson(words, people);
	}
	else if (words[0] == "ap") {
		isQuit = ap_insrtParticipation(words, roomList, people);
	}
	else if (words[0] == "ag") {
		isQuit = ag_addGroup(words, roomList, people,MaximumMeeting);
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
	else if (words[0] == "pt") {
		isQuit = pt_printMaximumMeetingTime(words, MaximumMeeting);
	}
	else if (words[0] == "rm") {
		isQuit = rm_replaceMeeting(words, roomList);
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
		isQuit = dp_delParticipation(words, roomList, people);
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
		isQuit = sd_saveFile(words, roomList, people,MaximumMeeting);
	}
	else if (words[0] == "ld") {
		isQuit = ld_loadFile(words, roomList, people,MaximumMeeting);
	}
	else {
		cerr << "Unrecognized command!\n";
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

inline bool isDay(string& day)
{
	if (day == "M") { return false; }
	else if (day == "T") { return false; }
	else if (day == "W") { return false; }
	else if (day == "Th") { return false; }
	else if (day == "F") { return false; }
	else if (day == "Sa") { return false; }
	else if (day == "Su") { return false; }
	else { return true; }
}

inline bool isTime(int time)
{
	if (0 <= time && time < 24) { return false; }
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
		cerr << "Invalid command : wrong input number \n";
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
		cerr << "Invalid command : wrong input number \n";
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
			cout << "No room with that number!\n";
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

bool pm_printMeeting(vector<string>& words, unordered_map<int, Room>& roomList)
{
	try {
		if (isCmNum(words, 4)) {
			int roomId = stoi(words[1]);
			if (roomId < 0) { throw out_of_range("Minus"); }
			string day = words[2];
			if (isDay(day)) { throw invalid_argument("day"); }
			int startTime = stoi(words[3]);
			if(isTime(startTime)) { throw invalid_argument("Time"); }
			unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
			if (roomPtr == roomList.end()) {
				cout << "No room with that number!\n";
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
		int meetingNum = 0;
		int roomNum = 0;
		for (auto& roomElements : roomList) {
			meetingNum += static_cast<int>(roomElements.second.getMeetingList().size());
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
			}
			else {
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
		int meetingNum = 0;
		for (auto& roomElement : roomList) {
			meetingNum += static_cast<int>(roomElement.second.getMeetingList().size());
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

bool pt_printMaximumMeetingTime(vector<string>& words, int MaximumMeeting)
{
	if (isCmNum(words, 1)) {
		cout << "Maximum Meeting Time is " << MaximumMeeting << endl;
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
	return false; //�ٽ� ��ɾ� �Է� ����
}

//ȸ�� �߰� �Լ�
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList,int MaximumMeeting)
{
	int roomId;
	string day;
	int startTime;
	int endTime;
	string topic;
	try {
		if (isCmNum(words, 6)) {
			roomId = stoi(words[1]);
			day = words[2];
			if (isDay(day)) { throw invalid_argument("Day"); }
			startTime = stoi(words[3]);
			if (isTime(startTime)) { throw invalid_argument("Time"); }
			endTime = stoi(words[4]);
			if (isTime(endTime)) { throw invalid_argument("Time"); }
			topic = words[5];
			unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
			if (roomPtr == roomList.end()) {
				cout << "No room with that number!\n";
				return false;
			}
			if (endTime <= startTime) {
				cout << "Endtime is faster (or same) as start time" << endl;
				return false;
			}
			if (endTime - startTime > MaximumMeeting) {
				cout << "The maximum meeting time has been exceeded." << endl;
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
		cerr << "Invalid argument : " << endl;
	}

	return false; //�ٽ� ��ɾ� �Է� ����
}

//�Լ� �߰� �Լ� �����ε�
bool am_insrtMeeting(int roomId_, string day_, int startTime_, int endTime_,string topic_, unordered_map<int, Room>& roomList, int MaximumMeeting)
{
	unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId_);
	if (roomPtr == roomList.end()) {
		cout << "No room with that number!\n";
		return false;
	}
	if (roomPtr->second.addMeeting(day_, startTime_, endTime_, topic_)) {
		return false;
	}
	if (endTime_ - startTime_ >= MaximumMeeting) {
		cout << "The maximum meeting time has been exceeded." << endl;
		return false;
	}
	cout << "Meeting added at" << day_ << " " << startTime_ << endl;
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
			int time = stoi(words[3]);
			if (isTime(time)) { throw invalid_argument("Time"); }
			string name = words[4];
			unordered_map<int, Room>::iterator roomPtr = roomList.find(roomId);
			if (roomPtr == roomList.end()) {
				cout << "No room with that number!\n";
				return false;
			}
			for (auto roomElement : roomList) {
				auto MeetingList = roomElement.second.getMeetingList();
				for (auto MeetingPtr = MeetingList.begin(); MeetingPtr != MeetingList.end(); ++MeetingPtr) {
					if ((roomId != roomElement.first) && (day == MeetingPtr->second.getDay())
						&& (!(time >= MeetingPtr->second.getEndTime() || roomList.find(roomId)->second.getMeeting(day,time).getEndTime()<= MeetingPtr->second.getStartTime()))
						&& MeetingPtr->second.getParticipation().find(name) != MeetingPtr->second.getParticipation().end()) {			
						cout << "Participation in other rooms can not exist at the same time." << endl;							// �ٸ� ��, ���� �ð��� Participation�� ���� �߻�
						return false;
					}
				}
			}
			if (roomPtr->second.getMeeting(day, time).addParticipation(people, name)) {
				return false;	// ���� �߻�
			}
			cout << "Participation "<< name << " added \n";
		}
		else {
			cerr << "Invalid command : wrong input number \n";
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

bool ag_addGroup(vector<string>& words, unordered_map<int,Room>& roomList, unordered_map<string, Person>& people, int MaximumMeeting)
{	
	try {
		if (!(isCmNum(words, 0) || isCmNum(words, 1) || isCmNum(words, 2) || isCmNum(words,3) || isCmNum(words, 4))) {
			int roomId = stoi(words[1]);
			if (roomId < 0) { throw out_of_range("Minus"); }
			int timeLength = stoi(words[2]);
			if (isTime(timeLength)) { throw invalid_argument("Time"); }
			string topic = words[3];
			vector<string>::iterator it = words.begin();
			vector<string> nameList;
			it += 4;
			for (; it == words.end(); ++it) {
				if (people.find(*it) == people.end()) {
					cerr << "No person with that name!" << endl;
					return false;
				}
				nameList.emplace_back(*it);
			}
			if (roomList.find(roomId) == roomList.end()) {
				cerr << "No room with that number!" << endl;
				return false;
			}
			auto roomPtr = roomList.find(roomId);

			//���� �ð�,���� �޾ƿ���.
			const string DAY[] = { "Su", "M", "T", "W", "Th", "F", "Sa" };
			time_t rawtime;
			struct tm timeinfo;
			time(&rawtime);
			localtime_s(&timeinfo, &rawtime);
			int wday = timeinfo.tm_wday;
			int time = timeinfo.tm_hour;
			string day = DAY[wday];

			//���� ���� ���� ����
			struct meetingChoice {
				string c_day;
				int c_startTime;
				int c_endTime;
			};
			vector<meetingChoice> chosenMeeting(3);


			bool hasMeeting = false;
			int count = 0;

			//����
			int _startTime = time+1;
			if (_startTime < 9) {
				_startTime = 9;
			}
			int _endTime = _startTime + timeLength;
			for (; _endTime < 19; ++_startTime) {
				_endTime = _startTime + timeLength;
				if (!(roomPtr->second.isMeeting(day, _startTime, _endTime))) {	//��� �ð��� �ִٸ�
					for (auto& name:nameList) {	//���� ���� �����ڵ鿡 ���ؼ�
						if (ag_subParOverlap(roomList, roomId, day, _startTime, _endTime, name)) {
							hasMeeting = true;
							break;
						}
					}
					if (!hasMeeting) {
						chosenMeeting[count].c_day = day;
						chosenMeeting[count].c_startTime = _startTime;
						chosenMeeting[count].c_endTime = _endTime;
						++count;
						break;
					}
				}
				hasMeeting = false;
			}

			//����������
			++wday;
			for (;!((wday > 6)||(count >= 3));++wday) {
				int startTime = 9;
				int endTime = startTime + timeLength;
				for (; ((endTime < 19)&&(count < 3)); ++startTime) {
					endTime = startTime + timeLength;
					if (!(roomPtr->second.isMeeting(DAY[wday], startTime, endTime))) {	//��� �ð��� �ִٸ�
						for (auto& name : nameList) {	//���� ���� �����ڵ鿡 ���ؼ�
							if (ag_subParOverlap(roomList, roomId, DAY[wday], startTime, endTime, name)) {
								hasMeeting = true;
								break;
							}
						}
						if (!hasMeeting) {
							chosenMeeting[count].c_day = DAY[wday];
							chosenMeeting[count].c_startTime = startTime;
							chosenMeeting[count].c_endTime = endTime;
							++count;
							break;
						}
					}
					hasMeeting = false;
				}
			}
			//���
			cout << "Possible meeting time:" << endl;
			if (count == 0) {
				cout << "No possible meeting!\n";
				return false;
			}

			for (int n = 0; n < count; ++n) {
				cout << n + 1 << ". " << chosenMeeting[n].c_day << " " << chosenMeeting[n].c_startTime << "-" 
					<< chosenMeeting[n].c_endTime <<endl;
			}

			cout << "What to add meeting (n";
			for (int n = 0; n < count; ++n) {
				cout << "/" << n + 1;
			}
			cout << ")?" << endl;

			string choice;
			while (1) {
				//for (auto& person : nameList) {
				//	cout << person << endl;
				//}
				getline(cin, choice);
				if (choice == "n") {
					cout << "Command canceled" << endl;
					break;
				}
				else if (choice == "1") {
					vector<string> newWord_am = { "am",to_string(roomId),chosenMeeting[0].c_day,to_string(chosenMeeting[0].c_startTime),to_string(chosenMeeting[0].c_endTime), topic };
					am_insrtMeeting(newWord_am, roomList, MaximumMeeting);
					for (auto& person : nameList) {
						vector<string> newWord_ap = { "ap",to_string(roomId),chosenMeeting[0].c_day,to_string(chosenMeeting[0].c_startTime), person};
						ap_insrtParticipation(newWord_ap, roomList, people);
					}
					break;
				}
				else if ((choice == "2") && (count >= 2)) {
					vector<string> newWord_am = { "am",to_string(roomId),chosenMeeting[1].c_day, to_string(chosenMeeting[1].c_startTime),to_string(chosenMeeting[1].c_endTime), topic };
					am_insrtMeeting(newWord_am, roomList, MaximumMeeting);
					for (auto& person : nameList) {
						vector<string> newWord_ap = { "ap",to_string(roomId),chosenMeeting[1].c_day,to_string(chosenMeeting[1].c_startTime), person };
						ap_insrtParticipation(newWord_ap, roomList, people);
					}
					break;
				}
				else if ((choice == "3") && (count >= 3)) {
					vector<string> newWord_am = { "am", to_string(roomId),chosenMeeting[2].c_day, to_string(chosenMeeting[2].c_startTime),to_string(chosenMeeting[2].c_endTime), topic };
					am_insrtMeeting(newWord_am, roomList, MaximumMeeting);
					for (auto& person : nameList) {
						vector<string> newWord_ap = { "ap",to_string(roomId),chosenMeeting[2].c_day,to_string(chosenMeeting[2].c_startTime), person };
						ap_insrtParticipation(newWord_ap, roomList, people);
					}
					break;
				}
				else {
					cerr << "Invalid command" << endl;
				}
			}
		}
		else {
			cerr << "Invalid command : wrong input number" << endl;
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

bool ag_subParOverlap(unordered_map<int, Room>& roomList,int roomId, string day, int startTime, int endTime, string name)
{
	for (auto roomElement : roomList) {
		auto MeetingList = roomElement.second.getMeetingList();
		for (auto MeetingPtr = MeetingList.begin(); MeetingPtr != MeetingList.end(); ++MeetingPtr) {
			if ((roomId != roomElement.first) && (day == MeetingPtr->second.getDay()) && !((startTime >= MeetingPtr->second.getEndTime())
				|| (endTime <= MeetingPtr->second.getStartTime())) && MeetingPtr->second.getParticipation().find(name) != MeetingPtr->second.getParticipation().end()) {
				return true; // �ٸ� ��, ���� �ð��� Participation�� ���� �߻�
			}
		}
	}
	return false;
}

bool rm_replaceMeeting(vector<string>& words, unordered_map<int, Room>& roomList)
{
	try {
		if (isCmNum(words, 7)) {
			int oldRoomId = stoi(words[1]);
			if (oldRoomId < 0) { throw out_of_range("Minus"); }
			string oldDay = words[2];
			if (isDay(oldDay)) { throw invalid_argument("day"); }
			int oldStartTime = stoi(words[3]);
			if (isTime(oldStartTime)) { throw invalid_argument("Time"); }
			int newRoomId = stoi(words[4]);
			if (newRoomId < 0) { throw out_of_range("Minus"); }
			string newDay = words[5];
			if (isDay(newDay)) { throw invalid_argument("day"); }
			int newStartTime = stoi(words[6]);
			if (isTime(newStartTime)) { throw invalid_argument("Time"); }
			unordered_map<int, Room>::iterator oldRoomPtr = roomList.find(oldRoomId);
			if (oldRoomPtr == roomList.end()) {
				cout << "No room with that number!\n";
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
				cout << "No room with that number!\n";
				return false;
			}

			if ((newRoomPtr->second.isMeetingEx(oldDay, oldStartTime, newDay, newStartTime, newEndTime))) {
					cerr << "There is already a meeting at that time!\n";
					return false;
			}
			
			//���� �� �߰� ���� Code
			dm_delMeeting(oldRoomId, oldDay, oldStartTime, roomList);
			newRoomPtr->second.addMeeting(newDay, newStartTime, newEndTime, Topic);
			newRoomPtr->second.getMeeting(newDay, newStartTime).acceptParticipation(ParList);
			cout << "Meeting rescheduled to room " << newRoomId << " at " << newDay << " " << newStartTime << endl;
			return false;
		}
		else {
			cerr << "Invalid command : wrong input number \n";
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
di name: Ư�� ����� � ȸ�ǿ��� �������� �ʾ��� ��� ����. ����: Ư�� �̸��� �ش��ϴ� ����� ���� ��, 1�� �̻� ȸ�ǿ� �������� ��
*/
bool di_delPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	if (isCmNum(words, 2)) {
		string name = words[1];
		if (people.find(name) != people.end()) {	// people �ȿ� �̸��� name�� person�� �����ϸ�
			for (auto roomPtr = roomList.begin(); roomPtr != roomList.end(); roomPtr++) {
				for (auto meetingPtr = roomPtr->second.getMeetingList().begin(); meetingPtr != roomPtr->second.getMeetingList().end(); meetingPtr++) {
					auto PersonList = meetingPtr->second.getParticipation();
					if (PersonList.find(name) == PersonList.end()) {	// Ư�� ȸ�ǿ��� �������� �ʾ��� ���
					}
					else {
						cout << "This person is a participant in a meeting!" << endl;
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
dr room: Ư�� ���ȣ ȸ�ǽǰ� �� �濡 �ִ� ��� ȸ�Ǹ� ����. ����: ���ȣ�� ������ ����� ��, ���ȣ�� �ش��ϴ� ȸ�ǽ��� ���� ��
*/

bool dr_delRoom(vector<string>& words, unordered_map<int, Room>& roomList) {
	try {
		if (isCmNum(words, 2)) {
			int roomId = stoi(words[1]);
			if (roomId < 0) { throw out_of_range("Minus"); }
			auto roomPtr = roomList.find(roomId);
			if (roomPtr != roomList.end()) {	//roomList�� ���ȣ�� roomId�� ���� �����ϸ�
				if (!roomPtr->second.getMeetingList().empty()) {	//�濡 meeting�� �����ϸ�
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

/*dm room day time: ���� ����. ����: ���ȣ ������ ��� ��, ���ȣ�� �ش��ϴ� ȸ�ǽ��� ���� ��, Ư�� �ð��� ȸ�ǰ� ���� ��*/

bool dm_delMeeting(vector<string>& words, unordered_map<int, Room>& roomList) {
	try {
		if (isCmNum(words, 4)) {
			int roomId = stoi(words[1]);
			string day = words[2];
			int time = stoi(words[3]);
			if (isTime(time)) { throw invalid_argument("Time"); }
			auto roomPtr = roomList.find(roomId);
			if (roomPtr != roomList.end()) {	//roomList�� ���ȣ�� roomId�� ���� �����ϸ�
				auto& meetingList = roomPtr->second.getMeetingList();	//	���ø���Ʈ
				auto meetingId = roomPtr->second.getMeetingId(day, time);
				if (meetingList.find(meetingId) != meetingList.end()) {		// Ư�� �ð��� ȸ�ǰ� �ִٸ�
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
/*dm �����ε� �Լ�. dm romm day startTime�� ���� �Է� �޴´�.
*/
bool dm_delMeeting(int roomId_, string day_, int startTime_, unordered_map<int, Room>& roomList) {
	int roomId = roomId_;
	string day = day_;
	int time = startTime_;
	auto roomPtr = roomList.find(roomId);
	if (roomPtr != roomList.end()) {	//roomList�� ���ȣ�� roomId�� ���� �����ϸ�
		auto& meetingList = roomPtr->second.getMeetingList();	//	���ø���Ʈ
		auto meetingId = roomPtr->second.getMeetingId(day, time);
		if (meetingList.find(meetingId) != meetingList.end()) {		// Ư�� �ð��� ȸ�ǰ� �ִٸ�
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

/*dp room day time name: Ư�� ����� ���� �����ڿ��� ����. 
����: ���ȣ ������ ��� ��, ���ȣ�� �ش��ϴ� ȸ�ǽ��� ���� ��,
Ư���ð��� ȸ�ǰ� ���� ��, Ư�� ����� ȸ�� �����ڰ� �ƴ� ��*/

bool dp_delParticipation(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people) {
	try {
		if (isCmNum(words, 5)) {
			int roomId = stoi(words[1]);
			if (roomId < 0) { throw out_of_range("Minus"); }
			string day = words[2];
			if (isDay(day)) { throw invalid_argument("day"); }
			int time = stoi(words[3]);
			if (isTime(time)) { throw invalid_argument("Time"); }
			string name = words[4];
			auto roomPtr = roomList.find(roomId);
			if (people.find(name) == people.end()) {							// name�̶�� �̸��� ���� ����� ���ٸ�
				cerr << "No person with that name!" << endl;
				return false;
			}
			if (roomPtr != roomList.end()) {									// roomList�� ���ȣ�� roomId�� ���� �����ϸ�
				auto& meetingList = roomPtr->second.getMeetingList();			// ���ø���Ʈ
				auto meetingId = roomPtr->second.getMeetingId(day, time);
				if (meetingList.find(meetingId) != meetingList.end()) {			// Ư�� �ð��� ȸ�ǰ� �ִٸ�
					auto& participation = meetingList.find(meetingId)->second.getParticipation();
					if (participation.find(name) != participation.end()) {		// �̸��� name�� participation�� �ִٸ�
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

/* ds: ��� ȸ�Ǹ� ����. ����: ���� */

bool ds_delAllMeeting(vector<string>& words, unordered_map<int, Room>& roomList) {
	if (isCmNum(words, 1)) {
		for (auto roomPtr = roomList.begin(); roomPtr != roomList.end(); roomPtr++) {
			roomPtr->second.getMeetingList().clear();		//��� ȸ�� ����
		}
		cout << "All meetngs deleted" << endl;
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
					cerr << "Cannot clear people list unless there are no meetings!" << endl;
					return false;
				}
			}
		}
		if (noOneAttend = true) {
			people.clear();		// ��� ���� ����
			cout << "All persons deleted" << endl;
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
		cout << "All rooms are deleted \nAll meetngs deleted\nAll persons deleted" << endl;
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

/*sd filename: ���� ȸ�ǽ�, ���, ȸ�ǿ� ���� ������ ���Ͽ� ����. ����: �����̸��� �ش��ϴ� ������ ������ ���� ��*/

bool sd_saveFile(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people, int MaximumMeeting) {
	if (isCmNum(words, 2)) {
		string filename = words[1]+".txt";
		ofstream os;
		os.open(filename);
		//��� ���� ���
		cout << "[MaximumMeetingTime " << MaximumMeeting << "]" << endl;
		os << "[MaximumMeetingTime " << MaximumMeeting << "]" << endl;
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
		//ȸ�ǽ� ���� ���
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
		//ȸ�� ���� ���
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
		os.close();
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}

bool ld_loadFile(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people,int& MaximumMeeting) {
	if (isCmNum(words, 2)) {
		string filename = words[1] + ".txt";
		string command;
		ifstream is;
		is.open(filename);
		vector<pair<string, vector<string>>> lines;
		if (is.fail()) {																			// ���� �������� ������ ���� �߻�			
			cerr << "The file does not exist!" << endl;
			return false;
		}
		// ���� �۾� ����
		roomList.clear();	// ��� ȸ�ǽ�, ȸ�� ����
		people.clear();		// ��� ���� ����
		while (!is.eof()) {
			getline(is, command);
			istringstream is{ command };
			vector<string> tokens{ istream_iterator<string> {is},istream_iterator<string> {} }; 	// ��ɾ� ��ūȭ
			lines.push_back({ command,tokens });
		}
		vector<pair<string, vector<string>>> ::iterator linesPtr = lines.begin();
		if (linesPtr->second[0] != "[MaximumMeetingTime") {
			cerr << "The file to import does not match the save format!" << endl;
			return false;
		}
		// �ִ� ȸ�ǽð� �ҷ�����
		string MaximumMeetingTime;
		MaximumMeetingTime = linesPtr->second[1];
		MaximumMeetingTime.erase(MaximumMeetingTime.find("]"));
		MaximumMeeting = stoi(MaximumMeetingTime);
		cout << "Maximum Meeting time is " << MaximumMeeting << endl;
		// People �ҷ�����
		string Person_name, Person_email;
		string roomId, day, startTime, endTime, topic, name, email;
		vector<string> words_ai, words_ar, words_am, words_ap;
		for (linesPtr+2; linesPtr!=lines.end(); linesPtr++) {
			if (linesPtr->first != "") {
				//Person ����
				if (linesPtr->second[0] == "<Person>" ) {
					Person_name = linesPtr->second[1];
					Person_email = linesPtr->second[2];
					words_ai = { "ai",Person_name,Person_email };
					ai_insrtPerson(words_ai, people);
				}
				else if(linesPtr->first == "No Person added") {
					cout << "No Person added" << endl;
				}
				//Room ����
				else if (linesPtr->second[0] == "[Room") {
					roomId = linesPtr->second[1];
					roomId.erase(roomId.find("]"));
					words_ar = { "ar",roomId };
					ar_insrtRoom(words_ar, roomList);
				}
				else if (linesPtr->first == "No Room Exist") {
					cout << "No Room Exist" << endl;
				}
				//Meeting ����
				else if (linesPtr->second[0] == "<Meeting>") {	
					day = linesPtr->second[1];
					startTime = linesPtr->second[2];
					endTime = linesPtr->second[3];
					topic = linesPtr->second[4];
					words_am = { "am",roomId, day,startTime,endTime,topic };
					am_insrtMeeting(words_am, roomList, MaximumMeeting);
				}
				//Participation ����
				else if (linesPtr->second[0] == "<Participation>") {	
					name = linesPtr->second[1];
					email = linesPtr->second[2];
					words_ap = { "ap",roomId,day,startTime,name };
					ap_insrtParticipation(words_ap, roomList, people);
				}
			}
		}
		is.close();
	}
	else {
		cerr << "Invalid command : wrong input number \n";
	}
	return false;
}