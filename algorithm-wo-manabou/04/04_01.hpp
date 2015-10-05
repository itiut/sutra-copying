#ifndef _04_01_H_
#define _04_01_H_

#include <vector>
#include <set>
#include <map>

class Vertex {
    friend bool operator == (const Vertex& v1, const Vertex&v2) {
        return &v1 == &v2;
    }
};

class Edge {
public:
    Vertex source;
    Vertex target;
};

class Graph {
public:
    std::set<Vertex> vs;
    std::map<Vertex, std::vector<Edge>> es;

    Graph();

    std::vector<Edge> getEdges(Vertex v) {
        return es[v];
    }
};

#endif /* _04_01_H_ */
