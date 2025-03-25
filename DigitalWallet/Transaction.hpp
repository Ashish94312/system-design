#ifndef TRANSACTION_HPP
#define TRANSACTION_HPP

#include <string>
#include <ctime>
using namespace std;

enum class TransactionType {
    DEPOSIT,
    WITHDRAWAL,
    TRANSFER
};

class Transaction {

    private:
    string transactionId;
    string walletId;
    TransactionType type;
    double amount;
    string timestamp;
    string description;
    bool status;

    public:
    Transaction(string transactionId, string walletId, TransactionType type, double amount,
    string timestamp, string description);

    string getTransactionId() const;
    TransactionType getType() const;
    double getAmount() const;
    string getTimestamp() const;
    string getDescription() const;
    bool setStatus(bool status);
    void displayInfo() const;
    
};

#endif
