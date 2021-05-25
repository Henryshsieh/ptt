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
			//cout << index++ << "." << x.boardName << endl;
		}
	}
	void showPosts(const Board* board)
	{
		int index = 1;
		for (auto x:board->posts)
		{
			cout << index++ << "." << x.title << endl;
		}
	}
	void showContent(const Post* post)
	{
		cout << post->title << endl;
		cout << post->contents << endl;
		for (auto x : post->comments)
		{
			if (x.vote == UPVOTE)
				cout << "good.";
			else if(x.vote == DOWNVOTE)
			{
				cout << "lame.";
			}
			cout << x.message << endl;
		}
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