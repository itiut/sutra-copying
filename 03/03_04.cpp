#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>&vs, int left, int mid, int right) {
    int n = right - left;
    vector<int> temps(n);

    int it = 0, il = left, ir = mid;
    while (il < mid && ir < right) {
        if (vs[il] < vs[ir]) {
            temps[it++] = vs[il++];
        } else {
            temps[it++] = vs[ir++];
        }
    }

    while (il < mid) {
        temps[it++] = vs[il++];
    }
    while (ir < right) {
        temps[it++] = vs[ir++];
    }

    copy(begin(temps), end(temps), begin(vs) + left);
}

void mergesort(vector<int>& vs, int left, int right) {
    if (right - left <= 1) {
        return;
    }

    int mid = left + (right - left) / 2;
    mergesort(vs, left, mid);
    mergesort(vs, mid, right);

    merge(vs, left, mid, right);
}

void mergesort(vector<int>& vs) {
    mergesort(vs, 0, vs.size());
}

int main() {
    vector<int> vs = {10, 6, 3, 8, 2, 4, 1, 5, 9, 7};
    mergesort(vs);
    for (auto v : vs) {
        cout << v << endl;
    }
}
