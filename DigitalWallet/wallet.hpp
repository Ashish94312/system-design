#ifndef WALLET_HPP
#define WALLET_HPP

#include <string>
#include <vector>
#include "Transaction.hpp"

class Wallet {
    private:
    string walletId;
    string userId;
    double balance;

    vector<Transaction*> transactions;

    public:
    Wallet(string walletId, string userId);
    ~Wallet();

    string getWalletId() const;
    string getUserId() const;
    double getBalance() const;

    bool addMoney(double amount ,string source);
    bool withdrawMoney(double amount, string destination);
    void addTransaction(Transaction* transaction);
    void displayTransactions() const;
    void displayInfo() const;


};


#endif