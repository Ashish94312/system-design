#include "Transaction.hpp"
#include <iostream>
#include <iomanip>
#include <ctime>

using namespace std;


Transaction::Transaction(string transactionId, string walletId, TransactionType type, double amount
, string timestamp, string description): transactionId(transactionId), walletId(walletId), type(type), amount(amount),
timestamp(timestamp), description(description) ,status(false){}


string Transaction::getTransactionId() const {
    return transactionId;
}

TransactionType Transaction::getType() const {
    return type;
}

double Transaction::getAmount() const {
    return amount;
}

string Transaction::getTimestamp() const {
    return timestamp;   
}

string Transaction::getDescription() const {
    return description;
}

bool Transaction::setStatus(bool status) {
    this->status = status;
    return true;
}

void Transaction::displayInfo() const {
    cout << "Transaction ID: " << transactionId << endl;    
    cout << "Wallet ID: " << walletId << endl;
    cout << "Type: ";
    switch (type) {
        case TransactionType::DEPOSIT:
            cout << "Deposit";
            break;
        case TransactionType::WITHDRAWAL:
            cout << "Withdrawal";
            break;
        case TransactionType::TRANSFER:
            cout << "Transfer";
            break;
        default:
            cout << "Unknown";
            break;
    }
    cout << endl;
    cout << "Amount: $" << fixed << setprecision(2) << amount << endl;
    cout << "Timestamp: " << timestamp << endl;
    cout << "Description: " << description << endl;
    cout << "Status: " << (status ? "Success" : "Failed") << endl;
    cout << "----------------------------------------" << endl;
}

