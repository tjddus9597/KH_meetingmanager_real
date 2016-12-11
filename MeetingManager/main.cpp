#include"stdafx.h"
#include<unordered_map>
#include"MeetingManager.h"

using namespace std;

int main()
{
	unordered_map<int, Room> roomList;
	unordered_map<string, Person> people;

	cout << "-------------------Start Scheduling-------------------\n\n";
	
	
	string command;
	int MaximumMeeting;
	do {
		try {
			cout << "1. Create a new file" << endl;
			cout << "2. Load a file" << endl;
			cout << "3. Quit the program" << endl;
			cout << "Select the menu (1/2/3)? ";
			getline(cin, command);
			cout << "------------------------------------------------------" << endl;
			if (command == "1") {
				string maximumtime;
				vector<string> words_mm;
				cout << "Please Specify maximum meeting time" << endl;
				cout << "Maximum meeting time : ";
				getline(cin, maximumtime);
				MaximumMeeting = stoi(maximumtime);
				break;
			}
			else if (command == "2") {
				string filename;
				vector<string> words_ld;
				cout << "Please enter the name of the saved file" << endl;
				cout << "Name of the saved file : ";
				getline(cin, filename);
				words_ld = { "ld", filename };
				MaximumMeeting = 0;
				ld_loadFile(words_ld, roomList, people, MaximumMeeting);
				break;
			}
			else if (command == "3") {
				return 0;
			}
			else {
				cout << "Invalid command! : Select only 1, 2 or 3" << endl;
			}
		}
		catch (invalid_argument) {
			cerr << "Invalid argument" << endl;
			cout << "------------------------------------------------------" << endl;
		}
		catch (out_of_range) {
			cerr << "Room number is not in range!" << endl;
			cout << "------------------------------------------------------" << endl;
		}
	} while (1);
	// simulation start
	do {
		cout << "------------------------------------------------------" << endl;
	} while (!simulation(roomList, people, MaximumMeeting));
}