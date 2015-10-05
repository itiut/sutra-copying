#include <iostream>
#include <vector>
using namespace std;

vector<int> refs(200);

int find(int a) {
    if (refs[a] == a) {
        return a;
    }
    return refs[a] = find(refs[a]);
}

void unify(int a, int b) {
    a = find(a);
    b = find(b);

    if (a == b) {
        return;
    }
    refs[a] = b;
}

bool united(int a, int b) {
    return find(a) == find(b);
}

int main() {
    for (int i = 0; i < refs.size(); i++) {
        refs[i] = i;
    }

    unify(0, 1);
    unify(1, 3);
    unify(2, 4);

    cout << "0 and 3 are united? -> " << united(0, 3) << endl;
    cout << "1 and 2 are united? -> " << united(1, 2) << endl;

    for (int i = 0; i < 5; i++) {
        cout << i << " " << refs[i] << endl;
    }
}
