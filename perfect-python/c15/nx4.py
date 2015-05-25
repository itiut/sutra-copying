import networkx as nx


def main():
    g = nx.Graph()
    g.add_star(range(5))
    g.add_star(range(5, 10))
    g.add_node('aaaa')
    print([x for x in nx.connected_components(g)])

    g.add_edge(1, 'aaaa')
    print([x for x in nx.connected_components(g)])


if __name__ == '__main__':
    main()
