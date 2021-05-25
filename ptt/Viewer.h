#pragma once
#include <vector>
#include "board.h"
#include "user.h"
class Viewer
{

public:
	void showMenu()
	{
		cout << "(r).Register\n";
		cout << "(l).Login\n";
		cout << "(e).Exit\n";
	}
	void showBoards(vector<Board> boards)
	{
		int index = 1;
		for (auto x:boards)
		{
			cout << "("<< index++ << ")" << "." << x.boardName << endl;
		}
		cout << "(e).Previous page" << endl;

	}
	void showPosts(const Board* board)
	{
		int index = 1;
		for (auto x:board->posts)
		{
			cout << "(" << index++ << ")" << "." << x.title << endl;
		}
		cout << "(s).submit a post" << endl;
		cout << "(e).Previous page" << endl;

	}
	void showContent(const Post* post)
	{
		cout << post->title << endl << endl;
		cout <<  post->contents << endl << endl;
		cout << "posted by "<< post->user.username << endl << endl;
		for (auto x : post->comments)
		{
			if (x.vote == UPVOTE)
				cout << "±À ";
			else if(x.vote == DOWNVOTE)
			{
				cout << "¼N ";
			}
			cout << x.message << " " << x.user.username << endl;
		}
		cout << "(E).edit this post\n";
		cout << "(L).Leave comments\n";
		cout << "(e).Previous page\n";
	}
	void showPostOperation(Post* post, User* currentUser)
	{
		/*
		if (currentUser->authority == ADMIN)
		{
			;
		}
		else if (post.user.username == currentUser->username)
		{
			;
		}*/
	}

};