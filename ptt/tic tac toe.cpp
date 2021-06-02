#include <cstdlib>
#include <iostream>
using namespace std;

bool checkWin(char t[][3], char player) {
	for (int i = 0; i < 3; i++)
		if (t[i][0] == player && t[i][1] == player && t[i][2] == player || t[0][i] == player && t[1][i] == player && t[2][i] == player)
			return true;
	if (t[0][0] == player && t[1][1] == player && t[2][2] == player || t[0][2] == player && t[1][1] == player && t[2][0] == player)
		return true;
	else
		return false;
}

void printBoard(char t[][3]) {
	cout << "*TIC-TAC-TOE*\n";
	for(int i = 0; i < 3; i++){
		cout << "-------------\n";
		for(int j = 0; j < 3; j++)
			cout<< "| " << t[i][j] << " ";
		cout << "|\n";
	}
	cout << "-------------\n";
}

void ticTacToe() {
	char t[3][3] = {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '};
	int m, n;
	char player;
	
	for(int i = 0; i < 9; i++) {
		if(i % 2 == 0)
			player = 'X';
		else
			player = 'O';
		
		printBoard(t);
		
		do{
			cout << "Enter a coordinate for player " << player << ": ";
			cin >> m >> n;
		} while(!(m >= 0 && m <= 2 && n >= 0 && n <= 2) || t[m][n] != ' ');
		t[m][n] = player;
		
		if(checkWin(t, player) == true){
			system("cls");
			printBoard(t);
			cout << "Player " << player << " wins!\n";
			return;
		}
		
		system("cls");
	}
	printBoard(t);
	cout << "Tie!\n";
			
}

int main() {
	ticTacToe();
}
