#include "contactList.hpp"
#include "stringmanip.hpp"
#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <iostream>

using namespace std;

const string FILENAME = "contacts.csv";

void setUpFile(ContactList& contacts);
void manageContacts(ContactList& contacts);

void printGeneralHelp();
void printSpecificHelp(const string& command);


int main() {
	ContactList contacts;

	setUpFile(contacts);
	manageContacts(contacts);
}


void setUpFile(ContactList& contacts) {
	ifstream fin(FILENAME);

	if (!fin) {
		cout << "Could not open contacts.csv\n";
		cout << "Starting new contacts list\n\n";
		return;
	}

	string header;
	getline(fin, header);

	if (header != "Last Name,First Name,Phone,Email") {
		cout << "File contacts.csv has invalid format\n\n";
		exit(0);
	}

	string line;
	int count = 0;

	while (getline(fin, line)) {
		if (trim(line).empty()) continue;

		istringstream iss(line);
		string last, first, phone, email;

		getline(iss, last, ',');
		getline(iss, first, ',');
		getline(iss, phone, ',');
		getline(iss, email, ',');

		contacts.addContact(last, first, phone, email);
		++count;
	}

	cout << "Read " << count << " contacts from contacts.csv\n\n";
}

void manageContacts(ContactList& contacts) {
	string line;

	while (getline(cin, line)) {
		vector<string> words;
		istringstream iss(line);
		string word;

		while (iss >> quoted(word)) {
			words.push_back(word);
		}

		if (words.empty()) continue;

		string command = uppercase(words[0]);

		if (command == "ADD" && words.size() == 1) {
			contacts.addContact();
		}
		else if (command == "UPDATE" && words.size() == 1) {
			contacts.updateContact();
		}
		else if (command == "SHOW" && words.size() == 3) {
			contacts.show(words[1], words[2]);
		}
		else if (command == "LIST" && words.size() == 1) {
			contacts.list();
		}
		else if (command == "SORT" && words.size() == 2) {
			contacts.sortByField(words[1]);
		}
		else if (command == "FIND" && words.size() == 2) {
			contacts.findBySubstring(words[1]);
		}
		else if (command == "DELETE" && words.size() == 3) {
			contacts.deleteContact(words[1], words[2]);
		}
		else if (command == "SAVE" && words.size() == 1) {
			contacts.save(FILENAME);
		}
		else if (command == "QUIT" && words.size() == 1) {
			break;
		}
		else if (command == "HELP") {
			if (words.size() == 1) {
				printGeneralHelp();
			}
			else if (words.size() == 2) {
				printSpecificHelp(uppercase(words[1]));
			}
			else {
				cout << "Invalid HELP usage. Try HELP or HELP [COMMAND]\n\n";
			}
		}
		else {
			cout << "Command not recognized\n\n";
		}
	}
}

void printGeneralHelp() {
	cout << "### Available Commands ###\n";
	cout << "--------------------------\n";
	cout << left << setw(10) << "ADD" << " - Interactively add a new contact.\n";
	cout << left << setw(10) << "UPDATE" << " - Interactively modify a contact's phone/email.\n";
	cout << left << setw(10) << "SHOW" << " - SHOW [First] [Last]: Display a specific contact's full details.\n";
	cout << left << setw(10) << "LIST" << " - Display a list of all contacts (First Name Last Name).\n";
	cout << left << setw(10) << "SORT" << " - SORT [Field]: Sort contacts by a specified field.\n";
	cout << left << setw(10) << "FIND" << " - FIND [Text]: Search all fields for a text substring.\n";
	cout << left << setw(10) << "DELETE" << " - DELETE [Last] [First]: Remove a specific contact.\n";
	cout << left << setw(10) << "SAVE" << " - Save all current contacts to contacts.csv.\n";
	cout << left << setw(10) << "QUIT" << " - Exit the program.\n";
	cout << left << setw(10) << "HELP" << " - Display this general help menu.\n";
	cout << left << setw(10) << "HELP [CMD]" << " - Display detailed help for a specific command.\n";
	cout << "--------------------------\n\n";
}

void printSpecificHelp(const string& command) {
	cout << "### Detailed Help for " << command << " ###\n";

	if (command == "ADD") {
		cout << "Syntax: ADD\n";
		cout << "Purpose: Starts an interactive session to prompt the user for the new contact's Last Name, First Name, Phone, and Email.\n";
		cout << "Constraint: Last Name and First Name cannot be empty. Fails if a contact with the exact same Last and First Name already exists (case-insensitive).\n";
		cout << "Example: ADD\n\n";
	}
	else if (command == "UPDATE") {
		cout << "Syntax: UPDATE\n";
		cout << "Purpose: Starts an interactive session. Prompts for the existing contact's Last Name and First Name, then prompts for the new Phone and Email.\n";
		cout << "Note: Only Phone and Email fields are modified. Fails if the contact does not exist.\n";
		cout << "Example: UPDATE\n\n";
	}
	else if (command == "SHOW") {
		cout << "Syntax: SHOW [First Name] [Last Name]\n";
		cout << "Purpose: Locates a contact using the exact Last and First names (case-insensitive) and displays all four fields.\n";
		cout << "Note: Names that contain spaces (e.g., 'Da Vinci') must be enclosed in double quotes.\n";
		cout << "Example (Simple Name): SHOW Smith John\n";
		cout << "Example (Compound Name): SHOW \"Bong Bong\" Marcos\n\n";
	}
	else if (command == "LIST") {
		cout << "Syntax: LIST\n";
		cout << "Purpose: Displays the First Name and Last Name of every contact currently in the list, using the current sort order.\n";
		cout << "Example: LIST\n\n";
	}
	else if (command == "SORT") {
		cout << "Syntax: SORT [Field]\n";
		cout << "Purpose: Sorts the entire contact list.\n";
		cout << "Valid Fields (case-insensitive): Last, First, Phone, Email.\n";
		cout << "Example: SORT last\n";
	}
	else if (command == "FIND") {
		cout << "Syntax: FIND [Substring]\n";
		cout << "Purpose: Searches all fields (First Name, Last Name, Phone, Email) of all contacts for the specified text substring.\n";
		cout << "Output: Prints the First Name and Last Name of all matching contacts.\n";
		cout << "Example: FIND 123\n\n";
	}
	else if (command == "DELETE") {
		cout << "Syntax: DELETE [Last Name] [First Name]\n";
		cout << "Purpose: Permanently removes the contact matching the exact Last and First names (case-insensitive).\n";
		cout << "Note: Names that contain spaces (e.g., 'Da Vinci') must be enclosed in double quotes.\n";
		cout << "Example (Simple Name): DELETE Smith John\n";
		cout << "Example (Compound Name): DELETE \"Bong Bong\" Marcos\n\n";
	}
	else if (command == "SAVE") {
		cout << "Syntax: SAVE\n";
		cout << "Purpose: Writes the current list of contacts to the contacts.csv file, overwriting its contents.\n";
		cout << "Example: SAVE\n\n";
	}
	else if (command == "QUIT") {
		cout << "Syntax: QUIT\n";
		cout << "Purpose: Exits the program immediately. Warning: Any unsaved changes will be lost.\n";
		cout << "Example: QUIT\n\n";
	}
	else {
		cout << "Help information not available for command: " << command << ". Try HELP to see the list of commands.\n\n";
	}
}