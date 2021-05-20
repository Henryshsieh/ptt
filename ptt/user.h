#include <iostream>
#include <vector>
#include<string>
using namespace std;
enum Authority {
	Admin = 0,
	Menber = 1,
	Guest = 2,
	Notlogin = 3
};
typedef struct {
	string username, password;
	Authority authority;
}user;
class users {
public:
	users() {
		user adminadministrator = {
			"ntust","12345",Admin
		};
		accounts.push_back(adminadministrator);
		current_user.authority = Notlogin;
	}
	bool findaccount(string username) {
		for (int i = 0; i < accounts.size(); i++) {
			if (accounts[i].username == username) {
				return 1;
			}
		}
		return 0;
	}
	bool checkname(string username) {
		if (findaccount(username)) {
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
			cout << "Password cannot contain spaces, enter again:\n";
			return 1;
		}
		return 0;
	}

	void Register() {
		string username, password;
		cout << "Enter the username:";
		getline(cin, username);
		while (checkname(username)) {
			getline(cin, username);
		}
		cout << "Enter the password:";
		getline(cin, password);
		while (checkpassword(password)) {
			getline(cin, password);
		}
		user regi_user = { username,password,Menber };
		accounts.push_back(regi_user);
		cout << "Register success\n";
		cout << "username:" << regi_user.username << "\npassword:" << regi_user.password << endl;
	}
	void Login() {
		string username, password;
		string loginmethod;
		cout << "Enter 1 for login, enter 2 for login as guests:";
		getline(cin, loginmethod);
		if (loginmethod == "1") {
			cout << "Enter username:";
			getline(cin, username);
			while (!findaccount(username)) {
				cout << "Username does not exist, enter again";
				getline(cin, username);
			}
			user login_user;
			for (int i = 0; i < accounts.size(); i++) {
				if (accounts[i].username == username)
					login_user = accounts[i];
			}
			cout << "Enter the password:";
			getline(cin, password);
			while (password != login_user.password) {
				cout << "Password is wrong, enter again:";
				getline(cin, password);
			}
			current_user = login_user;
			cout << "login success\n";
		}
		else if (loginmethod == "2") {
			current_user.authority = Guest;
			cout << "login as guest success\n";
		}
	}
	void printloginaccount() {
		switch (current_user.authority) {
		case 0:
			cout << "Username:" << current_user.username << "\nPassword:" << current_user.password << "\nAuthority:admin" << endl;
		break;		case 1:
			cout << "Username:" << current_user.username << "\nPassword:" << current_user.password << "\nAuthority:user" << endl;
			break;
		case 2:
			cout << "guest\n";
			break;
		case 3:
			cout << "not yet logged in\n";
			break;
		}

	}
private:
	user current_user;
	vector<user> accounts;
};