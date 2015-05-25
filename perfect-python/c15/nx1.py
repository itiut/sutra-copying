import networkx as nx


def main():
    g = nx.Graph([(0, 1),
                  (1, 2),
                  (2, 3),
                  (10, 20),
                  (20, 30),
                  (30, 40),
                  (40, 10)])

    print(g.node)
    print(g.nodes())
    print(g.edge)
    print(g.edges())
    print(g.degree())
    print(g[1])


if __name__ == '__main__':
    main()
