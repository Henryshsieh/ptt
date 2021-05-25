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
	Comment() 
	{
		vote = 0;
		message = "";
	}
	Comment(bool _vote, string _message):vote(_vote), message(_message){}
	//User user;
};

struct Post
{
public:
	Post()
	{
		title = "";
		contents = "";
	}
	Post(string _title, string _contents, vector<Comment> _comments)
	{
		title = _title;
		contents = _contents;
		comments.assign(_comments.begin(), _comments.end());
	}
	void setTitle();//user as paramater
	void setContents();//user as paramater
	void setComment();//user as paramater
	string title;
	string contents;
	vector<Comment> comments;
	//User user;
	//bool editComment(User* currentUser);

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
	Board() 
	{
		boardName = "";
	}
	Board(string _boardName, vector<Post> _posts)
	{
		boardName = _boardName;
		posts.assign(_posts.begin(), _posts.end());
	}
	void editBoard();//user as paramater
	int selectPost();
	void createPosts(); // create dummy posts for testing//user as paramater
	vector<Post> posts;
	//vector <user> moderator;
	string boardName;
	//bool addBoard(User* currentUser);
	//bool removePost(User* currentUser);
	//bool setMod(vector<User*> user, User* currentUser);
	//friend bool removeBoard(vector<Board> boards, Board* currentBoard, User* currentUser);

};

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

