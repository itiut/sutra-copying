#include <iostream>
#include <vector>
using namespace std;

void selectionsort(vector<int>& vs) {
    for (int i = 0; i < vs.size(); i++) {
        int min_idx = i;
        for (int j = i + 1; j < vs.size(); j++) {
            if (vs[j] < vs[min_idx]) {
                min_idx = j;
            }
        }

        int temp = vs[i];
        vs[i] = vs[min_idx];
        vs[min_idx] = temp;
    }
}

int main() {
    vector<int> vs = {10, 6, 3, 8, 2, 4, 1, 5, 9, 7};
    selectionsort(vs);
    for (auto v : vs) {
        cout << v << endl;
    }
}
