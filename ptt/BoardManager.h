#pragma once
#include <vector>
#include <fstream>
#include "board.h"
#include "user.h"
#include "Viewer.h"
#include <filesystem>

using namespace std;
using namespace std::filesystem;

class BoardManager
{
public:
	enum state
	{
		MENU,
		SELECT_BOARD,
		BOARD,
		POST,
		EXIT
	};
	BoardManager();
	void run();
	void load();
	void save();

	Viewer viewer;
	vector<Board> boards;
	vector<User*> users;
	state currentState;
	User* currentUser;
	Post* currentPost;
	Board* currentBoard;
};
BoardManager::BoardManager()
{
	currentBoard = NULL;
	currentPost = NULL;
	currentUser = NULL;
	currentState = MENU;
	load();

}
void BoardManager::load()
{
	fstream file;
	string username;
	string password;
	int auth;
	file.open("accounts.txt", ios::in);
	while (file >> username >> password >> auth)
	{
		users.push_back(new User(username, password, auth));
	}
	file.close();
	string path = "boards";
	cout << "幹";
	
		
}
void BoardManager::run()
{
	while (true)
	{
		currentUser = new User();
		char action;
		while (currentState == MENU)
		{
			viewer.showMenu();
			cin >> action;
			if (action == 'r')
			{
				currentUser = currentUser->Register(users);
				currentState = SELECT_BOARD;
			}
			else if (action == 'l')
			{
				currentUser = currentUser->Login(users);
				currentState = SELECT_BOARD;

			}
			else if (action == 'e')
			{
				currentState = EXIT;
				break;
			}
			else
			{
				cout << "enter again\n";
			}
		}	
		while(currentState == SELECT_BOARD)
		{
			viewer.showBoards(boards);
			/*
			if (selectBoard(boards, currentBoard))
				currentState == BOARD;
			else
			{
				cout << "choose again\n";
			}*/
		}
		while(currentState == BOARD)
		{
			/*
			viewer.showPosts(currentBoard);
			if (selectPost(boards, currentPost))
				currentState == POST;
			else
			{
				cout << "choose again\n";
			}*/
		}
		while(currentState == POST)
		{
			viewer.showContent(currentPost);

		}
		while(currentState == EXIT)
		{
			exit(0);
		}
	}
}