#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class UnionFind {
private:
    vector<int> ids;

public:
    UnionFind(int n) : ids(vector<int>(n)) {
        for (int i = 0; i < n; i++) {
            ids[i] = i;
        }
    }

    int find(int a) {
        if (ids[a] == a) {
            return a;
        }
        return ids[a] = find(ids[a]);
    }

    void unify(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) {
            return;
        }
        ids[a] = b;
    }

    bool united(int a, int b) {
        return find(a) == find(b);
    }
};

class Kruskal {
public:
    int v_size;
    int e_size;
    vector<vector<double>> edges;
    vector<pair<int, int>> results;

    Kruskal(int v, int e)
        : v_size(v), e_size(e),
          edges(vector<vector<double>>(v, vector<double>(v, -1)))
        {}

    void find() {
        UnionFind uf(v_size);

        vector<pair<double, pair<int, int>>> es;
        for (int i = 0; i < v_size; i++) {
            for (int j = 0; j < v_size; j++) {
                if (edges[i][j] >= 0) {
                    es.push_back(make_pair(edges[i][j], make_pair(i, j)));
                }
            }
        }
        sort(begin(es), end(es));

        results.clear();
        for (auto e : es) {
            if (uf.united(e.second.first, e.second.second)) {
                continue;
            }
            uf.unify(e.second.first, e.second.second);
            results.push_back(e.second);
        }
    }
};

int main() {
    int v_size = 6;
    int e_size = 9;
    Kruskal kruskal(v_size, e_size);

    kruskal.edges[0][1] = kruskal.edges[1][0] = 1;
    kruskal.edges[0][3] = kruskal.edges[3][0] = 4;
    kruskal.edges[0][4] = kruskal.edges[4][0] = 1;
    kruskal.edges[1][2] = kruskal.edges[2][1] = 2;
    kruskal.edges[1][4] = kruskal.edges[4][1] = 1;
    kruskal.edges[2][4] = kruskal.edges[4][2] = 7;
    kruskal.edges[2][5] = kruskal.edges[5][2] = 3;
    kruskal.edges[3][4] = kruskal.edges[4][3] = 1;
    kruskal.edges[4][5] = kruskal.edges[5][4] = 4;

    kruskal.find();

    for (auto result : kruskal.results) {
        cout << result.first << " <-> " << result.second << endl;
    }
}
