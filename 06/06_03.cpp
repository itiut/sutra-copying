#include <iostream>
#include <vector>
#include <utility>
#include <queue>
#include <cfloat>
using namespace std;

class Dijkstra {
public:
    int v_size;
    int e_size;
    vector<vector<double>> edges;
    vector<double> distances;

    Dijkstra(int v, int e)
        : v_size(v), e_size(e),
          edges(vector<vector<double>>(v, vector<double>(v, -1))),
          distances(vector<double>(v_size, DBL_MAX))
        {}

    void find(int start) {
        vector<bool> dones(v_size, false);
        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> q;

        q.push(make_pair(0, start));
        distances[start] = 0;

        while (!q.empty()) {
            int from = q.top().second;
            q.pop();

            if (dones[from]) {
                continue;
            }
            dones[from] = true;

            for (int to = 0; to < v_size; to++) {
                if (edges[from][to] < 0) {
                    continue;
                }
                if (distances[to] > distances[from] + edges[from][to]) {
                    distances[to] = distances[from] + edges[from][to];
                    q.push(make_pair(distances[to], to));
                }
            }
        }
    }
};


int main() {
    int v_size = 6;
    int e_size = 7;
    Dijkstra dijkstra(v_size, e_size);

    vector<vector<int>> edges = {
        {0, 1, 4},
        {0, 2, 2},
        {1, 3, 1},
        {2, 3, 1},
        {2, 4, 4},
        {3, 5, 6},
        {4, 5, 5}
    };

    for (int i = 0; i < edges.size(); i++) {
        int a = edges[i][0];
        int b = edges[i][1];
        dijkstra.edges[a][b] = dijkstra.edges[b][a] = edges[i][2];
    }

    dijkstra.find(0);

    for (int i = 0; i < v_size; i++) {
        cout << i << " " << dijkstra.distances[i] << endl;
    }
}
