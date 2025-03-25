#include "User.hpp"
#include <iostream>

User::User(string userId, string name, string email, string password, string phoneNumber, string address):
    userId(userId),
    name(name),
    email(email),
    password(password),
    phoneNumber(phoneNumber),
    address(address) {}


string User::getUserId() const {
    return userId;
}

string User::getName() const {
    return name;
}

string User::getEmail() const {
    return email;
}


string User::getPhoneNumber() const {
    return phoneNumber;
}

string User::getAddress() const {
    return address;
}

void User::displayUserInfo() const {
    cout << "User ID: " << userId << endl;
    cout << "Name: " << name << endl;
    cout << "Email: " << email << endl;
    cout << "Phone Number: " << phoneNumber << endl;
    cout << "Address: " << address << endl;
}