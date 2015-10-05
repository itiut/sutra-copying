#include <iostream>
#include <vector>
#include <stdexcept>
#include <climits>
using namespace std;

class Heap {
private:
    int pos;
    vector<int> values;

public:
    Heap(int n) : pos(0), values(vector<int>(n)) {}

    void push(int v) {
        if (values.size() <= pos) {
            throw length_error("Excees the limit.");
        }

        int p = pos++;
        values[p] = v;

        while (p > 0) {
            int parent = (p - 1) / 2;
            if (values[parent] <= values[p]) {
                break;
            }
            int t = values[parent];
            values[parent] = values[p];
            values[p] = t;
            p = parent;
        }
    }

    int pop() {
        if (pos <= 0) {
            throw logic_error("Exceeds the limit.");
        }

        int ret = values[0];
        values[0] = values[--pos];

        int p = 0;
        while (p < pos) {
            int left = (2 * p + 1 < pos) ? values[2 * p + 1] : INT_MAX;
            int right = (2 * p + 2 < pos) ? values[2 * p + 2] : INT_MAX;
            if (values[p] <= left && values[p] <= right) {
                break;
            }

            if (left < right) {
                values[2 * p + 1] = values[p];
                values[p] = left;
                p = 2 * p + 1;
            } else {
                values[2 * p + 2] = values[p];
                values[p] = right;
                p = 2 * p + 2;
            }
        }
        return ret;
    }
};

void heapsort(vector<int>& vs) {
    Heap heap(vs.size());
    for (auto v : vs) {
        heap.push(v);
    }
    for (int i = 0; i < vs.size(); i++) {
        vs[i] = heap.pop();
    }
}

int main() {
    vector<int> vs = {10, 6, 3, 8, 2, 4, 1, 5, 9, 7};
    heapsort(vs);
    for (auto v : vs) {
        cout << v << endl;
    }
}
