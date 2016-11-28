#pragma once
#include<string>
#include<unordered_map>
#include"Meeting.h"

using namespace std;
class Room
{
private:
	int m_roomId;
	unordered_map<string, Meeting> m_meetingList; //container for meetings
	bool isMeeting(string day, double starttime, double endtime);
public:
	Room(int roomid);
	string getMeetingId(string day, double starttime);
	unordered_map<string, Meeting>& getMeetingList();
	Meeting& getMeeting(string day, double starttime);
	bool addMeeting(string day, double starttime, double endtime, string topic);
	void delMeeting(string day, double starttime);
	~Room();
};

