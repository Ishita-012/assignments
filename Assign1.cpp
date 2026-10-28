
// #include <iostream>
// #include <queue>
// #include <map>
// #include <algorithm>
// #include <cmath>
// using namespace std;

// struct Node {
//     string state;
//     int g, f;
// };

// struct Compare {
//     bool operator()(Node a, Node b) {
//         return a.f > b.f;
//     }
// };

// // Manhattan distance heuristic
// int h(string s) {
//     int distance = 0;

//     for (int i = 0; i < 9; i++) {
//         if (s[i] != '0') {
//             int n = s[i] - '1';
//             distance += abs(i / 3 - n / 3)
//                       + abs(i % 3 - n % 3);
//         }
//     }
//     return distance;
// }

// int main() {
//     string start, goal = "123456780";

//     cout << "Enter initial state (use 0 for blank): ";
//     cin >> start;

//     priority_queue<Node, vector<Node>, Compare> pq;
//     map<string, int> cost;
//     map<string, string> parent;

//     pq.push({start, 0, h(start)});
//     cost[start] = 0;
//     parent[start] = "";

//     while (!pq.empty()) {
//         Node cur = pq.top();
//         pq.pop();

//         string s = cur.state;

//         if (cur.g != cost[s])
//             continue;

//         if (s == goal) {
//             vector<string> path;

//             while (s != "") {
//                 path.push_back(s);
//                 s = parent[s];
//             }

//             reverse(path.begin(), path.end());

//             cout << "\nSolution Path:\n";

//             for (string p : path) {
//                 for (int i = 0; i < 9; i++) {
//                     cout << p[i] << " ";
//                     if (i % 3 == 2)
//                         cout << endl;
//                 }
//                 cout << endl;
//             }

//             cout << "Total moves: " << path.size() - 1;
//             return 0;
//         }

//         int pos = s.find('0');
//         int r = pos / 3, c = pos % 3;
//         int dr[] = {-1, 1, 0, 0};
//         int dc[] = {0, 0, -1, 1};

//         for (int i = 0; i < 4; i++) {
//             int nr = r + dr[i];
//             int nc = c + dc[i];

//             if (nr >= 0 && nr < 3 &&
//                 nc >= 0 && nc < 3) {

//                 string next = s;
//                 swap(next[pos], next[nr * 3 + nc]);

//                 int newCost = cur.g + 1;

//                 if (!cost.count(next) ||
//                     newCost < cost[next]) {
//                     cost[next] = newCost;
//                     parent[next] = s;

//                     pq.push({next, newCost,
//                              newCost + h(next)});
//                 }
//             }
//         }
//     }

//     cout << "No solution found.";
//     return 0;
// }


#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct Node {
    string state;
    int g, f;
};

struct Compare {
    bool operator()(Node a, Node b) {
        return a.f > b.f;
    }
};

// Misplaced Tiles Heuristic
int h(string s) {
    string goal = "123456780";
    int misplaced = 0;

    for (int i = 0; i < 9; i++) {
        if (s[i] != '0' && s[i] != goal[i]) {
            misplaced++;
        }
    }

    return misplaced;
}

int main() {
    string start, goal = "123456780";

    cout << "Enter initial state (use 0 for blank): ";
    cin >> start;

    priority_queue<Node, vector<Node>, Compare> pq;
    map<string, int> cost;
    map<string, string> parent;

    pq.push({start, 0, h(start)});
    cost[start] = 0;
    parent[start] = "";

    while (!pq.empty()) {
        Node cur = pq.top();
        pq.pop();

        string s = cur.state;

        if (cur.g != cost[s])
            continue;

        if (s == goal) {
            vector<string> path;

            while (s != "") {
                path.push_back(s);
                s = parent[s];
            }

            reverse(path.begin(), path.end());

            cout << "\nSolution Path:\n";

            for (string p : path) {
                for (int i = 0; i < 9; i++) {
                    cout << p[i] << " ";
                    if (i % 3 == 2)
                        cout << endl;
                }
                cout << endl;
            }

            cout << "Total moves: " << path.size() - 1;
            return 0;
        }

        int pos = s.find('0');
        int r = pos / 3, c = pos % 3;

        int dr[] = {-1, 1, 0, 0};
        int dc[] = {0, 0, -1, 1};

        for (int i = 0; i < 4; i++) {
            int nr = r + dr[i];
            int nc = c + dc[i];

            if (nr >= 0 && nr < 3 &&
                nc >= 0 && nc < 3) {

                string next = s;
                swap(next[pos], next[nr * 3 + nc]);

                int newCost = cur.g + 1;

                if (!cost.count(next) ||
                    newCost < cost[next]) {

                    cost[next] = newCost;
                    parent[next] = s;

                    pq.push({next, newCost,
                             newCost + h(next)});
                }
            }
        }
    }

    cout << "No solution found.";
    return 0;
}
