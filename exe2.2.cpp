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
    for (int i = 4; i <= MAX_N; i++) {
        ps[i] = true;
    }
    for (int i = 3; i + i <= MAX_N; i += 2) {
        if (!ps[i]) {
            continue;
        }
        for (int j = i + i; j <= MAX_N; j += i) {
            ps[j] = false;
        }
    }

    vector<pair<int, int>> twins;
    for (int i = 3; i < MAX_N - 1; i+= 2) {
        if (ps[i] && ps[i + 2]) {
            twins.push_back(make_pair(i, i + 2));
        }
    }

    int k;
    while (cin >> k, k) {
        cout << twins[k - 1].first << " " << twins[k - 1].second << endl;
    }
}
