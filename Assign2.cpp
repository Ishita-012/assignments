
#include <iostream>
#include <algorithm>
using namespace std;

int main() {
    int n, d[10][10], p[10], best = 0;

    cout << "Enter number of cities: ";
    cin >> n;

    cout << "Enter distance matrix:\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            cin >> d[i][j];

    for (int i = 0; i < n; i++)
        p[i] = i;

    for (int i = 0; i < n; i++)
        best += d[p[i]][p[(i + 1) % n]];

    bool improved = true;

    while (improved) {
        improved = false;

        for (int i = 1; i < n - 1; i++) {
            for (int j = i + 1; j < n; j++) {
                swap(p[i], p[j]);

                int cost = 0;
                for (int k = 0; k < n; k++)
                    cost += d[p[k]][p[(k + 1) % n]];

                if (cost < best) {
                    best = cost;
                    improved = true;
                } else {
                    swap(p[i], p[j]);
                }
            }
        }
    }

    cout << "\nBest route: ";

    for (int i = 0; i < n; i++)
        cout << p[i] + 1 << " -> ";

    cout << p[0] + 1;

    cout << "\nMinimum distance: " << best;

    return 0;
}
