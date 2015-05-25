import networkx as nx


def main():
    g = nx.Graph()
    g.add_cycle(range(5))
    g.add_cycle(range(5, 10))
    g.add_node(20)
    print(nx.cycle_basis(g))

    g.add_edges_from([(0, 5), (3, 8)])
    print(nx.cycle_basis(g))


if __name__ == '__main__':
    main()
