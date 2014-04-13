#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool contsins(int v, vector<int> vs) {
    int low = 0;
    int high = vs.size() - 1;

    while (low < high) {
        int mid = (low + high) / 2;
        if (vs[mid] < v) {
            low = mid + 1;
        } else if (vs[mid] > v) {
            high = mid - 1;
        } else {
            return true;
        }
    }

    return vs[low] == v;
}

int main() {
    vector<int> vs{1, 2, 3, 5, 6, 8, 10};
    for (int i = 0; i < 15; i++) {
        cout << i << " " << contsins(i, vs) << " " << binary_search(begin(vs), end(vs), i) << endl;
    }
}
