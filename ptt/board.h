#pragma once
#include "user.h"
#include <vector>
enum vote
{
	UPVOTE,
	DOWNVOTE
};

struct Comment
{
	bool vote;
	string message;
};

struct Post
{
public:
	void setTitle();
	void setContents();
	void setComment();
	string title;
	string contents;
	vector<Comment> comments;
};

void Post::setTitle() {
	cout << "Title: ";
	getline(cin, title);
}

void Post::setContents() {
	string buffer;
	cout << "Editing:\n *type \"SAVE\" when you finish editing.\n";
	while (getline(cin, buffer) && buffer != "SAVE") {
		if (buffer == "SAVE")
			cout << "contents saved.\n";
		else
			contents += buffer + "\n";
	}
}

void Post::setComment() {
	Comment newComment;
	cout << "leave a comment: ";
	getline(cin, newComment.message);
	// TODO: voting mechanism
	comments.push_back(newComment);
}

class Board
{
public:
	Board();
	void editBoard();
private:
	vector<Post> posts;
};

Board::Board() {
}

void Board::editBoard() {
	char cmd;
	while (true) {
		cout << "Select a mode:\n 'n'ew post\n"
			" 'e'dit an existing post\n 'd'elete a post\n 'q'uit\n";
		cin >> cmd;
		cin.ignore();
		if (cmd == 'n') {
			Post newPost;
			newPost.setTitle();
			newPost.setContents();
			newPost.setComment();
			posts.push_back(newPost);
		}
		else if (cmd == 'e') {
			cout << "Under construction!\n";
		}
		else if (cmd == 'd') {
			cout << "Under construction!\n";
		}
		else if (cmd == 'q')
			return;
	}
}