#ifndef USER_HPP
#define USER_HPP


#include <string>
using namespace std;

class User {
    private:
    string userId;
    string name;
    string email;
    string password;
    string phoneNumber;
    string address;
    
    public:
    User(string userId, string name, string email, string password, string phoneNumber, string address);
    string getUserId() const;
    string getName() const;
    string getEmail() const;
    string getPassword() const;
    string getPhoneNumber() const;
    string getAddress() const;
    void displayUserInfo() const;
    
};



#endif