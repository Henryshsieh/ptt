#pragma once	
#include <iostream>
#include <vector>
#include<direct.h>
#include<string>
#include <fstream>

using namespace std;
enum Authority {
	ADMIN = 0,
	MEMBER = 1,
	GUEST = 2,
	Notlogin = 3
};
struct mail
{
	string article, content, sender;
};
class User {
public:
	User()
	{
		username = "GUEST";
		password = "GUEST";
		authority = GUEST;

	}
	User(string name, string _password, int auth) :username(name), password(_password), authority(auth) {};
	User& operator = (User r)
	{
		username = r.username;
		password = r.password;
		authority = r.authority;
		return *this;
	} 
	
	bool findaccount(string username, vector<User*> users) {
		for (auto x : users)
		{

			if (x->username == username) {
				return 1;
			}
		}
		return 0;
	}
	bool checkname(string username, vector<User*> users){
		if (findaccount(username, users)) {
			cout << "Username had been used, enter again:";
			return 1;
		}
		int blank = username.find_first_of(" ", 0);
		if (blank != string::npos) {
			cout << "Username cannot contain spaces, enter again:";
			return 1;
		}
		return 0;
	}
	bool checkpassword(string password) {
		int blank = password.find_first_of(" ", 0);
		if (blank != string::npos) {
			cout << "password cannot contain spaces, enter again:";
			return 1;
		}
		return 0;
	}
	//void newAdmin(vector <User*> users)
	//void sendMessage(vector <User*> users, string receiver)
	User* Register(vector<User*>& users) {
		cout << "Enter the username:";
		cin.ignore();
		string username;
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
		ofstream outfile;
		outfile.open("accounts.txt", std::ios_base::app); // append instead of overwrite
		if (outfile.is_open())
		{
			outfile << username << " " << password << " " << (int)MEMBER << endl;
			outfile.close();
		}
		else
		{
			cout << "aaaaaaaaaaaa\n";
		}
		return users.back();
	}
	User* Login(vector<User*>& users) {
		string loginmethod;
		User tmpUser;
		cout << "Enter 1 for login, enter 2 for login as guests:";
		cin.ignore();
		getline(cin, loginmethod);
		if (loginmethod == "1") {
			cout << "Enter username:";
			getline(cin, tmpUser.username);
			while (!findaccount(tmpUser.username, users)) {
				cout << "No username found,enter again:";
				getline(cin, tmpUser.username);
			}
			cout << "Enter the password:";
			getline(cin, tmpUser.password);
			for (auto x : users) {
				if (x->username == tmpUser.username && x->password == tmpUser.password)
				{
					cout << "login success\n";
					return x;

				}
			}
			while (1) {
				cout << "password is wrong,enter again:";
				getline(cin, tmpUser.password);
				for (auto x : users) {
					if (x->username == tmpUser.username && x->password == tmpUser.password)
					{
						cout << "login success\n";
						return x;

					}
				}
			}
		}
		else if (loginmethod == "2") {
			cout << "login as guests\n";
			return users[0];
		}
	}
	void writemail(bool remail,string reart,string sender,string receiver,vector<User*>& users) {
		string buffer = "",contents = "";
		mail currentmail;
		system("cls");
		if (remail) {
				currentmail.article = "re"+reart;
		}
		else {
			cout << "Article:";
			cin >> currentmail.article;
		}
		cout << "type \"SAVE\" when you finish editing.\nContnet:\n";
		while (getline(cin, buffer)) {
			if (buffer == "SAVE")
			{
				break;
			}
			else
				contents += buffer + "\n";
		}
		currentmail.content = contents;
		currentmail.sender = sender;
		if (remail) {
			for (auto x : users) {
				if (x->username == receiver)
				{
					x->receivemail.push_back(currentmail);
					ofstream file;
					string path = "mails\\" + receiver + "\\";
					_mkdir(path.c_str());
					//save contents
					file.open((path + currentmail.article));
					if (!file.is_open())
					{
						cout << "fuck\n";
					}
					else
					{
						file << "sender:\n";
						file << sender << endl;
						file << "contents:\n";
						file << contents;
					}
					file.close();

				}
			}
		}
		else {
			cout << "Receiver:";
			cin >> receiver;
			while (!findaccount(receiver, users)) {
				cout << "No user found,enter again:";
				cin >> receiver;
			}
			for (auto x : users) {
				if (x->username == receiver)
				{
					x->receivemail.push_back(currentmail);
					ofstream file;
					string path = "mails\\" + receiver + "\\";
					//made dir 
					_mkdir(path.c_str());
					//save contents
					file.open((path + currentmail.article).c_str());
					if (!file.is_open())
					{
						cout << "fuck\n";
					}
					else
					{
						file << "sender:\n";
						file << sender << endl;
						file << "contents:\n";
						file << contents;
					}
					file.close();
				}
			}
		}
	}
	void email(vector<User*>& users)
	{	
		system("cls");
		char action;
		cout<<"(c).check email\n(w).write email\n(p).previous page\n";
		cin >> action;
		system("cls");
		if (action == 'c') {
			if (receivemail.size() == 0) {
				cout << "No receive email\n";
				cout << "(e).exit\n";
				cin >> action;
			}
			else {
				int index;
				for (int i = 1; i <= receivemail.size(); i++)
					cout << "(" << i << ")"<<receivemail[i-1].article << " from "<< receivemail[i-1].sender << endl;
				cin >> index;
				while (index<1 || index>index > receivemail.size()) {
					cout << "Enter again\n";
					cin >> index;
				}
				mail currentmail = receivemail[index - 1];
				system("cls");
				cout << currentmail.article << " from " << currentmail.sender << ":\n" << currentmail.content;
				cout << "(r).reply\n(e).exit\n";
				cin >> action;
				if (action == 'r') {
					writemail(1, currentmail.article, username, currentmail.sender, users);
				}
				else
					email(users);
			}
		}
		else if (action == 'w') {
			writemail(0,"", username,"", users);
		}
	}
	string username, password;
	int authority;
	vector<mail> receivemail;
};