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
			cout<<"此帳號名稱已存在 請再輸入一次:";
			return 1;
		}
		int blank = username.find_first_of(" ",0);
		if (blank != string::npos) {
			cout<< "帳號名稱不可含空白鍵 請再輸入一次:";
			return 1;
		}
		return 0;
	}
	bool checkpassword(string password) {
		int blank = password.find_first_of(" ", 0);
		if (blank != string::npos) {
			cout << "密碼不可含空白鍵 請再輸入一次:\n";
			return 1;
		}
		return 0;
	}

	void Register() {
		string username, password;
		cout << "請輸入註冊帳號名稱:";
		getline(cin,username);
		while (checkname(username)) {
			getline(cin, username);
		}
		cout << "請輸入密碼:";
		getline(cin, password);
		while (checkpassword(password)) {
			getline(cin, password);
		}
		user regi_user={username,password,Menber};
		accounts.push_back(regi_user);
		cout << "註冊成功\n";
		cout <<"帳號:"<<regi_user.username << "\n密碼:" << regi_user.password<<endl;
	}
	void Login() {
		string username, password;
		string loginmethod;
		cout << "登入帳號請輸入1 以訪客身分請輸入2:";
		getline(cin,loginmethod);
		if (loginmethod == "1") {
			cout << "請輸入帳號名稱:";
			getline(cin, username);
			while (!findaccount(username)) {
				cout << "查無此帳號 請再輸入一遍:";
				getline(cin, username);
			}
			user login_user;
			for (int i = 0; i < accounts.size(); i++) {
				if (accounts[i].username == username)
					login_user = accounts[i];
			}
			cout << "請輸入密碼:";
			getline(cin, password);
			while (password!=login_user.password) {
				cout << "密碼錯誤 請再輸入一遍";
				getline(cin, password);
			}
			current_user = login_user;
			cout << "登入成功\n";
		}
		else if (loginmethod == "2") {
			current_user.authority = Guest;
			cout << "以訪客登入成功\n";
		}
	}
	void printloginaccount() {
		switch (current_user.authority) {
		case 0:
			cout << "名稱:" << current_user.username << "\n密碼:" << current_user.password << "\n權限:管理員" << endl;
		break;		case 1:
			cout << "名稱:" << current_user.username << "\n密碼:" << current_user.password << "\n權限:一般使用者"<< endl;
			break;
		case 2:
			cout << "'訪客模式\n";
			break;
		case 3:
			cout << "尚未登入\n";
			break;	
		}

	}
private:
	user current_user;
	vector<user> accounts;
};