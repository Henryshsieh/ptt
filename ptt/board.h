#pragma once

#include "user.h"
#include <vector>
#include <string>
#include <fstream>
#include<direct.h>

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
	User user;
};

struct Post
{
public:
	Post():user(User())
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
	void setTitle();
	void setContents();
	void setComment();

	string title;
	string contents;
	vector<Comment> comments;
	User user;
	//bool editComment(User* currentUser);

};

void Post::setTitle() {
	cout << "Title: ";
	cin.ignore(22222,'\n');
	getline(cin, title);
}

void Post::setContents() {
	string buffer = "";
	cout << "Editing:\n *type \"SAVE\" when you finish editing.\n";
	while (getline(cin, buffer)) {
		if (buffer == "SAVE")
		{
			cout << "contents saved.\n";
			break;
		}
		else
			contents += buffer + "\n";
	}
	

}

void Post::setComment() {
	Comment newComment;
	cout << "leave a comment: ";
	cin.ignore();
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
	void editBoard();
	int selectPost();
	void submitPost(User* user)
	{
		posts.push_back(Post());
		posts.back().setTitle();
		posts.back().setContents();
		posts.back().user = *user;
		savePost();
	}
	void leaveComment(Post* currentPost, User* currentUser)
	{
		currentPost->comments.push_back(Comment());
		cout << "(0.)��\n";
		cout << "(1.)�N\n";
		cin >> currentPost->comments.back().vote;
		cin.ignore();
		cout << "enter message:\n";
		(getline(cin, currentPost->comments.back().message));
		currentPost->comments.back().user = *currentUser;
		saveComments(currentPost);
	}
	void saveComments(Post* currentPost) {
		ofstream file;
		string path = "boards\\" + boardName + "\\" + currentPost->title;
		//save commmets
		file.open((path + "\\comments.txt").c_str(), std::ios::app);
		if (!file.is_open())
		{
			cout << "fuck\n";
		}
		else
		{
			file << (int)currentPost->comments.back().vote << endl;
			file << currentPost->comments.back().message << endl;
			file << currentPost->comments.back().user.username << endl;
		}
		file.close();

	}
	void savePost()
	{
		ofstream file;
		string path = "boards\\" + boardName + "\\" +posts.back().title;
		//made dir of board
		_mkdir(path.c_str());
		//save contents
		file.open((path + "\\contents.txt").c_str());
		if (!file.is_open())
		{
			cout << "fuck\n";
		}
		else
		{
			file << posts.back().contents;
		}
		ofstream ffile((path + "\\" + posts.back().user.username));//touch user
		if (!ffile.is_open())
		{
			cout << "fuck\n";
		}
		ffile.close();
		file.open((path + "\\comments.txt").c_str());
		file.close();


	}
	void createPosts(); // create dummy posts for testing
	vector<Post> posts;
	vector <User> moderator;
	string boardName;
	//void editPost(Post* currentPost, User* currentUser);
	bool setMod(vector<User*> users, User* currentUser)//�]���D ���p�߼g�� ��admin�N�n
	{
		bool isMod = false;
		bool isExists = false;
		string username;
		for (auto x : moderator)
		{
			if (x.username == currentUser->username)
				isMod = true;
		}
		if (currentUser->authority == ADMIN || isMod)
		{
			cout << "Set whih one to be Mod:";
			cin >> username;
			for (auto x : users)
			{
				if (username == x->username)
				{
					isExists = true;
					moderator.push_back(*x);
				}
			}
		}
		if (!isExists)
		{
			cout << "user does not exist.\n";
		}
	}
	//void removeBoard(vector<Board> boards, User* currentUser);

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

