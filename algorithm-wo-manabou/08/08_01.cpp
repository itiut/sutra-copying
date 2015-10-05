#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(const vector<int>& weights, const vector<int>& values, int W) {
    const int N = weights.size();
    vector<vector<int>> dp(N + 1, vector<int>(W + 1, 0));

    for (int k = 1; k <= N; k++) {
        for (int w = 0; w <= W; w++) {
            dp[k][w] = dp[k - 1][w];
            if (w > 0) {
                dp[k][w] = max(dp[k][w], dp[k][w - 1]);
            }
            if (w >= weights[k - 1]) {
                dp[k][w] = max(dp[k][w], dp[k - 1][w - weights[k - 1]] + values[k - 1]);
            }
        }
    }
    return dp[N][W];
}

int main() {
    vector<int> weights = {5, 3, 3, 1};
    vector<int> values = {20, 11, 11, 1};
    cout << knapsack(weights, values, 6) << endl;
}
