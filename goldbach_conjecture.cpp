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

const int MAX_N = 1000000;
vector<bool> ps(MAX_N + 1, true);

int main() {
    ps[0] = ps[1] = false;
    for (int i = 4; i <= MAX_N; i += 2) {
        ps[i] = false;
    }
    for (int i = 3; i + i <= MAX_N; i += 2) {
        if (ps[i]) {
            for (int j = i + i; j <= MAX_N; j += i) {
                ps[j] = false;
            }
        }
    }

    int n;
    while (cin >> n, n) {
        for (int i = 2; i < n - 1; i++) {
            if (ps[i] && ps[n - i]) {
                cout << i << " " << n - i << endl;
                break;
            }
        }
    }
}
