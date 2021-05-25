#include <iostream>
#include "user.h"
#include "board.h"
#include "BoardManager.h"
int main()
{
// Testing users
/*	users users;
	users.Register();
	users.Login();
	users.printloginaccount();*/
// Testing Posts
/*	Post newPost;
	newPost.setTitle();
	newPost.setContents();
	cout << "## title: " << newPost.title << endl << "## contents:\n" << newPost.contents;
	cout << "Leave a comment: ";
	newPost.setComment();
	cout << "## comments:\n";
	for (int i = 0; i < newPost.comments.size(); i++) {
		cout << newPost.comments[i].message << endl;
	} */
// Testing Boards
	BoardManager Manager;
	Manager.run();
	Board HatePolitics;
	HatePolitics.createPosts();
	HatePolitics.editBoard();
}