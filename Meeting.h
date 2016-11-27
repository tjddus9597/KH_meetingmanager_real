#pragma once
#include "Person.h"
#include<iostream>
#include<unordered_map>
#include<string>

using namespace std;

class Meeting
{
private:
	unordered_map<string, auto_ptr<Person>> Participation;
	string topic;
	string day;
	double startTime;
	double endTime;

public:
	Meeting(string topic_, string day_, double startTime_, double endTime_);
	void insrtParticipation(unordered_map<string, auto_ptr<Person>>& People, string name);
	string getTopic() const;
	string getDay() const;
	double getsStartTime() const;
	double getEndTime() const;
	auto_ptr<Person> getParticipation(string name_);
	void setTopic(const string new_topic);
	void setDay(const string new_day);
	void setStartTime(const double new_startTime);
	void setEndTime(const double new_endTime);

	~Meeting();
};

