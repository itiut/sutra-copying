#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& vs, int left, int right, int pivot) {
    int il = left;
    int ir = right - 1;
    while (il < ir) {
        while (il < right && vs[il] <= pivot) {
            il++;
        }
        while (left <= ir && pivot < vs[ir]) {
            ir--;
        }
        if (il >= ir) {
            break;
        }

        int temp = vs[il];
        vs[il] = vs[ir];
        vs[ir] = temp;
    }
    return ir + 1;
}

int find_pivot_idx(vector<int>& vs, int left, int right) {
    if (right - left <= 1) {
        return -1;
    }
    int temp = vs[left];
    for (int i = left + 1; i < right; i++) {
        if (vs[i] == temp) {
            continue;
        }
        if (vs[i] < temp) {
            return i;
        } else {
            return left;
        }
    }
    return -1;
}

void quicksort(vector<int>& vs, int left, int right) {
    if (right - left <= 1) {
        return;
    }

    int pivot_idx = find_pivot_idx(vs, left, right);
    if (pivot_idx < 0) {
        return;
    }

    int mid = partition(vs, left, right, vs[pivot_idx]);
    quicksort(vs, left, mid);
    quicksort(vs, mid, right);
}

void quicksort(vector<int>& vs) {
    quicksort(vs, 0, vs.size());
}

int main() {
    vector<int> vs = {10, 6, 3, 8, 2, 4, 1, 5, 9, 7};
    quicksort(vs);
    for (auto v : vs) {
        cout << v << endl;
    }
}
