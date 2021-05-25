#pragma once
#include <vector>
#include <fstream>
#include "board.h"
#include "user.h"
#include "Viewer.h"
#include <filesystem>

using namespace std;

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
void BoardManager::load()//load boards and account infomation
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
	int i = 0;
	for (const auto& file : std::filesystem::recursive_directory_iterator(path))
	{
		int dirLevel = 0;//directory level
		for (int i = 0; i < file.path().string().length(); i++)
		{
			if (file.path().string()[i] == '\\')
				dirLevel++;
		}
		if (dirLevel == 1)
		{
			boards.push_back(Board());
			boards.back().boardName = file.path().filename().string();
		}
		else if(dirLevel == 2)
		{
			boards.back().posts.push_back(Post());
			boards.back().posts.back().title = file.path().filename().string();
		}
		else if (dirLevel == 3)
		{
			if (file.path().filename().string() == "comments.txt")//load comments
			{
				ifstream str;
				string buffer;
				str.open(file.path().c_str());
				if (!str.is_open())
				{
					cout << file.path().string() << "cant be open\n";
				}
				for (int j = 0; getline(str, buffer); j++)
				{
					if (j % 3 == 0)
					{
						boards.back().posts.back().comments.push_back(Comment());
						boards.back().posts.back().comments.back().vote = stoi(buffer);
					}
					else if(j % 3 == 1)
					{
						boards.back().posts.back().comments.back().message = buffer;
					}
					else
					{
						boards.back().posts.back().comments.back().user.username = buffer;

					}
				}
				str.close();
			}
			else if (file.path().filename().string() == "content.txt")//load article
			{
				ifstream str;
				string buffer = "";
				
				str.open(file.path().c_str());
				if (!str.is_open())
				{
					cout << file.path().string() << "cant be open\n";
				}
				while (getline(str, buffer))
				{
					boards.back().posts.back().contents += buffer + "\n";
				}
				str.close();
			}
			else
			{
				boards.back().posts.back().user.username = file.path().filename().string();
			}
		}
		cout << dirLevel << file.path() << endl;
	}
	
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
			cin >> action;
			if (action == 'e')
			{
				currentState = MENU;
			}
			else if (isdigit(action))
			{
				if (action - '0' - 1 < boards.size() && action - '0' - 1 >= 0)
				{
					currentBoard = &boards[action - '0' - 1];
					currentState = BOARD;
				}
				
			}
		}
		while(currentState == BOARD)
		{
			
			viewer.showPosts(currentBoard);
			cin >> action;
			if (action == 'e')
			{
				currentState = SELECT_BOARD;
			}
			else if (action == 's')
			{
				currentBoard->submitPost(currentUser);
			}
			else if (isdigit(action))
			{
				if (action - '0' - 1 < currentBoard->posts.size() && action - '0' - 1 >= 0)
				{
					currentPost = &currentBoard->posts[action - '0' - 1];
					currentState = POST;
				}

			}
		}
		while(currentState == POST)
		{
			viewer.showContent(currentPost);
			cin >> action;
			if (action == 'e')
			{
				currentState = BOARD;
			}
			else if (action = 'E')
			{
				;
			}
			else if (action = 'L')
			{
				;
			}
		}
		while(currentState == EXIT)
		{
			exit(0);
		}
	}
}