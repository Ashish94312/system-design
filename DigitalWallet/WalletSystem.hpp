#ifndef WALLET_SYSTEM_HPP
#define WALLET_SYSTEM_HPP

#include <vector>
#include <string>
#include "User.hpp"
#include "wallet.hpp"
#include "Transaction.hpp"

using namespace std;

class WalletSystem {
    private: 
    vector<User*> users;
    vector<Wallet*> wallets;
    int transactionIdCounter;

    public:
    WalletSystem();
    ~WalletSystem();

    void addUser(User* user);
    Wallet* createWallet(string userId);
    bool addMoney(string walletId, double amount, string source);
    bool transferMoney(string fromWalletId, string toWalletId, double amount);
    bool withdrawMoney(string walletId, double amount, string destination);
    void displayUserInfo(string userId) const;
    void displayWalletInfo(string walletId) const;
    void displayAllUsers() const;
    void displayAllWallets() const;

    private:
    User* findUser(string userId) const;
    Wallet* findWallet(string walletId) const;
    string generateTransactionId();
    string getCurrentTimeStamp() const;

};

#endif