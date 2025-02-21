#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <list>
#include <algorithm>
#include <utility>
#include <functional>
#include <stdexcept>
#include <queue>
using namespace std;

typedef string ExpenseID;
typedef string userID;
typedef string GroupID;


class User {
    public:
    userID uid;
    string ImageURI;
    string bio;
};




class Group {
    public:
    GroupID gid;
    string ImageURI;
    string bio;

    list<User> lt;
    list<User> users;
    string ImageURI;
    string title;
    string description;
};

class Expense {
    public:
    ExpenseID expenseId;
    bool isSettled = false;
    map<User, Expense> exp;
    string title;
    GroupID gid;
    int timeStamp;
    string imageURI;
};

class Balance {
    public:
    string currency;
    long amount;
};

class Node {
    public:
    userID user_id;
    int final_balance;

    bool operator<(const Node &other) const {
        return final_balance < other.final_balance;
    }
};

class PaymentNode {
    public:
    userID from;
    userID to;
    int amount;
};


struct PayerComparator {
    bool operator()(const Node &a, const Node &b) {
        return a.final_balance < b.final_balance;  // Max-heap for payers
    }
};

list<PaymentNode> makePaymentGraph(list<Node> users){

    priority_queue <Node> receviers;
    // priority_queue<Node> payers;
    priority_queue<Node, vector<Node>, PayerComparator> payers;

    for(const auto &user : users) {
        if(user.final_balance>0){
            receviers.push(user);
        }
        else if (user.final_balance<0){
            Node payer = user;
            payer.final_balance = abs(payer.final_balance);
            payers.push(payer);
        }
    }


    list<PaymentNode> transactions;

    while (!receviers.empty() && !payers.empty())
    {
        /* code */
        Node receiver = receviers.top();
        Node payer = payers.top();
        receviers.pop();
        payers.pop();

        int settledAmount = min(receiver.final_balance, payer.final_balance);

        PaymentNode txn;
        txn.from = payer.user_id;
        txn.to = receiver.user_id;
        txn.amount = settledAmount;
        transactions.push_back(txn);
        receiver.final_balance -= settledAmount;
        payer.final_balance -= settledAmount;
        if(receiver.final_balance>0){
            receviers.push(receiver);
        }
        else if(payer.final_balance>0){
            payers.push(payer);
        }

    }

    return transactions;
    
}



int main() {
    list<Node> users = {
        {"user1", -100},
        {"user2", 200},
        {"user3", -50},
        {"user4", 50}
    };

    list<PaymentNode> transactions = makePaymentGraph(users);

    for (const auto& txn : transactions) {
        cout << "From: " << txn.from << " To: " << txn.to << " Amount: " << txn.amount << "\n";
    }

    return 0;
}