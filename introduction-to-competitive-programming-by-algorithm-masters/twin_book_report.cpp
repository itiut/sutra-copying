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

int solve(int n, const vector<int>& rs, const vector<int>& ws) {
    int sum_r = accumulate(begin(rs), end(rs), 0);
    int max_r_idx = max_element(begin(rs), end(rs)) - begin(rs);
    int max_r = rs[max_r_idx];
    int sum_w = accumulate(begin(ws), end(ws), 0);

    if (max_r <= sum_r - max_r) {
        return sum_r + sum_w;
    }

    int max_waiting_time = max_r - (sum_r - max_r);
    vector<vector<bool>> dp(n + 1, vector<bool>(max_waiting_time, false));
    dp[0][0] = true;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= max_waiting_time; j++) {
            dp[i + 1][j] = dp[i + 1][j] || dp[i][j];
            if (i == max_r_idx) {
                continue;
            }
            if (j - ws[i] >= 0) {
                dp[i + 1][j] = dp[i + 1][j] || dp[i][j - ws[i]];
            }
        }
    }
    int max_j = 0;
    for (int j = 0; j <= max_waiting_time; j++) {
        if (dp[n][j]) {
            max_j = j;
        }
    }
    return 2 * max_r + (sum_w - max_j);
}

int main() {
    int n;
    while (cin >> n, n) {
        vector<int> rs(n), ws(n);
        for (int i = 0; i < n; i++) {
            cin >> rs[i] >> ws[i];
        }
        cout << solve(n, rs, ws) << endl;
    }
}
