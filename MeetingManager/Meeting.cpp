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
	if (People.find(name) != People.end())	// �̸��� name�� Person�� �����ϸ�
	{
		Participation[name] = People.find(name)->second;
	}
	else {
		cout << "�̸��� " << name << " �� Person�� ���� ���� �ʽ��ϴ�." << endl;
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
