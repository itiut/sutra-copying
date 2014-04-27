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

const long long MOD = 1000000007;

bool isValidDigit(const string& S, int nth, int digit) {
    if (S.size() -1 == nth && digit == 0) {
        return false;
    }
    if (S[nth] != '?' && S[nth] != '0' + digit) {
        return false;
    }
    return true;
}

long long solve(const string& A, const string& B, const string& C) {
    vector<vector<long long>> numSolutions(2, vector<long long>(A.size() + 1));
    numSolutions[0][0] = 1;

    for (int i = 0; i < A.size(); i++) {
        for (int a = 0; a <= 9; a++) {
            if (!isValidDigit(A, i, a)) {
                continue;
            }
            for (int b = 0; b <= 9; b++) {
                if (!isValidDigit(B, i, b)) {
                    continue;
                }

                if (isValidDigit(C, i, (a + b) % 10)) {
                    int carry = (a + b) / 10;
                    numSolutions[carry][i + 1] += numSolutions[0][i];
                    numSolutions[carry][i + 1] %= MOD;
                }
                if (isValidDigit(C, i, (a + b + 1) % 10)) {
                    int carry = (a + b + 1) / 10;
                    numSolutions[carry][i + 1] += numSolutions[1][i];
                    numSolutions[carry][i + 1] %= MOD;
                }
            }
        }
    }
    return numSolutions[0][A.size()] % MOD;
}

int main(void) {
    string a, b, c;
    while (true) {
        cin >> a >> b >> c;
        if (a == "0")
            break;

        reverse(a.begin(), a.end());
        reverse(b.begin(), b.end());
        reverse(c.begin(), c.end());
        cout << solve(a, b, c) << endl;
    }
}
