#pragma once	
#include <iostream>
#include <vector>
#include<string>
using namespace std;
enum Authority {
	ADMIN = 0,
	MEMBER = 1,
	GUEST = 2,
	Notlogin = 3
};
class User {
public:
	User()
	{
		username = "GUEST";
		password = "GUEST";
		authority = GUEST;

	}
	User(string name, string _password, int auth):username(name), password(_password), authority(auth){};

	bool findaccount(string username, vector<User*>& users) {
		for (auto x : users)
		{
			if (x->username == username)
				return 1;
		}
		return 0;
	}
	bool checkname(string username, vector<User*>& users){
		if (findaccount(username, users)) {
			cout << "Username had been used, enter again:";
			return 1;
		}
		int blank = username.find_first_of(" ",0);
		if (blank != string::npos) {
			cout << "Username cannot contain spaces, enter again:";
			return 1;
		}
		return 0;
	}
	bool checkpassword(string password) {
		int blank = password.find_first_of(" ", 0);
		if (blank != string::npos) {
			cout << "±K½X¤£¥i§tªÅ¥ÕÁä ½Ð¦A¿é¤J¤@¦¸:\n";
			return 1;
		}
		return 0;
	}

	User* Register(vector<User*>& users) {
		cout << "Enter the username:";
		cin.ignore();
		getline(cin,username);
		while (checkname(username, users)) {
			getline(cin, username);
		}
		cout << "Enter the password:";
		getline(cin, password);
		while (checkpassword(password)) {
			getline(cin, password);
		}
		cout << "Register success\n";
		cout << "username:" << username << "\npassword:" << password << endl;
		users.push_back(new User(username, password, MEMBER));
		return users.back();
	}
	User* Login(vector<User*>& users) {
		string loginmethod;
		User tmpUser;
		cout << "Enter 1 for login, enter 2 for login as guests:";
		cin.ignore();
		getline(cin,loginmethod);
		if (loginmethod == "1") {
			cout << "Enter username:";
			getline(cin, tmpUser.username);
			cout << "Enter the password:";
			getline(cin, tmpUser.password);

			while (!findaccount(tmpUser.username, users)) {
				cout << "enter again";
				cout << "Enter username:";
				getline(cin, tmpUser.username);
				cout << "Enter the password:";
				getline(cin, tmpUser.password);


			}

			for (auto x : users) {
				if (x->username == tmpUser.username && x->password == tmpUser.password)
				{
					cout << "login success\n";
					return x;

				}
			}
			cout << "password is wrong\n";
		}
		else if (loginmethod == "2") {
			cout << "login as guests\n";
			return users[0];
		}
	}
	void printloginaccount() {
		switch (authority) {
		case 0:
			cout << "¦WºÙ:" << username << "\n±K½X:" << password << "\nÅv­­:ºÞ²z­û" << endl;
		break;		case 1:
			cout << "¦WºÙ:" << username << "\n±K½X:" << password << "\nÅv­­:¤@¯ë¨Ï¥ÎªÌ"<< endl;
			break;
		case 2:
			cout << "'³X«È¼Ò¦¡\n";
			break;
		case 3:
			cout << "©|¥¼µn¤J\n";
			break;	
		}

	}

	string username, password;
	int authority;
};