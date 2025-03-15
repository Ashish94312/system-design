#include "Post.hpp"
#include "Comment.hpp"
#include <iostream>
#include <algorithm>

using namespace std;


Post::Post(string postId, string userId, string content, const vector<string>& tags, PostType type):
 postId(postId), userId(userId), content(content), tags(tags),score(0), accepted(false), type(type){

    timestamp = time(NULL);

 }

 Post::~Post(){
    for(auto comment : comments){
        delete comment;
    }
 }


 string Post::getPostId() const {
    return postId;
 }

 string Post::getUserId() const {
    return userId;
 }

 string Post::getContent() const {
    return content;
 }

 const vector<string>& Post::getTags() const {
    return tags;
 }

 const vector<Comment*>& Post::getComments() const {
    return comments;
 }

 int Post::getScore() const {
    return score;
 }

 bool Post::isAccepted() const {
    return accepted;
 }
 
 PostType Post::getType() const {
    return type;
 }

 time_t Post::getTimeStamp() const {
    return timestamp;
 }

 void Post::addComment(Comment * comment) {
    comments.push_back(comment);
 }

 bool
  Post::addVote(const string& userId){
   
    if (find(votes.begin(),votes.end(),userId) == votes.end()) {
        votes.push_back(userId);
        score++;
        return true;
    }
    return false;
 }


 bool Post::removeVote(const string& userId) {
    auto it = find(votes.begin(), votes.end(),userId);
    if (it != votes.end()){
        votes.erase(it);
        score--;
        return true;

    }
    return false;
 }

 void Post::setAccepted(bool status) {
    accepted = status;
 }

 void Post::displayInfo() const {
    cout << "Post ID: " << postId << endl;
    cout << "User ID: " << userId << endl;
    cout << "Content: " << content << endl;
    cout << "Tags: ";
    for(auto tag : tags){
        cout << tag << " ";
    }
    cout << endl;
    cout << "Score: " << score << endl;
    cout << "Accepted: " << (accepted ? "Yes" : "No") << endl;
    cout << "Type: " << (type == PostType::QUESTIONS ? "Question" : "Answer") << endl;
    cout << "Timestamp: " << ctime(&timestamp);

    cout << "Comments:" << endl;
    for(auto comment : comments){
        comment->displayInfo();
    }
    cout << endl;
 }