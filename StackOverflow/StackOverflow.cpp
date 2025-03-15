

#include "StackOverflow.hpp"
#include <iostream>
#include <vector>


StackOverflow::StackOverflow(): userIdCounter(1), postIdCounter(1),commentIdCounter(1){
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

bool StackOverflow::unvotePost(const string& userId, const string& postId) {

    Post *post = findPost(postId);

    if(!post) return false;

    if(post->removeVote(userId)){
        updateUsersReputation(post->getUserId(),-10);
        return true;
    }

    return false;
}

bool StackOverflow::acceptAnswer(const string&userId, const string& answerId) {
    Post* answer = findPost(answerId);

    if(!answer || answer->getType()!= PostType::ANSWERS) return false;

    answer->setAccepted(true);
    updateUsersReputation(answer->getUserId(),15);
    return true;

}



vector<Post*> StackOverflow::searchQuestions(const string& tag) const {
    vector<Post*> results;

    for(const auto& post : posts){
        if(post->getType() == PostType::QUESTIONS) {
            const auto& tags = post->getTags();
            if( find(tags.begin(),tags.end(),tag)!=tags.end()) {
                results.push_back(post);
            }
        }
    }

    return results;
}

void StackOverflow::displayUserProfile(const string& userId) const {
    // Post* question = findPost(questionId);
    User *user = findUser(userId);

    if (!user) return;

    user->displayInfo();

    cout<<"\n Post by "<<user->getUsername()<<":" << endl;
    for(const auto& post : posts){
        if(post->getUserId() == userId){
            post->displayInfo();
        }
    }

}


void StackOverflow::displayQuestion(const string& questionId) const {
    Post* question = findPost(questionId);

    if(!question || question->getType()!= PostType::QUESTIONS) return;
    question->displayInfo();

    cout<<"\n Answer:" << std::endl;

    for(const auto& post : posts) {
        if( post->getType() == PostType::ANSWERS) {
            post->displayInfo();
            cout<< " -------------------------------- " << std::endl;
        }
    }
}


User* StackOverflow::findUser(const string& userId) const {
    auto it = find_if(users.begin(), users.end(), [userId](User* user) {
        return user->getUserId() == userId;
    });
    return it != users.end() ? *it : nullptr;
}

Post* StackOverflow::findPost(const string& postId) const {
    auto it = find_if(posts.begin(), posts.end(), [postId](Post* post) {
        return post->getPostId() == postId;
    });
    return it!= posts.end()? *it : nullptr;
}

void StackOverflow::updateUsersReputation(const string& userId, int points) {
    User* user = findUser(userId);
    if(user) user->updateReputation(points);
}


string StackOverflow::generateUserId() {
    return "U" +to_string(userIdCounter++);
}


string StackOverflow::generatePostId() {
    return "P" + to_string(postIdCounter++);
}


string StackOverflow::generateCommentId() {
    return "C" + to_string(commentIdCounter++);
}