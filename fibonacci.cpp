#include <iostream>
#include <vector>
using namespace std;

void calculate_fib(int n, vector<int>& fs) {
    fs[0] = fs[1] = 1;
    for (int i = 2; i <= n; i++) {
        fs[i] = fs[i - 1] + fs[i -2];
    }
}

int main() {
    vector<int> fs(46);
    calculate_fib(45, fs);

    for (int i = 0; i <= 45; i++) {
        cout << i << ": " << fs[i] << endl;
    }
}
