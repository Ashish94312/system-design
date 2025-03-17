#ifndef STACK_OVERFLOW_HPP
#define STACK_OVERFLOW_HPP

#include "User.hpp"
#include "Post.hpp"
#include <iostream>
#include <vector>
#include <string>
using namespace std;


class StackOverflow {

    private:

    vector<User*> users;
    vector<Post*> posts;

    int userIdCounter;
    int postIdCounter;
    int commentIdCounter;
    

    public: 

    StackOverflow();
    ~StackOverflow();

    User* registerUser(const string& username, const string& email);
    void removeUser( const string& userId);

    Post* addQuestion( const string& userId, const string& content, vector<string>& tags);
    Post * addAnswer(const string& userId, const string& questionId, const string& content);
    Comment* addComment(const string& userId, const string& postId, const string& content);


    bool votePost(const string& userId, const string& postId);
    bool unvotePost(const string& userId, const string& postId);
    bool acceptAnswer(const string& userId, const string& answerId);

    vector<Post*> searchQuestions(const string& tag) const;
    void displayUserProfile(const string& userId) const;
    void displayQuestion(const string& QuestionId) const;
    void displayAllQuestions() const;


    private:
    User* findUser(const string& userId) const;
    Post* findPost(const string& postId) const;
    void updateUsersReputation(const string& userId, int points);
    string generateUserId();
    string generatePostId();
    string generateCommentId();








};


#endif