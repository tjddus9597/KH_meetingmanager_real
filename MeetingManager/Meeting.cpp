#include "stdafx.h"
#include "Meeting.h"


Meeting::Meeting(string day_, double startTime_, double endTime_, string topic_)
{
	m_topic = topic_;
	m_day = day_;
	m_startTime = startTime_;
	m_endTime = endTime_;
}

/*Participation안에 이름이 name인 person이 존재하는지를 검사한다.
*/
bool Meeting::isPerson(string name)
{
	for (auto it = m_Participation.begin(); it != m_Participation.end(); ++it) {
		if (name == it->second.getName())
		{
			return true;		//존재
		}
	}
	return false;				//존재하지 않음
}

bool Meeting::addParticipation(unordered_map<string, Person>& People, string name) {
	
	if (People.find(name) != People.end()) // People 안에 이름이 name인 Person이 존재하면(추가할 수 있다)
	{
		if (isPerson(name))	// Participation 안에 이름이 name인 Person이 이미 존재하면
		{
			cerr << "Participation 안에 "<< "이름이 " << name << " 인 Person이 이미 존재합니다." << endl;
			return true;	//오류 발생
		}
		else {
			m_Participation.emplace(name, People.find(name)->second);
			return false;	//오류 없음
		}
	}
	else {
		cerr << "People 안에 " << "이름이 " << name << " 인 Person이 존재 하지 않습니다." << endl;
		return true;	// 오류 발생
	}
}
//이미 존재하던 participation들을 받아오는 경우.
void Meeting::acceptParticipation(unordered_map<string, Person>& newPar) {
	m_Participation = newPar;
}


/*Participation을 삭제한다.
해당 Participation이 존재하는지 확인한다.
*/
void Meeting::delParticiaption(string name)
{
	//Person 존재 확인
	if(isPerson(name))
		cerr << "이름이 " << name << " 인 Person이 존재 하지 않습니다." << endl;
	//Person 삭제
	else {
		m_Participation.erase(name);
	}
}

/*해당하는 Participation을 반환한다.
해당 Participation이 존재하는지 확인한다.
*/
Person& Meeting::getParticipation(string name)
{
	//Person 존재 확인
	if (isPerson(name)) {
		cerr << "이름이 " << name << " 인 Person이 존재 하지 않습니다." << endl;
	}
	//Person 반환
	else
		return m_Participation[name];
	
}

unordered_map<string, Person>& Meeting::getParticipation() {
	return m_Participation;
}

string Meeting::getTopic() const {
	return m_topic;
}

string Meeting::getDay() const {
	return m_day;
}

double Meeting::getStartTime() const {
	return m_startTime;
}

double Meeting::getEndTime() const {
	return m_endTime;
}

void Meeting::setTopic(const string new_topic) {
	m_topic = new_topic;
}

void Meeting::setDay(const string new_day) {
	m_day = new_day;
}

void Meeting::setStartTime(const double new_startTime) {
	m_startTime = new_startTime;
}

void Meeting::setEndTime(const double new_endTime) {
	m_endTime = new_endTime;
}
