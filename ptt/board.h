#pragma once
#include "user.h"
#include <vector>
#include <string>
using namespace std;
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
	void selectPost();
private:
	vector<Post> posts;
};

Board::Board() {
}

void Board::editBoard() {
	char cmd;
	while (true) {
		cout << "Select a mode:\n 'c'reate a new post\n"
			" 'e'dit an existing post\n 'd'elete a post\n 'q'uit\n";
		cin >> cmd;
		cin.ignore();
		if (cmd == 'c') {
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
		else if (cmd == 'q') {
			// modify the following code to write the record into a file
			for (int i = 0; i < posts.size(); i++) {
				// might have to print the keyword "title: " for later identification
				cout << posts[i].title << endl;
				cout << posts[i].contents;
				for (int j = 0; j < posts[i].comments.size(); j++) {
					cout << "comments " << j << ": ";
					cout << posts[i].comments[j].message << endl;
				}
			}
			// ======================================
			return;
		}
	}
}

void Board::selectPost() {
	int index = 0;
	char selector;
	while (true) {
		cin >> selector;
		if (selector == 'p' && index - 1 >= 0) {
			index--;
			cout << posts[index].title << endl;
		}
		else if (selector == 'n' && index + 1 < posts.size()) {
			index++;
			cout << posts[index].title << endl;
		}
		else {

		}
	}
}
