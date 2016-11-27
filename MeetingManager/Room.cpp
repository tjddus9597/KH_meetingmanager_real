#include "stdafx.h"
#include "Room.h"
#include "meeting.h"
#include <unordered_map>
#include <string>
#include <iostream>

using namespace std;
Room::Room(int roomId):
	m_roomId(roomId)
{
	;
}

/*meeting 아이디를 계산한다.
* 이는 meetingList의 key값으로 활용된다.
*/
string Room::getMeetingId(string day, double startTime, double endTime)
{
	return day + "_" + to_string(startTime) + "_" + to_string(endTime);
}

/*해당 시간 구간에 meeting이 존재하는지를 검사한다.
*/
bool Room::isMeeting(string day, double startTime, double endTime)
{
	for (auto it = m_meetingList.begin(); it != m_meetingList.end(); ++it) {
		if (day != it->second.getDay() && (startTime < it->second.getEndTime()) && (endTime > it->second.getStartTime()))
			return true;
	}
	return false;
}

/*meeting을 추가한다.
* 시간이 겹치는지 확인이 필요하다.
*/
void Room::addMeeting(string day, double startTime, double endTime, string topic)
{	
	//meeting 시간 겹치는지 확인
	if (isMeeting(day,startTime,endTime)) {
		cerr << "There is other meeting at this time \n";
	}
	//meeting 생성(meetingId 생성) 및 m_meetingList에 할당
	else {
		Meeting newMeeting(day, startTime, endTime, topic);
		m_meetingList.emplace(getMeetingId(day, startTime, endTime), newMeeting);
	}
}

/*meeting을 삭제한다. 
* 해당 meeting이 존재하는지 확인한다.
*/
void Room::delMeeting(string day, double startTime, double endTime)
{
	//meeting 존재 확인
	if (m_meetingList.find(getMeetingId(day, startTime, endTime)) == m_meetingList.end()) {
		throw "No meeting for such day, time is founded \n";
	}
	//meeting 삭제
	else
		m_meetingList.erase(getMeetingId(day, startTime, endTime));
}

/*해당하는 meeting을 반환한다. 
* 해당 meeting이 존재하는지 확인한다.
*/
Meeting& Room::getMeeting(string day, double startTime, double endTime)
{
	//meeting 존재 확인
	if (m_meetingList.find(getMeetingId(day, startTime, endTime)) == m_meetingList.end()) {
		throw "No meeting for such day, time is founded \n";
	}
	//meeting 반환
	else
		return m_meetingList.find(getMeetingId(day, startTime, endTime))->second;
}

Room::~Room()
{
	if (!m_meetingList.empty())
		m_meetingList.clear();
}
