#pragma once
#include<iostream>
#include<unordered_map>
#include<string>
#include "Person.h"
using namespace std;

using namespace std;
class Meeting
{
private:
	unordered_map<string, Person> m_Participation; //container for Person
	string m_topic;
	string m_day;
	int m_startTime;
	int m_endTime;
public: 
	Meeting(string day_, int startTime_, int endTime_, string topic_);
	bool Meeting::isPerson(string name);
	bool addParticipation(unordered_map<string, Person>& People, string name);
	void Meeting::acceptParticipation(unordered_map<string, Person>& People);
	unordered_map<string, Person>& getParticipation();
	Person& getParticipation(string name);
	void delParticiaption(string name);
	string getTopic() const;
	string getDay() const;
	int getStartTime() const;
	int getEndTime() const;
	void setTopic(const string new_topic);
	void setDay(const string new_day);
	void setStartTime(const int new_startTime);
	void setEndTime(const int new_endTime);
};