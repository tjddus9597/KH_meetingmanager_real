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

/*meeting ���̵� ����Ѵ�.
* �̴� meetingList�� key������ Ȱ��ȴ�.
*/
string Room::getMeetingId(string day, double startTime, double endTime)
{
	return day + "_" + to_string(startTime) + "_" + to_string(endTime);
}

/*�ش� �ð� ������ meeting�� �����ϴ����� �˻��Ѵ�.
*/
bool Room::isMeeting(string day, double startTime, double endTime)
{
	for (auto it = m_meetingList.begin(); it != m_meetingList.end(); ++it) {
		if (day != it->second.getDay() && (startTime < it->second.getEndTime()) && (endTime > it->second.getStartTime()))
			return true;
	}
	return false;
}

/*meeting�� �߰��Ѵ�.
* �ð��� ��ġ���� Ȯ���� �ʿ��ϴ�.
*/
void Room::addMeeting(string day, double startTime, double endTime, string topic)
{	
	//meeting �ð� ��ġ���� Ȯ��
	if (isMeeting(day,startTime,endTime)) {
		cerr << "There is other meeting at this time \n";
	}
	//meeting ����(meetingId ����) �� m_meetingList�� �Ҵ�
	else {
		Meeting newMeeting(day, startTime, endTime, topic);
		m_meetingList.emplace(getMeetingId(day, startTime, endTime), newMeeting);
	}
}

/*meeting�� �����Ѵ�. 
* �ش� meeting�� �����ϴ��� Ȯ���Ѵ�.
*/
void Room::delMeeting(string day, double startTime, double endTime)
{
	//meeting ���� Ȯ��
	if (m_meetingList.find(getMeetingId(day, startTime, endTime)) == m_meetingList.end()) {
		throw "No meeting for such day, time is founded \n";
	}
	//meeting ����
	else
		m_meetingList.erase(getMeetingId(day, startTime, endTime));
}

/*�ش��ϴ� meeting�� ��ȯ�Ѵ�. 
* �ش� meeting�� �����ϴ��� Ȯ���Ѵ�.
*/
Meeting& Room::getMeeting(string day, double startTime, double endTime)
{
	//meeting ���� Ȯ��
	if (m_meetingList.find(getMeetingId(day, startTime, endTime)) == m_meetingList.end()) {
		throw "No meeting for such day, time is founded \n";
	}
	//meeting ��ȯ
	else
		return m_meetingList.find(getMeetingId(day, startTime, endTime))->second;
}

Room::~Room()
{
	if (!m_meetingList.empty())
		m_meetingList.clear();
}
