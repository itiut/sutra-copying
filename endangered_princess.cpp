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
#include <queue>
#include <set>
#include <sstream>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> Vertex;
typedef int Weight;
struct Edge {
    Vertex target;
    Weight weight;
    Edge() {}
    Edge(const Vertex& t, Weight w) : target(t), weight(w) {}
};

typedef vector<Edge> Edges;
typedef map<Vertex, Edges> Graph;
typedef map<Vertex, Weight> Potential;

bool operator>(const Edge& lhs, const Edge& rhs) {
    if (lhs.weight != rhs.weight) {
        return lhs.weight > rhs.weight;
    }
    return lhs.target > rhs.target;
}

Potential dijkstra(Graph& g, const Vertex& startV) {
    Potential pot;
    priority_queue<Edge, Edges, greater<Edge>> Q;
    Q.push(Edge(startV, 0));
    while (!Q.empty()) {
        Edge edge = Q.top();
        Q.pop();
        Vertex p = edge.target;
        Weight curr = edge.weight;

        if (pot.count(p)) {
            continue;
        }
        pot[p] = curr;

        Edges& es = g[p];
        for (auto& e : es) {
            if (pot.count(e.target)) {
                continue;
            }
            Q.push(Edge(e.target, curr + e.weight));
        }
    }
    return pot;
}

int main() {
    int n, m, l, k, a, h;
    while (cin >> n >> m >> l >> k >> a >> h, n || m || l || k || a || h) {
        Graph g;
        for (int i = 0; i < l; i++) {
            int city;
            cin >> city;
            for (int j = 0; j < m; j++) {
                g[Vertex(city, j)].push_back(Edge(Vertex(city, j + 1), 1));
            }
        }
        for (int i = 0; i < k; i++) {
            int x, y, t;
            cin >> x >> y >> t;
            for (int j = t; j <= m; j++) {
                g[Vertex(x, j)].push_back(Edge(Vertex(y, j - t), t));
                g[Vertex(y, j)].push_back(Edge(Vertex(x, j - t), t));
            }
        }
        Potential pot(dijkstra(g, Vertex(a, m)));
        int minTime = INT_MAX;
        for (int i = 0; i <= m; i++) {
            if (!pot.count(Vertex(h, i))) {
                continue;
            }
            minTime = min(minTime, pot[Vertex(h, i)]);
        }
        if (minTime == INT_MAX) {
            cout << "Help!" << endl;
        } else {
            cout << minTime << endl;
        }
    }
}
