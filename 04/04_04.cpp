#include "04_01.hpp"
#include <set>
#include <queue>
using namespace std;

bool bfs(Graph g, Vertex start, Vertex goal) {
    set<Vertex> visited;
    queue<Vertex> q;
    q.push(start);

    while (!q.empty()) {
        Vertex v(q.front());
        q.pop();
        if (&v == &goal) {
            return true;
        }

        if (visited.count(v) == 1) {
            continue;
        }
        visited.insert(v);

        for (auto edge : g.getEdges(v)) {
            if (visited.count(edge.target) == 1) {
                continue;
            }
            q.push(edge.target);
        }
    }

    return false;
}
