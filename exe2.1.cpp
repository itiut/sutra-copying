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

int main() {
    int n;
    cin >> n;
    vector<int> points(n);
    for (auto& point : points) {
        cin >> point;
    }
    int sum = accumulate(begin(points), end(points), 0);
    sum -= *min_element(begin(points), end(points));
    sum -= *max_element(begin(points), end(points));
    cout << sum / (n - 2) << endl;
}
