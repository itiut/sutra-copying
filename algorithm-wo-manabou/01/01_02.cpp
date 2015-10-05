#include <iostream>
#include <climits>
using namespace std;

int powmod(int a, int k, int m) {
    if (k == 0) {
        return 1;
    }

    long long ret = powmod(a, k / 2, m);
    ret = (ret * ret) % m;
    if (k % 2 == 1) {
        ret = (ret * a) % m;
    }

    return ret;
}

int main() {
    cout << powmod(3, INT_MAX, 10000) << endl;
}
