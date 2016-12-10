#include "stdafx.h"
#include "Room.h"
#include "meeting.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <stdexcept>

using namespace std;
Room::Room(int roomId):
	m_roomId(roomId)
{
	;
}

/*meeting 아이디를 계산한다.
* 이는 meetingList의 key값으로 활용된다.
*/
string Room::getMeetingId(string day, double startTime)
{
	return day + "_" + to_string(startTime);
}

/*RoomId 반환
*/
double Room::getRoomId()
{
	return m_roomId;
}

/*해당 시간 구간에 meeting이 존재하는지를 검사한다.
*/
bool Room::isMeeting(string day, double startTime, double endTime)
{
	for (auto it = m_meetingList.begin(); it != m_meetingList.end(); ++it) {
		if (!((day != it->second.getDay()) || (startTime >= it->second.getEndTime()) || (endTime <= it->second.getStartTime()))) {
			return true;
		}
	}
	return false;
}

bool Room::isMeetingEx(string oldDay, double oldStartTime, string newDay, double newStartTime, double newEndTime)
{	
	for (auto it = m_meetingList.begin(); it != m_meetingList.end(); ++it) {
		if ((it != m_meetingList.find(getMeetingId(oldDay,oldStartTime)))&&(!((newDay != it->second.getDay()) ||
			(newStartTime >= it->second.getEndTime()) || (newEndTime <= it->second.getStartTime()))))
		{
			return true;
		}
	}
	return false;
}

/*meeting을 추가한다.
* 시간이 겹치는지 확인이 필요하다.
*/
bool Room::addMeeting(string day, double startTime, double endTime, string topic)
{	
	//meeting 시간 겹치는지 확인
	if (isMeeting(day,startTime,endTime)) {
		cerr << "There is already a meeting at that time!\n";
		return true;//이미 미팅이 있다면 true
	}
	//meeting 생성(meetingId 생성) 및 m_meetingList에 할당
	else {
		Meeting newMeeting(day, startTime, endTime, topic);
		m_meetingList.emplace(getMeetingId(day, startTime), newMeeting);
		return false;
	}
}

/*meeting을 삭제한다. 
* 해당 meeting이 존재하는지 확인한다.
*/
void Room::delMeeting(string day, double startTime)
{
	//meeting 존재 확인
	if (m_meetingList.find(getMeetingId(day, startTime)) == m_meetingList.end()) {
		throw "No meeting for such day, time is founded \n";
	}
	//meeting 삭제
	else
		m_meetingList.erase(getMeetingId(day, startTime));
}

unordered_map<string, Meeting>& Room::getMeetingList() {
	return m_meetingList;
}

/*해당하는 meeting을 반환한다. 
* 해당 meeting이 존재하는지 확인한다.
*/
Meeting& Room::getMeeting(string day, double startTime)
{
	//meeting 존재 확인
	if (m_meetingList.find(getMeetingId(day, startTime)) == m_meetingList.end()) {
		cout << "No room with that number!" << endl;
		throw runtime_error("nosuchroom");
	}
	//meeting 반환
	else
		return m_meetingList.find(getMeetingId(day, startTime))->second;
}

Room::~Room()
{
	if (!m_meetingList.empty())
		m_meetingList.clear();
}
