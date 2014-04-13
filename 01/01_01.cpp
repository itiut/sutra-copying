#include <iostream>
#include <climits>
using namespace std;

int powmod(int a, int k, int m) {
    long long ret;
    for (int i = 0; i < k; i++) {
        ret = (ret * a) % m;
    }
    return ret;
}

int main() {
    cout << powmod(3, INT_MAX, 10000) << endl;
}
