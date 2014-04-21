#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <stdexcept>
using namespace std;

class Prim {
public:
    int v_size;
    int e_size;
    vector<vector<double>> edges;
    vector<pair<int, int>> results;

    Prim(int v, int e)
        : v_size(v), e_size(e),
          edges(vector<vector<double>>(v, vector<double>(v, -1)))
        {}

    void find() {
        priority_queue<pair<double, pair<int, int>>, vector<pair<double, pair<int, int>>>, greater<pair<double, pair<int, int>>>> q;
        q.push(make_pair(0, make_pair(-1, 0)));

        results.clear();
        vector<bool> dones(v_size, false);

        while (!q.empty() && results.size() < v_size) {
            int from = q.top().second.first;
            int to = q.top().second.second;
            q.pop();
            if (dones[to]) {
                continue;
            }
            dones[to] = true;
            if (from >= 0) {
                results.push_back(make_pair(from, to));
            }

            for (int i = 0; i < v_size; i++) {
                if (dones[i] || edges[to][i] < 0) {
                    continue;
                }
                q.push(make_pair(edges[to][i], make_pair(to, i)));
            }
        }

        if (results.size() != v_size - 1) {
            throw logic_error("No results");
        }
    }
};

int main() {
    int v_size = 6;
    int e_size = 9;
    Prim prim(v_size, e_size);

    prim.edges[0][1] = prim.edges[1][0] = 1;
    prim.edges[0][3] = prim.edges[3][0] = 4;
    prim.edges[0][4] = prim.edges[4][0] = 1;
    prim.edges[1][2] = prim.edges[2][1] = 2;
    prim.edges[1][4] = prim.edges[4][1] = 1;
    prim.edges[2][4] = prim.edges[4][2] = 7;
    prim.edges[2][5] = prim.edges[5][2] = 3;
    prim.edges[3][4] = prim.edges[4][3] = 1;
    prim.edges[4][5] = prim.edges[5][4] = 4;

    prim.find();

    for (auto result : prim.results) {
        cout << result.first << " <-> " << result.second << endl;
    }
}
