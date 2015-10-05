#include <iostream>
using namespace std;

int solve(int n) {
    if (n <= 3) {
        return n;
    }
    for (int i = 1; i <= 3; i++) {
        if (solve(n - i) == 0) {
            return i;
        }
    }
    return 0;
}

int main() {
    cout << solve(39) << endl;
}
