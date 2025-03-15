#ifndef POST_HPP
#define POST_HPP

#include "Comment.hpp"
#include <string>
#include <vector>
#include <ctime>
using namespace std;


enum class PostType {
    QUESTIONS,
    ANSWERS
};


class Post {
    private:
    string postId;
    string userId;
    string content;
    vector<string> tags;
    vector<Comment*> comments;
    vector<string> votes;
    int score;
    bool accepted;
    PostType type;
    time_t timestamp;

    public:

    Post(string postId, string userId, string content, const vector<string>&tags, PostType type);
    ~Post();
    string getPostId() const;
    string getUserId() const;

    string getContent() const;

    const vector<string>& getTags() const;
    const vector<Comment*>& getComments() const;
    int getScore() const;
    bool isAccepted() const;
    PostType getType() const;
    time_t getTimeStamp() const;

    void addComment(Comment* comment);
    bool addVote(const string& userId);
    bool removeVote(const string& userId);
    void setAccepted(bool status);
    void displayInfo() const;
};


#endif