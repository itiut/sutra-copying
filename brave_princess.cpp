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
    priority_queue<Edge, Edges, greater<Edge>> q;
    q.push(Edge(startV, 0));
    while (!q.empty()) {
        Edge edge = q.top();
        q.pop();
        Vertex p = edge.target;
        Weight curr = edge.weight;

        if (pot.count(p)) {
            continue;
        }
        pot[p] = curr;
        for (auto& e : g[p]) {
            if (pot.count(e.target)) {
                continue;
            }
            q.push(Edge(e.target, curr + e.weight));
        }
    }
    return pot;
}

int main() {
    int n, m, l;
    while (cin >> n >> m >> l, n || m || l) {
        Graph g;
        for (int i = 0; i < m; i++) {
            int a, b, d, e;
            cin >> a >> b >> d >> e;
            for (int restMoney = 0; restMoney <= l; restMoney++) {
                g[Vertex(a, restMoney)].push_back(Edge(Vertex(b, restMoney), e));
                g[Vertex(b, restMoney)].push_back(Edge(Vertex(a, restMoney), e));

                if (restMoney >= d) {
                    g[Vertex(a, restMoney)].push_back(Edge(Vertex(b, restMoney - d), 0));
                    g[Vertex(b, restMoney)].push_back(Edge(Vertex(a, restMoney - d), 0));
                }
            }
        }
        Potential pot(dijkstra(g, Vertex(1, l)));
        int minCost = INT_MAX;
        for (int money = 0; money <= l; money++) {
            if (!pot.count(Vertex(n, money))) {
                continue;
            }
            minCost = min(minCost, pot[Vertex(n, money)]);
        }
        cout << minCost << endl;
    }
}
