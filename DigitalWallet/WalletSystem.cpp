#include "WalletSystem.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

WalletSystem::WalletSystem() : transactionIdCounter(0) {}

WalletSystem::~WalletSystem() {
    for (auto user : users) {
        delete user;
    }
    for (auto wallet : wallets) {
        delete wallet;
    }
}


void WalletSystem::addUser(User* user) {
    users.push_back(user);
}

Wallet* WalletSystem::createWallet(string userId) {

    if (!findUser(userId)) {
        return nullptr;
    }
    string walletId = "W" + userId;
    Wallet* wallet = new Wallet(walletId, userId);
    wallets.push_back(wallet);
    return wallet;
}


bool WalletSystem::addMoney(string walletId, double amount, string source) {
    Wallet* wallet = findWallet(walletId);
    if (!wallet){
        return false;
    }

    if(wallet->addMoney(amount, source)){
        Transaction* transaction = new Transaction(generateTransactionId(), walletId, TransactionType::DEPOSIT, amount, getCurrentTimeStamp(), source);
        transaction->setStatus(true);
        wallet->addTransaction(transaction);
        return true;
    }
    return false;
}



bool WalletSystem::transferMoney(string fromWalletId, string toWalletId, double amount) {
    Wallet* fromWallet = findWallet(fromWalletId);
    Wallet* toWallet = findWallet(toWalletId);

    if (!fromWallet || !toWallet) {
        return false;
    }

    if(fromWallet->withdrawMoney(amount, "transfer")){
        if(toWallet->addMoney(amount, "transfer")){
            Transaction* transaction = new Transaction(generateTransactionId(), fromWalletId, TransactionType::TRANSFER, amount, getCurrentTimeStamp(), "transfer");
            transaction->setStatus(true);
            fromWallet->addTransaction(transaction);

            Transaction* transaction2 = new Transaction(generateTransactionId(), toWalletId, TransactionType::TRANSFER, amount, getCurrentTimeStamp(), "transfer");
            transaction2->setStatus(true);
            toWallet->addTransaction(transaction2);
            return true;       
        }
    }
    return false;
}


bool WalletSystem::withdrawMoney(string walletId, double amount, string destination) {
    Wallet* wallet = findWallet(walletId);
    if(!wallet){
        return false;
    }

    if (wallet->withdrawMoney(amount, destination)){
        Transaction* transaction = new Transaction(generateTransactionId(), walletId, TransactionType::WITHDRAWAL, amount, getCurrentTimeStamp(), destination);
        transaction->setStatus(true);
        wallet->addTransaction(transaction);
        return true;
    }
    return false;
}



void WalletSystem::displayUserInfo(string userId) const {
    User* user = findUser(userId);
    if(!user){
        cout << "User not found" << endl;
        return;
    }
    
    if(user){
        user->displayUserInfo();
        for (const auto& wallet : wallets){
            if(wallet->getUserId() == userId){
                wallet->displayInfo();
                wallet->displayTransactions();
            }
        }
    }
}


void WalletSystem::displayAllUsers() const {
    for (const auto& user : users){
        user->displayUserInfo();
    }
    cout<< "--------------------------------" << endl;
}

void WalletSystem::displayAllWallets() const {
    for (const auto& wallet : wallets){
        wallet->displayInfo();
        wallet->displayTransactions();
    }
    cout<< "--------------------------------" << endl;
}




string WalletSystem::getCurrentTimeStamp() const {
    time_t now = time(0);
    tm* localTime = localtime(&now);
    stringstream ss;
    ss << put_time(localTime, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

string WalletSystem::generateTransactionId() {
    return "T" + std::to_string(transactionIdCounter++);
}

Wallet* WalletSystem::findWallet(string walletId) const {
    for (const auto& wallet : wallets){
        if(wallet->getWalletId() == walletId){
            return wallet;
        }
    }
    return nullptr;
}