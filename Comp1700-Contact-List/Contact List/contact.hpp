#pragma once
#include <string>

using std::string;

class Contact {
private:
	string lastName;
	string firstName;
	string phone;
	string email;

public:
	Contact(string lastName, 
		string firstName, 
		string phone, 
		string email);

	string getLastName() const;
	string getFirstName() const;
	string getPhone() const;
	string getEmail() const;

	void setPhone(string phone);
	void setEmail(string email);
};