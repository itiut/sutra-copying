#include <iostream>
#include <vector>
using namespace std;

void bubblesort(vector<int>& vs) {
    for (int i = 0; i < vs.size(); i++) {
        for (int j = 0; j < vs.size() - 1 - i; j++) {
            if (vs[j] > vs[j + 1]) {
                int temp = vs[j];
                vs[j] = vs[j + 1];
                vs[j + 1] = temp;
            }
        }
    }
}

int main() {
    vector<int> vs = {10, 6, 3, 8, 2, 4, 1, 5, 9, 7};
    bubblesort(vs);
    for (auto v : vs) {
        cout << v << endl;
    }
}
