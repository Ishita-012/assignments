
#include <iostream>
using namespace std;

char b[9] = {'1','2','3','4','5','6','7','8','9'};

void show() {
    cout << "\n";
    for (int i = 0; i < 9; i++) {
        cout << " " << b[i] << " ";
        if (i % 3 != 2) cout << "|";
        else if (i != 8) cout << "\n---+---+---\n";
    }
    cout << "\n\n";
}

int win() {
    int lines[8][3] = {
        {0,1,2},{3,4,5},{6,7,8},
        {0,3,6},{1,4,7},{2,5,8},
        {0,4,8},{2,4,6}
    };

    for (auto &l : lines)
        if (b[l[0]] == b[l[1]] && b[l[1]] == b[l[2]])
            return b[l[0]] == 'O' ? 10 : -10;

    return 0;
}

int minimax(bool computer) {
    int score = win();

    if (score != 0) return score;

    bool full = true;
    for (char c : b)
        if (c >= '1' && c <= '9') full = false;

    if (full) return 0;

    if (computer) {
        int best = -1000;

        for (int i = 0; i < 9; i++) {
            if (b[i] >= '1' && b[i] <= '9') {
                char old = b[i];
                b[i] = 'O';
                int score = minimax(false);
                b[i] = old;
                if (score > best) best = score;
            }
        }
        return best;
    } else {
        int best = 1000;

        for (int i = 0; i < 9; i++) {
            if (b[i] >= '1' && b[i] <= '9') {
                char old = b[i];
                b[i] = 'X';
                int score = minimax(true);
                b[i] = old;
                if (score < best) best = score;
            }
        }
        return best;
    }
}

int main() {
    int move;

    cout << "You are X, Computer is O\n";

    for (int turn = 0; turn < 9; turn++) {
        show();

        if (turn % 2 == 0) {
            cout << "Enter position (1-9): ";
            cin >> move;

            if (move < 1 || move > 9 ||
                b[move - 1] < '1' || b[move - 1] > '9') {
                cout << "Invalid move! Try again.\n";
                turn--;
                continue;
            }

            b[move - 1] = 'X';
        } else {
            int best = -1000, pos = -1;

            for (int i = 0; i < 9; i++) {
                if (b[i] >= '1' && b[i] <= '9') {
                    char old = b[i];
                    b[i] = 'O';
                    int score = minimax(false);
                    b[i] = old;

                    if (score > best) {
                        best = score;
                        pos = i;
                    }
                }
            }

            b[pos] = 'O';
            cout << "Computer chooses position " << pos + 1 << "\n";
        }

        if (win() != 0) {
            show();
            cout << (win() == 10 ? "Computer wins!" : "You win!") << endl;
            return 0;
        }
    }

    show();
    cout << "Game Draw!\n";
    return 0;
}
