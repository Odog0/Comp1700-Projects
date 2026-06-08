#include "contactList.hpp"
#include "stringmanip.hpp"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

auto ContactList::findContact(const string& first, const string& last) {
	return find_if(contacts.begin(), contacts.end(),
		[&](const Contact& c) {
			return lowercase(c.getFirstName()) == lowercase(first) && lowercase(c.getLastName()) == lowercase(last);
		});
}

auto ContactList::findContact(const string& first, const string& last) const {
	return find_if(contacts.begin(), contacts.end(),
		[&](const Contact& c) {
			return lowercase(c.getFirstName()) == lowercase(first) && lowercase(c.getLastName()) == lowercase(last);
		});
}

void ContactList::addContact() {
	string lastName;
	string firstName;
	string phone;
	string email;

	cout << "Last Name:\n";
	getline(cin, lastName);
	lastName = trim(lastName);

	if (lastName.empty()) {
		cout << "\nInvalid contact data\n\n";
		return;
	}

	cout << "First Name:\n";
	getline(cin, firstName);
	firstName = trim(firstName);

	if (firstName.empty()) {
		cout << "\nInvalid contact data\n\n";
		return;
	}

	auto p = findContact(firstName, lastName);

	cout << "Phone:\n";
	getline(cin, phone);
	phone = trim(phone);

	cout << "Email:\n";
	getline(cin, email);
	email = trim(email);

	if (p != contacts.end()) {
		cout << "\nAdd contact failed : contact already exists\n\n";
		return;
	}

	contacts.push_back(Contact(lastName, firstName, phone, email));

	cout << "\nContact added\n\n";
}

void ContactList::addContact(
	const string& lastName,
	const string & firstName,
	const string& phone,
	const string& email) 
{
	contacts.push_back(Contact(lastName, firstName, phone, email));
}

void ContactList::updateContact() {
	string lastName;
	string firstName;
	string phone;
	string email;

	cout << "Last Name:\n";
	getline(cin, lastName);
	lastName = trim(lastName);

	if (lastName.empty()) {
		cout << "\nInvalid contact data\n\n";
		return;
	}

	cout << "First Name:\n";
	getline(cin, firstName);
	firstName = trim(firstName);

	if (firstName.empty()) {
		cout << "\nInvalid contact data\n\n";
		return;
	}

	auto p = findContact(firstName, lastName);

	cout << "Phone:\n";
	getline(cin, phone);
	phone = trim(phone);

	cout << "Email:\n";
	getline(cin, email);
	email = trim(email);

	if (p == contacts.end()) {
		cout << "\nUpdate contact failed: contact does not exist\n\n";
		return;
	}

	p->setPhone(phone);
	p->setEmail(email);

	cout << "\nContact updated\n\n";
}

void ContactList::show(string firstName, string lastName) const {
	auto p = findContact(firstName, lastName);

	if (p == contacts.end()) {
		cout << firstName << ' ' << lastName << " not found\n\n";
		return;
	}

	cout << left << setw(12) << "Last Name:" << p->getLastName() << '\n'
		<< left << setw(12) << "First Name:" << p->getFirstName() << '\n'
		<< left << setw(12) << "Phone:" << p->getPhone() << '\n'
		<< left << setw(12) << "Email:" << p->getEmail() << "\n\n";
}

void ContactList::list() const {
	if (contacts.empty())
		cout << "No contacts found\n";

	for (const Contact& contact : contacts) {
		cout << contact.getFirstName() << ' ' << contact.getLastName() << '\n';
	}
	cout << '\n';
}

void ContactList::sortByField(string field) {
	field = lowercase(field);

	stable_sort(contacts.begin(), contacts.end(),
		[&](const Contact& a, const Contact& b) {
			if (field == "first")
				return lowercase(a.getFirstName()) < lowercase(b.getFirstName());

			if (field == "last")
				return lowercase(a.getLastName()) < lowercase(b.getLastName());

			if (field == "phone")
				return lowercase(a.getPhone()) < lowercase(b.getPhone());

			if (field == "email")
				return lowercase(a.getEmail()) < lowercase(b.getEmail());

			return false;
		});

	cout << "Contacts sorted\n\n";
}

void ContactList::findBySubstring(string substring) const {
	bool printed = false;
	for (const Contact& c : contacts) {
		string metaData = c.getFirstName() + c.getLastName() + c.getPhone() + c.getEmail();

		if (metaData.find(substring) != string::npos) {
			cout << c.getFirstName() << ' ' << c.getLastName() << '\n';
			printed = true;
		}
	}

	if (!printed)
		cout << "No contacts found\n";
	
	cout << '\n';
}

void ContactList::deleteContact(string firstName, string lastName) {
	auto p = findContact(firstName, lastName);

	if (p == contacts.end()) {
		cout << "Delete contact failed: contact does not exist\n\n";
		return;
	}

	contacts.erase(p);
	cout << "Contact deleted.\n\n";
}

void ContactList::save(string file) {
	ofstream fout(file);

	fout << "Last Name,First Name,Phone,Email\n";

	for (const Contact& c : contacts) {
		fout << c.getLastName() << ','
			<< c.getFirstName() << ','
			<< c.getPhone() << ','
			<< c.getEmail() << '\n';
	}

	cout << "Saved contacts.csv\n\n";
}