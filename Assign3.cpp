
#include <iostream>
#include <string>
#include <vector>
#include <cctype>
using namespace std;

string w1, w2, result;
vector<char> letters;
int val[256], used[10] = {0};

long long number(string s) {
    long long n = 0;
    for (char c : s)
        n = n * 10 + val[(unsigned char)c];
    return n;
}

bool leadingZero(char c) {
    return (w1[0] == c && w1.size() > 1) ||
           (w2[0] == c && w2.size() > 1) ||
           (result[0] == c && result.size() > 1);
}

bool solve(int k) {
    if (k == letters.size()) {
        return number(w1) + number(w2) == number(result);
    }

    char c = letters[k];

    for (int d = 0; d <= 9; d++) {
        if (used[d]) continue;
        if (d == 0 && leadingZero(c)) continue;

        val[(unsigned char)c] = d;
        used[d] = 1;

        if (solve(k + 1))
            return true;

        used[d] = 0;
        val[(unsigned char)c] = -1;
    }

    return false;
}

int main() {
    string eq, left;
    cout << "Enter equation (e.g. SEND + MORE = MONEY): ";
    getline(cin, eq);

    // Remove spaces and convert to uppercase
    string s;
    for (unsigned char c : eq)
        if (!isspace(c))
            s += toupper(c);

    int e = s.find('=');
    if (e == string::npos || s.find('=', e + 1) != string::npos) {
        cout << "Invalid equation";
        return 0;
    }

    left = s.substr(0, e);
    result = s.substr(e + 1);

    int p = left.find('+');
    if (p == string::npos || left.find('+', p + 1) != string::npos ||
        result.empty()) {
        cout << "Enter two words + one result word";
        return 0;
    }

    w1 = left.substr(0, p);
    w2 = left.substr(p + 1);

    if (w1.empty() || w2.empty()) {
        cout << "Invalid equation";
        return 0;
    }

    for (char c : s) {
        if (c == '+' || c == '=') continue;
        if (!isalpha((unsigned char)c)) {
            cout << "Use letters and + = only";
            return 0;
        }

        bool found = false;
        for (char x : letters)
            if (x == c) found = true;

        if (!found)
            letters.push_back(c);
    }

    if (letters.size() > 10) {
        cout << "Too many unique letters (maximum 10)";
        return 0;
    }

    if (w1.size() > 18 || w2.size() > 18 || result.size() > 18) {
        cout << "Words are too long";
        return 0;
    }

    for (int i = 0; i < 256; i++)
        val[i] = -1;

    if (solve(0)) {
        cout << "\nSolution found:\n";

        for (char c : letters)
            cout << c << " = " << val[(unsigned char)c] << endl;

        cout << "\n" << number(w1) << " + "
             << number(w2) << " = " << number(result) << endl;
    } else {
        cout << "No solution exists";
    }

    return 0;
}
