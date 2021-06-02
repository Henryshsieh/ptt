#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <string>
using namespace std;

int main() {
    srand(time(NULL));
    int num_of_candidates, ladder_size, dest;
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

    return 0;
}
