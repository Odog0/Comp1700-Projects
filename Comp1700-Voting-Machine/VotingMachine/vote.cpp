#include <iostream>
#include <vector>
#include <string>
#include <cctype>
#include <iomanip>
#include <cstdlib>
using namespace std;


// reference to javascript but lazier
string stringtolower(string str) {
	for (int i = 0; i < str.length(); i++) {
		str[i] = tolower(str[i]);
	}

	return str;
}

void getOptions(vector<string>& options, vector<int>& votes) {
	cout << "\nEnter the options: (type \"quit\" to quit)\n";
	string option;

	while (cin >> option && option != "quit") {
		options.push_back(option);
		votes.push_back(0);
	}

	system("cls");
}

void conductVoting(string question, vector<string>& options, vector<int>& votes) {
	while (1) {
		cout << endl << question << endl;

		for (const string& o : options) {
			cout << "- " << o << endl;
		}
		cout << endl;

		string vote;
		bool validVote = false;

		while (!validVote) {
			cout << "Vote: ";
			cin >> vote;

			if (vote == "quit") {
				system("cls");
				return;
			}
			
			string lowerCase = stringtolower(vote);

			for (int i = 0; i < options.size(); ++i) {
				if (stringtolower(options[i]) == lowerCase) {
					votes[i]++;
					validVote = true;
					break;
				}
			}

			if (!validVote)
				cout << "Invalid choice!  Please try again.\n";
		}
	}
}

void displayResults(string question, const vector<string>& options, const vector<int>& votes) {
	cout << question << "\n\n";

	int maxVotes = 0;

	for (int i = 0; i < options.size(); ++i) {
		cout << left << setw(29) << setfill('.') << options[i];
		cout << votes[i] << endl;

		if (votes[i] > maxVotes)
			maxVotes = votes[i];
	}

	vector<string> winners;
	if (maxVotes > 0) {
		for (int i = 0; i < options.size(); ++i) {
			if (votes[i] == maxVotes) {
				winners.push_back(options[i]);
			}
		}
	}

	if (winners.empty()) {
		cout << "\nNo votes\n";
	}
	else if (winners.size() == 1) {
		cout << "\nThe winner is:\n" << winners[0] << endl;
	}
	else {
		cout << "\nThe winners are:\n";
		for (const string& winner : winners) {
			cout << winner << endl;
		}
	}
}

int main() {
	vector<string> options;
	vector<int> votes;
	string question;

	cout << "Enter the question:\n";
	getline(cin, question);

	// phase one
	getOptions(options, votes);

	// phase two
	conductVoting(question, options, votes);
	
	// phase three
	displayResults(question, options, votes);
}