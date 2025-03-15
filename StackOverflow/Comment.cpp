
#include "Comment.hpp"
#include <iostream>


Comment::Comment(string commentId, string userId, string content):
 commentId(commentId), userId(userId), content(content) {
    timestamp = time(NULL);
 }


 string Comment::getCommentId() const {
    return commentId;
 }

 string Comment::getUserId() const {
    return userId;
 }

 string Comment::getContent() const {
    return content;
 }

 time_t Comment::getTimestamp() const {
    return timestamp;
 }


 void Comment::displayInfo() const {
    cout << "Comment ID: " << commentId << endl;
    cout << "User ID: " << userId << endl;
    cout << "Content: " << content << endl;
    cout << "Timestamp: " << ctime(&timestamp) << endl;
 }
