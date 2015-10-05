#include <iostream>
#include <vector>
using namespace std;

bool contsins(int v, vector<int> vs) {
    for (auto elem : vs) {
        if (elem == v) {
            return true;
        }
    }
    return false;
}
