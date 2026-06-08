#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <map>
#include <fstream>
using namespace std;


const string fileName = "gradebook.csv";


void readInput(map<string, vector<int>>& gradebook, vector<string>& assignments, vector<double>& averages);
void writeOutput(map<string, vector<int>>& gradebook, vector<string>& assignments, vector<double>& averages);


int main() {
	map<string, vector<int>> gradebook;
	vector<string> assignments;
	vector<double> averages;

	readInput(gradebook, assignments, averages);
	writeOutput(gradebook, assignments, averages);
}


void readInput(map<string, vector<int>>& gradebook, vector<string>& assignments, vector<double>& averages) {
	int studentCount, assignmentCount;
	cin >> studentCount >> assignmentCount;

	for (int i = 0; i < assignmentCount; ++i) {
		string assignmentName;

		while (getline(cin, assignmentName) && assignmentName.empty()) {
			continue;
		}

		assignments.push_back(assignmentName);

		double totalGrades = 0.0;

		for (int j = 0; j < studentCount; ++j) {
			string studentName;
			string gradeText;
			int gradeNum;

			getline(cin, studentName, ':');
			getline(cin, gradeText);

			gradeNum = stoi(gradeText);

			gradebook[studentName].push_back(gradeNum);
			totalGrades += gradeNum;
		}

		double averageGrade = totalGrades / studentCount;
		averages.push_back(averageGrade);
	}
}

void writeOutput(map<string, vector<int>>& gradebook, vector<string>& assignments, vector<double>& averages) {
	ofstream fout(fileName);

	fout << fixed << setprecision(2);


	fout << "Name,";
	for (const string& assignment : assignments) {
		fout << assignment << ',';
	}
	fout << "Final Grade\n";

	double totalFinalGrades = 0.0;


	for (const auto& pair : gradebook) {
		const string& studentName = pair.first;
		const vector<int>& grades = pair.second;

		fout << pair.first;

		double studentSum = 0.0;

		for (int grade : grades) {
			fout << "," << grade;
			studentSum += grade;
		}

		double finalGrade = studentSum / grades.size();
		totalFinalGrades += finalGrade;

		fout << ',' << finalGrade << '\n';
	}

	double overallAverage = totalFinalGrades / gradebook.size();

	fout << "Averages,";

	for (double avg : averages) {
		fout << avg << ',';
	}
	fout << overallAverage << '\n';
}