#pragma once
#include <vector>
#include <iomanip>
#include "board.h"
#include "user.h"
class Viewer
{

public:
	void showMenu()
	{
		system("cls");
		cout << "(g).Game\n";
		cout << "(m).Mail\n";
		cout << "(s).Select Board\n";
		cout << "(e).Exit\n";
	}

	void showLoginMenu()
	{
		system("cls");
		cout << "(r).Register\n";
		cout << "(l).Login\n";
		cout << "(e).Exit\n";
	}
	void showBoards(vector<Board> boards, User* currentUser)
	{
		system("cls");
		int index = 1;
		for (auto x:boards)
		{
			cout << "("<< index++ << ")" << "." << x.boardName << endl;
		}
		if (currentUser->authority == ADMIN)
		{
			cout << "(c).create new board" << endl;
		}
		cout << "(e).previous page" << endl;

	}
	void showBoardOperation(const Board* board, const User* user)
	{
		bool isMod = false;
		for (auto x : board->moderator)
		{
			if (x.username == user->username)
				isMod = true;
		}
		if (isMod || user->authority == ADMIN)
		{
			cout << "(r).remove board\n";
		}
	}
	void showPosts(const Board* board)
	{
		system("cls");
		int index = 1;
		for (auto x:board->posts)
		{
			cout << "(" << index++ << ")" << "." << x.title << endl;
		}
		cout << "(s).submit a post" << endl;
		cout << "(e).previous page" << endl;

	}
	void showContent(const Post* post, User* currentUser)
	{
		system("cls");
		cout << post->title << endl << endl;
		cout <<  post->contents << endl << endl;
		cout << "posted by "<< post->user.username << endl << endl;
		for (auto x : post->comments)
		{
			if (x.vote == UPVOTE)
				cout << "�� ";
			else if(x.vote == DOWNVOTE)
			{
				cout << "�N ";
			}
			cout << left << setw(40) << x.message << " "  << setw(10) << x.user.username << endl;
		}
		if (post->user.username == currentUser->username)//is owner or isadmin
		{
			cout << "(E).edit this post\n";
		}
		if(currentUser->authority == ADMIN || post->user.username == currentUser->username)
		{
			cout << "(d).delete this post\n";
		}
		if (currentUser->authority == ADMIN)
		{
			cout << "(r).delete specific comment\n";
		}
		cout << "(l).leave comments\n";
		cout << "(e).previous page\n";
	}
	void showgames() {
		system("cls");
		cout << "(c).climb ladder\n";
		cout << "(p).poker\n";
		cout << "(P).Pikachu volley ball\n";
		cout << "(C).chess\n";
		cout << "(t).ticTacToe\n";
		cout << "(q).quit\n";

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