#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;
int deal(string face[13], string suit[4]);
void poker() {
	system("cls");
	cout << "Rank1:Straight flush\n";
	cout << "Rank2:Four of a kind\n";
	cout << "Rank3:Full house\n";
	cout << "Rank4:Flush\n";
	cout << "Rank5:Straight\n";
	cout << "Rank6:Three of a kind\n";
	cout << "Rank7:Two pair\n";
	cout << "Rank8:One pair\n";
	cout << "Rank9:High card\n";
	cout << "Enter s to start game:";
	string face[13] =
	{ "Ace","Deuce","Three","Four",
	 "Five","Six","Seven","Eight",
	 "Nine","Ten","Jack","Queen","King" };

	string suit[4] =
	{ "Spades","Club","Heart","Diamonds" };
	int ca, cb;
	char start;
	srand(time(NULL));
	cin >> start;
	while (start=='s') {
		system("cls");
		cout << "Your cards:\n";
		ca = deal(face, suit);
		cout << "\n\nOpponent's cards:\n";
		cb = deal(face, suit);
		cout << "\n\n";
		if(ca>cb)
			cout << "You lose\n\n";
		else if (cb > ca)
			cout << "You win\n\n";
		else
			cout << "Tie\n\n";
		cout << "(s).play again\n";
		cout << "(q).quit\n";
		cin >> start;
	}
}
int deal(string face[13], string suit[4]) {
	int deck[52], i, j, temp, a, b, c[7], check, cn[13] = { 0 }, cstr[7];

	for (i = 0; i < 52; i++)
		deck[i] = i;




	for (i = 0; i < 52; i++) {
		a = rand() % 52;
		temp = deck[i];
		deck[i] = deck[a];
		deck[a] = temp;
	}

	for (i = 0; i < 5; i++) {
		c[i] = deck[i];
		cout << setprecision(5) << face[(deck[i] % 13)] << " of " << suit[(deck[i] / 13)] << endl;
		cstr[i] = c[i] % 13;
	}


	for (i = 4; i > 0; i--)
		for (j = 0; j < i; j++) {
			if (c[i] > c[i + 1]) {
				int temp = c[i];
				c[i] = c[i + 1];
				c[i + 1] = temp;
			}
			if (cstr[i] > cstr[i + 1]) {
				int temp = cstr[i];
				cstr[i] = cstr[i + 1];
				cstr[i + 1] = temp;
			}
		}

	check = 1;
	for (i = 0; i < 4; i++) {
		if (c[i + 1] - c[i] != 1) {
			check = 0;
		}

	}

	cn[c[0] % 13]++;
	cn[c[2] % 13]++;
	cn[c[3] % 13]++;
	cn[c[4] % 13]++;
	cn[c[5] % 13]++;
	cout << "\n\n";
	if (check) {
		if (c[4] % 13 >= 5) {
			cout << "Straight flush";
			return 1;
		}
	}

	for (i = 0; i < 13; i++) {
		if (cn[i] == 4)
			check = 1;
	}

	if (check) {
		cout << "Four of a kind";
		return 2;
	}

	for (i = 0; i < 13; i++)
		if (cn[i] == 3)
			for (j = 0; j < 13; j++) {
				if (cn[j] == 2)
					check = 1;
				else {
					cout << "Three of king";
					return 6;
				}
			}
	if (check) {
		cout << "Full house";
		return 3;
	}
	check = 1;
	for (i = 0; i < 5; i++) {
		if (c[i + 1] / 13 != c[i] / 13)
			check = 0;
	}

	if (check) {
		cout << "Flush";
		return 4;
	}

	check = 1;
	for (i = 0; i < 5; i++)
		if (cstr[i + 1] - cstr[i] != 1)
			check = 0;

	if (check) {
		if (c[4] >= 5) {
			cout << "Straight";
			return 5;
		}
	}

	int count = 0;
	for (i = 0; i < 13; i++)
		if (cn[i] == 2)
			count++;
	if (count == 2) {
		cout << "Two pair";
		return 7;
	}
	else if (count == 1) {
		cout << "One pair";
		return 8;
	}
	else
		cout << "High card";
	return 9;


}
void climbladder() {
	srand(time(NULL));
	int num_of_candidates, ladder_size, dest;
	char start='a';
	while (start == 'a') {
		system("cls");
		cout << "How many candidates: ";
		cin >> num_of_candidates;
		ladder_size = num_of_candidates * 1.5;
		vector<string> candidates(num_of_candidates);
		vector<int> rails(ladder_size);
		cin.ignore();
		cout << "Enter candidates\n";
		for (int i = 0; i < num_of_candidates; i++) {
			cout << "candidate " << i << ": ";
			getline(cin, candidates[i]);
		}

		for (int i = 0; i < ladder_size; i++)
			rails[i] = rand() % (num_of_candidates - 1);

		//===== print the ladder
		for (int i = 0; i < ladder_size; i++)
			cout << rails[i] << " ";
		cout << endl;
		//=====

		for (int i = 0; i < num_of_candidates; i++) {
			dest = i;
			for (int j = 0; j < ladder_size; j++) {
				if (rails[j] == dest)
					dest++;
				else if (rails[j] == dest - 1)
					dest--;
			}
			cout << "#" << dest << "\t" << candidates[i] << endl;
		}

		cout << "(a).play again\n(q).quit\n";
		cin >> start;
	}
}


