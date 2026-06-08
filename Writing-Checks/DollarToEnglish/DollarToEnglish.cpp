#include <iostream>
#include <string>
using namespace std;

string getPlaceValue(int n) {
	const string ones[] = { "", "One", "Two", "Three", "Four", "Five", "Six", "Seven", "Eight", "Nine" };
	const string teens[] = { "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen", "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen" };
	const string tens[] = { "", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};

	string result = "";

	if (n > 100) {
		int h = n / 100;

		result += ones[h] + " Hundred";
		n %= 100;
		if (n) result += " ";
	}

	if (n >= 20) {
		int t = n / 10;
		int o = n % 10;

		if (t >= 2 && t <= 9) {
			result += tens[t];
			if (o != 0) result += " " + ones[o];
		}
	}
	else if (n >= 10 && n <= 19) {
		result += teens[n - 10];
	}
	else if (n >= 1 && n <= 9) {
		result += ones[n];
	}
	return result;
}

string getEnglish(int money) {
	if (money == 0) return "No Dollars";
	if (money == 1) return "One Dollar";

	const string otherPlace[] = { " ", " Thousand ", " Million " };
	string english = "";

	for (int i = 0; i < 3; i++) {
		int triple = money % 1000;

		if (triple != 0)
			english = getPlaceValue(triple) + otherPlace[i] + english;

		money /= 1000;
	}
	return english + "Dollars";
}

string getCents(double amount) {
	long long cents = (long long)(amount * 100.0 + 0.5) % 100;

	if (cents == 0) return "No Cents";

	return to_string(cents) + (cents == 1 ? " Cent" : " Cents");
}

int main() {
	double amount;

	while (1) {
		cout << "Amount? ";
		cin >> amount;
		if (amount == 0) break;

		cout << endl << getEnglish((int)amount) << " and " << getCents(amount) << endl << endl;
	}
}