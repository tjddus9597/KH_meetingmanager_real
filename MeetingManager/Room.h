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
	
public:
	Room(int roomid);
	bool isMeeting(string day, int starttime, int endtime);
	bool Room::isMeetingEx(string oldDay, int oldStartTime, string newDay, int newStartTime, int newEndTime);
	string getMeetingId(string day, int starttime);
	unordered_map<string, Meeting>& getMeetingList();
	Meeting& getMeeting(string day, int starttime);
	int getRoomId();
	bool addMeeting(string day, int starttime, int endtime, string topic);
	void delMeeting(string day, int starttime);
	~Room();
};

