#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

vector<int> dy{-1, 0, 1, 0};
vector<int> dx{0, 1, 0, -1};

void bfs(const vector<string>& field, int h, int w, int start_y, int start_x) {
    vector<vector<bool>> visited(h, vector<bool>(w, false));
    queue<pair<int, int>> q;
    q.push(make_pair(start_y, start_x));
    while (!q.empty()) {
        int y = q.front().first;
        int x = q.front().second;
        q.pop();
        if (field[y][x] == 'x') {
            cout << x << " " << y << endl;
            return;
        }
        visited[y][x] = true;

        for (int i = 0; i < 4; i++) {
            int ny = y + dy[i];
            int nx = x + dx[i];
            if (0 <= ny && ny < h && 0 <= nx && nx < w && !visited[ny][nx]) {
                q.push(make_pair(ny, nx));
            }
        }
    }
}

int main() {
    int h, w;
    while (cin >> h >> w, h || w) {
        vector<string> field(h);
        for (auto& row : field) {
            cin >> row;
        }
        int x, y;
        cin >> x >> y;
        bfs(field, h, w, y, x);
    }
}
