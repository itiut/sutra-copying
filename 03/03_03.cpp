#include <iostream>
#include <vector>
using namespace std;

void insertionsort(vector<int>& vs) {
    for (int i = 1; i < vs.size(); i++) {
        int temp = vs[i];
        int j = i;
        while (j > 0 && vs[j - 1] > temp) {
            vs[j] = vs[j - 1];
            j--;
        }
        vs[j] = temp;
    }
}

int main() {
    vector<int> vs = {10, 6, 3, 8, 2, 4, 1, 5, 9, 7};
    insertionsort(vs);
    for (auto v : vs) {
        cout << v << endl;
    }
}
