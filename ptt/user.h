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
	string username,password;
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
	bool checkname(string username){
		if (findaccount(username)) {
			cout<<"���b���W�٤w�s�b �ЦA��J�@��:";
			return 1;
		}
		int blank = username.find_first_of(" ",0);
		if (blank != string::npos) {
			cout<< "�b���W�٤��i�t�ť��� �ЦA��J�@��:";
			return 1;
		}
		return 0;
	}
	bool checkpassword(string password) {
		int blank = password.find_first_of(" ", 0);
		if (blank != string::npos) {
			cout << "�K�X���i�t�ť��� �ЦA��J�@��:\n";
			return 1;
		}
		return 0;
	}

	void Register() {
		string username, password;
		cout << "�п�J���U�b���W��:";
		getline(cin,username);
		while (checkname(username)) {
			getline(cin, username);
		}
		cout << "�п�J�K�X:";
		getline(cin, password);
		while (checkpassword(password)) {
			getline(cin, password);
		}
		user regi_user={username,password,Menber};
		accounts.push_back(regi_user);
		cout << "���U���\\n";
		cout <<"�b��:"<<regi_user.username << "\n�K�X:" << regi_user.password<<endl;
	}
	void Login() {
		string username, password;
		string loginmethod;
		cout << "�n�J�b���п�J1 �H�X�Ȩ����п�J2:";
		getline(cin,loginmethod);
		if (loginmethod == "1") {
			cout << "�п�J�b���W��:";
			getline(cin, username);
			while (!findaccount(username)) {
				cout << "�d�L���b�� �ЦA��J�@�M:";
				getline(cin, username);
			}
			user login_user;
			for (int i = 0; i < accounts.size(); i++) {
				if (accounts[i].username == username)
					login_user = accounts[i];
			}
			cout << "�п�J�K�X:";
			getline(cin, password);
			while (password!=login_user.password) {
				cout << "�K�X���~ �ЦA��J�@�M";
				getline(cin, password);
			}
			current_user = login_user;
			cout << "�n�J���\\n";
		}
		else if (loginmethod == "2") {
			current_user.authority = Guest;
			cout << "�H�X�ȵn�J���\\n";
		}
	}
	void printloginaccount() {
		switch (current_user.authority) {
		case 0:
			cout << "�W��:" << current_user.username << "\n�K�X:" << current_user.password << "\n�v��:�޲z��" << endl;
		break;		case 1:
			cout << "�W��:" << current_user.username << "\n�K�X:" << current_user.password << "\n�v��:�@��ϥΪ�"<< endl;
			break;
		case 2:
			cout << "'�X�ȼҦ�\n";
			break;
		case 3:
			cout << "�|���n�J\n";
			break;	
		}

	}
private:
	user current_user;
	vector<user> accounts;
};