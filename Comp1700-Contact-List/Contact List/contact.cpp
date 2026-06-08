#include "contact.hpp"

Contact::Contact(string lastName, string firstName, string phone, string email)
		: lastName(lastName), firstName(firstName), phone(phone), email(email) {}

string Contact::getLastName() const {
	return lastName;
}

string Contact::getFirstName() const {
	return firstName;
}

string Contact::getPhone() const {
	return this->phone;
}

string Contact::getEmail() const {
	return this->email;
}

void Contact::setPhone(string phone) {
	this->phone = phone;
}

void Contact::setEmail(string email) {
	this->email = email;
}

