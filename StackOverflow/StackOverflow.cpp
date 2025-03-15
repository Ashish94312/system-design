

#include "StackOverflow.hpp"
#include <iostream>
#include <vector>


StackOverflow::StackOverflow(): userIdCounter(1), postIdCounter(1),commentCounter(1){
    

}


StackOverflow:: ~ StackOverflow(){
    for(auto user : users){
        delete user;
    }
    for(auto post : posts){
        delete post;
    }
}


User* StackOverflow::registerUser(const string& username, const string& email){
    string userId = generateUserId();
    User* newUser = new User(userId, username, email);
    users.push_back(newUser);
    return newUser;
}

void  StackOverflow::removeUser(const string& userId) {
    auto it  =find_if(users.begin(), users.end(),
    [userId](User* user){
        return user->getUserId() == userId;
    });
    if(it!= users.end()){
        delete *it;
        users.erase(it);
    }
}


Post* StackOverflow::addQuestion(const string& userId, const string& content, vector<string>& tags){

    if (!findUser(userId)) return nullptr;

    string postId = generatePostId();
    Post* newQuestion = new Post(postId, userId, content, tags, PostType::QUESTIONS);
    posts.push_back(newQuestion);
    return newQuestion;
}

Post* StackOverflow::addAnswer(const string& userId, const string& questionId, const string& content) {

    if(!findUser(userId)) return nullptr;

    Post* question  = findPost(questionId);
    if(!question || question->getType() != PostType::QUESTIONS) return nullptr;

    string postId = generatePostId();
    Post* newAnswer = new Post(postId, userId, content, {}, PostType::ANSWERS);
    posts.push_back(newAnswer);

    return newAnswer;
}


Comment* StackOverflow::addComment(const string& userId, const string& postId, const string& content) {

    if(!findUser(userId)) return nullptr;
    Post* post = findPost(postId);
    if(!post) return nullptr;

    string commentId = generateCommentId();
    Comment* newComment = new Comment(commentId, userId, content);
    post->addComment(newComment);

    return newComment;
}


bool StackOverflow::votePost(const string& userId, const string& postId) {

    User* user = findUser(userId);
    Post* post = findPost(postId);

    if(!user || ! post || userId == post->getUserId()) return false;

    if (post->addVote(userId)){
        updateUsersReputation(post->getUserId(),10);
        return true;
    }

    return false;
}