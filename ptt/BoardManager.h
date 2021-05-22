#pragma once
#include "user.h"
#include <vector>
#include "board.h"
using namespace std;

class BoardManager
{
	enum state
	{
		MENU,
		SELECT_BOARD,
		BOARD,
		POST,
		EXIT
	};
	void run();
	vector<Board> boards;
	vector<User> users;
	int currentUser;
	state currentState;
};

void BoardManager::run()
{
	while (true)
	{
		if (currentState == MENU)
		{
			User user;

		}
		else if (currentState == SELECT_BOARD)
		{

		}
		else if (currentState == BOARD)
		{

		}
		else if (currentState == POST)
		{

		}
		else if (currentState == EXIT)
		{
			exit(0);
		}
		else
		{
			cout << "Enter again\n";
		}

	}
}