#pragma once
#include<string>
/*���� code�� ȣȯ�� �˻��
*/
using namespace std;
class Meeting
{
private:
	string m_meetingId;
	string m_day;
	double m_startTime;
	double m_endTime;
public: //������
	Meeting(string day, double startTime, double endTime, string topic, string meetingId) { };
	string getMeetingId() const { return m_meetingId; }
	string getDay() const { return m_day; }
	double getStartTime() const { return m_startTime; }
	double getEndTime() const { return m_endTime; }
};