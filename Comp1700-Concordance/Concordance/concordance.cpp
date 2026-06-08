#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cctype>
#include <iomanip>
using namespace std;


string toLower(string s) {
	string result = "";
	for (char c : s) {
		result += tolower(c);
	}
	return result;
}

string formatReference(string book, string chapter, string verse);

bool findMatch(string verseText, string searchPhrase);

int processBible(ifstream& fin, ofstream& fout, string searchPhrase);

string toUpper(string s) {
	string result = "";
	for (char c : s) {
		result += toupper(c);
	}
	return result;
}

int processBible(ifstream& fin, ofstream& fout, string searchPhrase) {
	int verseCount = 0;

	string line;
	string currentBook = "";
	string currentChapter = "";
	string currentVerseNum = "";
	string currentVerseText = "";

	string lowerSearchPhrase = toLower(searchPhrase);

	while (getline(fin, line)) {
		if (line.empty()) {
			if (!currentVerseText.empty()) {
				if (findMatch(currentVerseText, lowerSearchPhrase)) {
					++verseCount;
					fout << "- " << formatReference(currentBook, currentChapter, currentVerseNum) << endl;
				}

				currentVerseText = "";
			}
		}
		else if (line[0] == 'B') {
			currentBook = line.substr(6);
		}
		else if (line[0] == 'C') {
			size_t commaPos = line.rfind(',');

			currentChapter = line.substr(commaPos + 2);
		}
		else if (isdigit(line[0])) {
			size_t colonPos = line.find(':');

			currentVerseNum = line.substr(colonPos + 1, 3);
			currentVerseText = line.substr(colonPos + 5);
		}
		else if (line[0] == ' ') {
			currentVerseText += " " + line.substr(8);
		}
	}

	if (!currentVerseText.empty()) {
		if (findMatch(currentVerseText, lowerSearchPhrase)) {
			++verseCount;
			fout << "- " << formatReference(currentBook, currentChapter, currentVerseNum) << endl;
		}
	}

	return verseCount;
}

string formatReference(string book, string chapter, string verse) {
	stringstream ssChapter(chapter);
	stringstream ssVerse(verse);
	int chapNum, verseNum;

	ssChapter >> chapNum;
	ssVerse >> verseNum;

	return book + " " + to_string(chapNum) + ":" + to_string(verseNum);
}

bool findMatch(string verseText, string lowerSearchPhrase) {
	string lowerVerseText = toLower(verseText);

	size_t pos = lowerVerseText.find(lowerSearchPhrase);

	while (pos != string::npos) {
		bool validStart = false;

		if (pos == 0) {
			validStart = true;
		}
		else {
			if (!isalpha(lowerVerseText[pos - 1])) {
				validStart = true;
			}
		}

		bool validEnd = false;
		size_t endPos = pos + lowerSearchPhrase.length();

		if (endPos == lowerVerseText.length()) {
			validEnd = true;
		}
		else {
			if (!isalpha(lowerVerseText[endPos])) {
				validEnd = true;
			}
		}

		if (validStart && validEnd) 
			return true;

		pos = lowerVerseText.find(lowerSearchPhrase, pos + 1);
	}

	return false;
}

int main() {
	ifstream fin("bible.txt");

	if (!fin.is_open()) {
		cout << "Could not open \"bible.txt\"" << endl;
		return 1;
	}

	string searchPhrase;
	getline(cin, searchPhrase);

	cout << "Searching..." << endl;

	ofstream fout("concordance.txt", ios::app);

	if (!fout.is_open()) {
		cout << "Could not open concordance.txt for writing." << endl;
		fin.close();
		return 1;
	}
	
	fout << quoted(toUpper(searchPhrase)) << endl;

	string line;

	while (fin.good() && getline(fin, line)) {
		if (!line.empty() && line[0] == '-') 
			break;
	}

	int versesFound = processBible(fin, fout, searchPhrase);

	if (versesFound == 0)
		fout << "- Not found" << endl;

	fout << endl;

	cout << "Added " << versesFound << " verses" << endl;
}
