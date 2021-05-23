#pragma once
#include "user.h"
#include <vector>
#include <string>
#include <fstream>
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
	int selectPost();
	void createPosts(); // create dummy posts for testing
private:
	vector<Post> posts;
};

Board::Board() {
}

void Board::editBoard() {
	char cmd;
	while (true) {
		cout << "Select a mode:\n 'c'reate a new post\n"
			" 'v'iew existing posts\n 'q'uit\n 'p'rint (for testing)\n";
		cin >> cmd;
		cin.ignore();
		if (cmd == 'c') {
			Post newPost;
			newPost.setTitle();
			newPost.setContents();
			newPost.setComment();
			posts.push_back(newPost);
		}
		else if (cmd == 'v') {
			int i = selectPost();
			char mode;
			cout << " 'e'dit, 'd'elete or 'c'omment: ";
			cin >> mode;
			if (mode == 'e') {
				cin.ignore();
				posts[i].setTitle();
				posts[i].setContents();
				posts[i].setComment();
			}
			else if (mode == 'd') {
				posts.erase(posts.begin() + i);
			}
			else if (mode == 'c') {
				cin.ignore();
				posts[i].setComment();
			}
		}
		else if (cmd == 'q') {
		// save the entire board to a txt file
			//ofstream file;
			//file.open("boardRecord.txt");
			//for (int i = 0; i < posts.size(); i++) {
			//	file << "Title: ";
			//	file << posts[i].title << endl;
			//	file << posts[i].contents;
			//	for (int j = 0; j < posts[i].comments.size(); j++) {
			//		file << "comment " << j << ": ";
			//		file << posts[i].comments[j].message << endl;
			//	}
			//}
			//file.close();
			return;
		}
		// for testing only
		else if (cmd == 'p') {
			for (int i = 0; i < posts.size(); i++) {
				cout << "Title: ";
				cout << posts[i].title << endl;
				cout << posts[i].contents;
				for (int j = 0; j < posts[i].comments.size(); j++) {
					cout << "comment " << j << ": ";
					cout << posts[i].comments[j].message << endl;
				}
			}
		}
	}
}

int Board::selectPost() {
	int index = 0;
	char selector, cmd;
	cout << "Title: " << posts[index].title << endl;
	cout << " enter 'c' to select this post: ";
	cin >> cmd;
	if (cmd == 'c')
		return index;
	while (true) {
		cout << " select a post: 'p'revious or 'n'ext: ";
		cin >> selector;
		if (selector == 'p' && index - 1 >= 0) {
			index--;
			cout << "Title: " << posts[index].title << endl;
			cout << " enter 'c' to select this post: ";
			cin >> cmd;
			if (cmd == 'c')
				return index;
		}
		else if (selector == 'n' && index + 1 < posts.size()) {
			index++;
			cout << "Title: " << posts[index].title << endl;
			cout << " enter 'c' to select this post: ";
			cin >> cmd;
			if (cmd == 'c')
				return index;
		}
		cout << "Title: " << posts[index].title << endl;
	}
}

void Board::createPosts() {
	Post temp;
	for (int i = 0; i < 5; i++) {
		temp.title = "post " + to_string(i);
		posts.push_back(temp);
	}
}
