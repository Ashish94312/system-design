#include "wallet.hpp"
#include <iostream>
#include <iomanip>

using namespace std;

Wallet::Wallet(string walletId, string userId):
    walletId(walletId),
    userId(userId),
    balance(0.0) {}
    
Wallet::~Wallet() {
    for (Transaction* transaction : transactions) {
        delete transaction;
    }
}

string Wallet::getWalletId() const {
    return walletId;
}

string Wallet::getUserId() const {
    return userId;
}

double Wallet::getBalance() const {
    return balance;
}

bool Wallet::addMoney(double amount, string source) {
    if (amount <= 0) {
        return false;
    }
    balance += amount;
    return true;
    
}

bool Wallet::withdrawMoney(double amount, string destination) {
    if (amount <= 0 || amount > balance) {
        return false;
    }

    return true;
    
}

void Wallet::addTransaction(Transaction* transaction) {
    transactions.push_back(transaction);
}

void Wallet::displayTransactions() const {

    cout << "Transactions for Wallet ID: " << walletId << endl;
    cout << "--------------------------------" << endl;

    for (const Transaction* transaction : transactions) {
        transaction->displayInfo();
    }
    cout << "--------------------------------" << endl;

}

void Wallet::displayInfo() const {
    cout << "Wallet ID: " << walletId << endl;
    cout << "User ID: " << userId << endl;
    cout << "Balance: $" << fixed << setprecision(2) << balance << endl;
} 

