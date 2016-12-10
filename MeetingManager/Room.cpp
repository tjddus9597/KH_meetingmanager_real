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

/*meeting ���̵� ����Ѵ�.
* �̴� meetingList�� key������ Ȱ��ȴ�.
*/
string Room::getMeetingId(string day, double startTime)
{
	return day + "_" + to_string(startTime);
}

/*RoomId ��ȯ
*/
double Room::getRoomId()
{
	return m_roomId;
}

/*�ش� �ð� ������ meeting�� �����ϴ����� �˻��Ѵ�.
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

/*meeting�� �߰��Ѵ�.
* �ð��� ��ġ���� Ȯ���� �ʿ��ϴ�.
*/
bool Room::addMeeting(string day, double startTime, double endTime, string topic)
{	
	//meeting �ð� ��ġ���� Ȯ��
	if (isMeeting(day,startTime,endTime)) {
		cerr << "There is already a meeting at that time!\n";
		return true;//�̹� ������ �ִٸ� true
	}
	//meeting ����(meetingId ����) �� m_meetingList�� �Ҵ�
	else {
		Meeting newMeeting(day, startTime, endTime, topic);
		m_meetingList.emplace(getMeetingId(day, startTime), newMeeting);
		return false;
	}
}

/*meeting�� �����Ѵ�. 
* �ش� meeting�� �����ϴ��� Ȯ���Ѵ�.
*/
void Room::delMeeting(string day, double startTime)
{
	//meeting ���� Ȯ��
	if (m_meetingList.find(getMeetingId(day, startTime)) == m_meetingList.end()) {
		throw "No meeting for such day, time is founded \n";
	}
	//meeting ����
	else
		m_meetingList.erase(getMeetingId(day, startTime));
}

unordered_map<string, Meeting>& Room::getMeetingList() {
	return m_meetingList;
}

/*�ش��ϴ� meeting�� ��ȯ�Ѵ�. 
* �ش� meeting�� �����ϴ��� Ȯ���Ѵ�.
*/
Meeting& Room::getMeeting(string day, double startTime)
{
	//meeting ���� Ȯ��
	if (m_meetingList.find(getMeetingId(day, startTime)) == m_meetingList.end()) {
		cout << "No room with that number!" << endl;
		throw runtime_error("nosuchroom");
	}
	//meeting ��ȯ
	else
		return m_meetingList.find(getMeetingId(day, startTime))->second;
}

Room::~Room()
{
	if (!m_meetingList.empty())
		m_meetingList.clear();
}
