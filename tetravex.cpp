#include <algorithm>
#include <bitset>
#include <cctype>
#include <climits>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <deque>
#include <functional>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

struct Piece {
    int u, d, l, r;
    Piece() {}
    Piece(int u, int d, int l, int r)
        : u(u), d(d), l(l), r(r) {}
};

bool iter(vector<vector<Piece>>& field, vector<bool>& used,
          const vector<Piece>& pieces, int h, int w, int pos) {
    if (pos == h * w) {
        return true;
    }
    const int y = pos / w;
    const int x = pos % w;

    for (int i = 0; i < h * w; i++) {
        if (used[i]) {
            continue;
        }
        if (x != 0 && pieces[i].l != field[y][x - 1].r) {
            continue;
        }
        if (y != 0 && pieces[i].u != field[y - 1][x].d) {
            continue;
        }
        used[i] = true;
        field[y][x] = pieces[i];
        if (iter(field, used, pieces, h, w, pos + 1)) {
            return true;
        }
        used[i] = false;
    }
    return false;
}

bool solve(const vector<Piece>& pieces, int h, int w) {
    vector<vector<Piece>> field(h, vector<Piece>(w));
    vector<bool> used(h * w);
    return iter(field, used, pieces, h, w, 0);
}

int main() {
    for (int h, w; cin >> h >> w, (h || w); ) {
        vector<Piece> pieces(h * w);
        for (auto& piece : pieces) {
            int u, d, l, r;
            cin >> u >> d >> l >> r;
            piece = Piece(u, d, l, r);
        }
        if (solve(pieces, h, w)) {
            cout << "Yes" << endl;
        } else {
            cout << "No" << endl;
        }
    }
}
