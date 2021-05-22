// ptt.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
//#include "user.h"
#include "board.h"
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
	Board HatePolitics;
	HatePolitics.editBoard();
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
