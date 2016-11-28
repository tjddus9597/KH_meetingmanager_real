#include "stdafx.h"
#include "Meeting.h"


Meeting::Meeting(string day_, double startTime_, double endTime_, string topic_)
{
	m_topic = topic_;
	m_day = day_;
	m_startTime = startTime_;
	m_endTime = endTime_;
}

/*Participation�ȿ� �̸��� name�� person�� �����ϴ����� �˻��Ѵ�.
*/
bool Meeting::isPerson(string name)
{
	for (auto it = m_Participation.begin(); it != m_Participation.end(); ++it) {
		if (name == it->second.getName())
		{
			return true;		//����
		}
	}
	return false;				//�������� ����
}

bool Meeting::addParticipation(unordered_map<string, Person>& People, string name) {
	
	if (People.find(name) != People.end()) // People �ȿ� �̸��� name�� Person�� �����ϸ�(�߰��� �� �ִ�)
	{
		if (isPerson(name))	// Participation �ȿ� �̸��� name�� Person�� �̹� �����ϸ�
		{
			cerr << "Participation �ȿ� "<< "�̸��� " << name << " �� Person�� �̹� �����մϴ�." << endl;
			return true;	//���� �߻�
		}
		else {
			m_Participation.emplace(name, People.find(name)->second);
			return false;	//���� ����
		}
	}
	else {
		cerr << "People �ȿ� " << "�̸��� " << name << " �� Person�� ���� ���� �ʽ��ϴ�." << endl;
		return true;	// ���� �߻�
	}
}
//�̹� �����ϴ� participation���� �޾ƿ��� ���.
void Meeting::acceptParticipation(unordered_map<string, Person>& newPar) {
	m_Participation = newPar;
}


/*Participation�� �����Ѵ�.
�ش� Participation�� �����ϴ��� Ȯ���Ѵ�.
*/
void Meeting::delParticiaption(string name)
{
	//Person ���� Ȯ��
	if(isPerson(name))
		cerr << "�̸��� " << name << " �� Person�� ���� ���� �ʽ��ϴ�." << endl;
	//Person ����
	else {
		m_Participation.erase(name);
	}
}

/*�ش��ϴ� Participation�� ��ȯ�Ѵ�.
�ش� Participation�� �����ϴ��� Ȯ���Ѵ�.
*/
Person& Meeting::getParticipation(string name)
{
	//Person ���� Ȯ��
	if (isPerson(name)) {
		cerr << "�̸��� " << name << " �� Person�� ���� ���� �ʽ��ϴ�." << endl;
	}
	//Person ��ȯ
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
