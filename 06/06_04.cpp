#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int INF = 1 << 29;

int main() {
    int n = 4;
    vector<vector<int>> d(n, vector<int>(n, INF));

    for (int i = 0; i < n; i++) {
        d[i][i] = 0;
    }
    d[0][1] = 1;
    d[0][2] = 2;
    d[1][3] = 4;
    d[2][1] = 1;
    d[2][3] = 6;

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == j || d[i][j] >= INF) {
                continue;
            }
            cout << i << "-" << j << ": " << d[i][j] << endl;
        }
    }
}
