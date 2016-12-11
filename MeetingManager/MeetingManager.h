#pragma once
#include"stdafx.h"
#include"Meeting.h"
#include"Person.h"
#include"Room.h"
#include<iostream>
#include<string>
#include<unordered_map>
#include<vector>
#include<iterator>
#include<sstream>
#include<stdexcept>
#include<fstream>

bool simulation(unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
inline bool isCmNum(vector<string>& words, int validNum);																		//��ɾ� ���� Ȯ�� �Լ�
bool qq_Quit(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool ar_insrtRoom(vector<string>& words, unordered_map<int, Room>& roomList);												 	    //ar ��ɾ� ó�� �Լ�
bool am_insrtMeeting(vector<string>& words, unordered_map<int, Room>& roomList);													//am ��ɾ� ó�� �Լ�
bool am_insrtMeeting(int roomId_, string day_, int startTime_, int endTime_, string topic_, unordered_map<int, Room>& roomList);
bool ai_insrtPerson(vector<string>& words, unordered_map<string, Person>& people);													//ai ��ɾ� ó�� �Լ�
bool ap_insrtParticipation(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);		//ap ��ɾ� ó�� �Լ�
bool ag_addGroup(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool ag_subParOverlap(unordered_map<int, Room>& roomList, int roomId, string day, int startTime, int endTime, string name);
bool pi_printPerson(vector<string>& words, unordered_map<string, Person>& people);
bool pr_printRoom(vector<string>& words, unordered_map<int, Room>& roomList);
bool pm_printMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool ps_printEveryMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool pg_printEveryPerson(vector<string>& words, unordered_map<string, Person>& people);
bool pa_printAll(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool rm_replaceMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool di_delPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);				//di ��ɾ� ó�� �Լ�
bool dr_delRoom(vector<string>& words, unordered_map<int, Room>& roomList);															//dr ��ɾ� ó�� �Լ�
bool dm_delMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool dm_delMeeting(int roomId_, string day_, int startTime_, unordered_map<int, Room>& roomList);
bool dp_delParticipation(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool ds_delAllMeeting(vector<string>& words, unordered_map<int, Room>& roomList);
bool dg_delAllPerson(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool da_deleteAll(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool sd_saveFile(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);
bool ld_loadFile(vector<string>& words, unordered_map<int, Room>& roomList, unordered_map<string, Person>& people);