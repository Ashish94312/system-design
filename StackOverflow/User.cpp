#include "User.hpp"
#include  <iostream>


User::User(string userId, string username, string email) :
userId(userId), username(username), email(email),reputation(1), active(true) {}


string User::getUserId() const {
    return userId;
}

string User::getUsername() const {
    return username;
}

string User::getEmail() const {
    return email;
}

int User::getReputation() const {
    return reputation;
}

vector<string> User::getBadges() const {
    return badges;
}

bool User::isActive( ) const {
    return active;
}

void User::updateReputation(int points) {
    reputation += points;
}

void User::addBadge(const string& badge) {
    badges.push_back(badge);
}

void User::setActive(bool status) {
    active = status;
}

void User::displayInfo() const {
    cout << "User ID: " << userId << endl;
    cout << "Username: " << username << endl;
    cout << "Email: " << email << endl;
    cout << "Reputation: " << reputation << endl;
    cout << "Badges: ";
    for(auto badge : badges){
        cout << badge << " ";
    }
    cout << endl;
    cout << "Active: " << (active ? "Yes" : "No") << endl;
}