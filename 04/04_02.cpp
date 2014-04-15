#include "04_01.hpp"
#include <set>
using namespace std;

bool dfs(Graph g, Vertex v, Vertex goal, set<Vertex>& visited) {
    if (&v == &goal) {
        return true;
    }

    if (visited.count(v) == 1) {
        return false;
    }
    visited.insert(v);

    for (auto edge : g.getEdges(v)) {
        if (dfs(g, edge.target, goal, visited)) {
            return true;
        }
    }

    return false;
}

bool find(Graph g, Vertex start, Vertex goal) {
    set<Vertex> vertices;
    return dfs(g, start, goal, vertices);
}
