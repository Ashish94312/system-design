#ifndef COMMENT_HPP
#define COMMENT_HPP


#include <string>
#include <ctime>
using namespace std;

class Comment {
    private:
    string commentId;
    string UserId;
    string content;
    time_t timestamp;

    public:
    Comment(string commentId, string UserId, string content);

    string getCommentId() const;
    string getUserId() const;
    string getContent() const;
    time_t getTimestamp() const;
    void displayInfo() const;

};


#endif