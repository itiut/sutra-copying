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
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

const int SIZE = 70;
vector<int> dy{1, 1, 0, -1, -1, 0};
vector<int> dx{0, 1, 1, 0, -1, -1};

int main() {
    int t, n;
    while (cin >> t >> n, t || n) {
        vector<vector<int>> field(SIZE, vector<int>(SIZE, 0));
        for (int i = 0; i < n; i++) {
            int x, y;
            cin >> x >> y;
            y += SIZE/2;
            x += SIZE/2;
            field[y][x] = -1;
        }
        int start_x, start_y;
        cin >> start_x >> start_y;
        start_y += SIZE/2;
        start_x += SIZE/2;
        field[start_y][start_x] = 1;

        deque<pair<int, int>> q;
        q.push_back(make_pair(start_y, start_x));
        int ans = 0;
        while (!q.empty()) {
            int y = q.front().first;
            int x = q.front().second;
            q.pop_front();
            ans++;
            if (field[y][x] == t + 1) {
                continue;
            }

            for (int i = 0; i < 6; i++) {
                int ny = y + dy[i];
                int nx = x + dx[i];
                if (field[ny][nx] < 0) {
                    continue;
                } else if (field[ny][nx] == 0) {
                    field[ny][nx] = field[y][x] + 1;
                    q.push_back(make_pair(ny, nx));
                }
            }
        }
        cout << ans << endl;
    }
}
