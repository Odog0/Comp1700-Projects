#pragma once
#include "contact.hpp"
#include <vector>

using std::string;
using std::vector;

class ContactList {
private:
	vector<Contact> contacts;

	auto findContact(const string& first, const string& last);
	auto findContact(const string& first, const string& last) const;

public:
	void addContact();
	void addContact(
		const string& lastName,
		const string& firstName,
		const string& phone,
		const string& email);

	void updateContact();
	void show(string firstName, string lastName) const;
	void list() const;
	void sortByField(string field);
	void findBySubstring(string substring) const;
	void deleteContact(string firstName, string lastName);
	void save(string file);
};