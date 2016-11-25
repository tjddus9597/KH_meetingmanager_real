#pragma once
#include<string>
/*성연 code와 호환성 검사용
*/
using namespace std;
class Meeting
{
private:
	string m_meetingId;
	string m_day;
	double m_startTime;
	double m_endTime;
public: //디버깅용
	Meeting(string day, double startTime, double endTime, string topic, string meetingId) { };
	string getMeetingId() const { return m_meetingId; }
	string getDay() const { return m_day; }
	double getStartTime() const { return m_startTime; }
	double getEndTime() const { return m_endTime; }
};