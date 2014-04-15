#include <iostream>
#include <vector>
using namespace std;

vector<int> memo(2000, -1);

int solve(int n) {
    if (memo.at(n) > 0) {
        return memo.at(n);
    }
    if (n <= 3) {
        return n;
    }
    for (int i = 1; i <= 3; i++) {
        if (solve(n - i) == 0) {
            return memo[n] = i;
        }
    }
    return memo[n] = 0;
}

int main() {
    cout << solve(199) << endl;
}
