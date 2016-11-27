#include "stdafx.h"
#include "Meeting.h"


Meeting::Meeting(string topic_, string day_, double startTime_, double endTime_)
{
	topic = topic_;
	day = day_;
	startTime = startTime_;
	endTime = endTime_;
}

void Meeting::insrtParticipation(unordered_map<string, auto_ptr<Person>>& People, string name) {
	if (People.find(name) != People.end())	// 이름이 name인 Person이 존재하면
	{
		Participation[name] = People.find(name)->second;
	}
	else {
		cout << "이름이 " << name << " 인 Person이 존재 하지 않습니다." << endl;
	}
}

string Meeting::getTopic() const {
	return topic;
}

string Meeting::getDay() const {
	return day;
}

double Meeting::getsStartTime() const {
	return startTime;
}

double Meeting::getEndTime() const {
	return endTime;
}

auto_ptr<Person> Meeting::getParticipation(string name){
	return Participation[name];
}


void Meeting::setTopic(const string new_topic) {
	topic = new_topic;
}

void Meeting::setDay(const string new_day) {
	day = new_day;
}

void Meeting::setStartTime(const double new_startTime) {
	startTime = new_startTime;
}

void Meeting::setEndTime(const double new_endTime) {
	endTime = new_endTime;
}

Meeting::~Meeting()
{
}
