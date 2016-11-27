#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include "Person.h"
using namespace std;
/*성연 code와 호환성 검사용
*/
using namespace std;
class Meeting
{
private:
	unordered_map<string, Person> m_Participation; //container for Person
	string m_topic;
	string m_day;
	double m_startTime;
	double m_endTime;
public: //디버깅용
	Meeting(string day_, double startTime_, double endTime_, string topic_);
	bool Meeting::isPerson(string name);
	void addParticipation(unordered_map<string, Person>& People, string name);
	Person& getParticipation(string name);
	void delParticiaption(string name);
	string getTopic() const;
	string getDay() const;
	double getStartTime() const;
	double getEndTime() const;
	void setTopic(const string new_topic);
	void setDay(const string new_day);
	void setStartTime(const double new_startTime);
	void setEndTime(const double new_endTime);
};