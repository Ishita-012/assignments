
// #include <iostream>
// #include <queue>
// #include <set>
// using namespace std;

// struct State {
//     int x, y;
// };

// void solve() {
//     queue<State> q;
//     set<pair<int, int>> visited;

//     q.push({0, 0});
//     visited.insert({0, 0});

//     while (!q.empty()) {
//         State s = q.front();
//         q.pop();

//         cout << "(" << s.x << ", " << s.y << ") -> ";

//         if (s.x == 2 || s.y == 2) {
//             cout << "Goal Reached!";
//             return;
//         }

//         State next[] = {
//             {4, s.y},             // Fill 4L jug
//             {s.x, 3},             // Fill 3L jug
//             {0, s.y},             // Empty 4L jug
//             {s.x, 0},             // Empty 3L jug
//             {s.x - min(s.x, 3-s.y), s.y + min(s.x, 3-s.y)},
//             {s.x + min(s.y, 4-s.x), s.y - min(s.y, 4-s.x)}
//         };

//         for (State n : next) {
//             if (!visited.count({n.x, n.y})) {
//                 visited.insert({n.x, n.y});
//                 q.push(n);
//             }
//         }
//     }
// }

// int main() {
//     cout << "State Space Search - Water Jug Problem\n";
//     solve();
//     return 0;
// }

#include <iostream>
#include <queue>
#include <set>
#include <algorithm>
#include <numeric>
using namespace std;

struct State {
    int x, y;
};

int gcd(int a, int b) {
    while (b != 0) {
        int temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

void solve(int cap1, int cap2, int goal) {
    queue<State> q;
    set<pair<int, int>> visited;

    q.push({0, 0});
    visited.insert({0, 0});

    while (!q.empty()) {
        State s = q.front();
        q.pop();

        cout << "(" << s.x << ", " << s.y << ") -> ";

        if (s.x == goal || s.y == goal) {
            cout << "Goal Reached!\n";
            return;
        }

        int pour1to2 = min(s.x, cap2 - s.y);
        int pour2to1 = min(s.y, cap1 - s.x);

        State next[] = {
            {cap1, s.y},                   // Fill jug 1
            {s.x, cap2},                   // Fill jug 2
            {0, s.y},                      // Empty jug 1
            {s.x, 0},                      // Empty jug 2
            {s.x - pour1to2, s.y + pour1to2}, // Pour 1 to 2
            {s.x + pour2to1, s.y - pour2to1}  // Pour 2 to 1
        };

        for (State n : next) {
            if (!visited.count({n.x, n.y})) {
                visited.insert({n.x, n.y});
                q.push(n);
            }
        }
    }

    cout << "No solution found!\n";
}

int main() {
    int cap1, cap2, goal;

    cout << "Enter capacity of first jug: ";
    cin >> cap1;

    cout << "Enter capacity of second jug: ";
    cin >> cap2;

    cout << "Enter required amount: ";
    cin >> goal;

    if (cap1 <= 0 || cap2 <= 0 ||
        goal < 0 || goal > max(cap1, cap2)) {
        cout << "Invalid input!\n";
        return 0;
    }

    if (goal != 0 && goal % gcd(cap1, cap2) != 0) {
        cout << "No solution possible!\n";
        return 0;
    }

    cout << "\nState Space Search - Water Jug Problem\n";
    solve(cap1, cap2, goal);

    return 0;
}
