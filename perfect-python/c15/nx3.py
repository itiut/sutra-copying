import networkx as nx
import matplotlib.pyplot as plt


def main():
    g = nx.Graph()
    g.add_nodes_from(['node', 'test'])

    g.add_star([1, 2, 3, 4, 5, 6])
    g.add_star([6, 7, 8, 9, 10])

    nx.draw(g)
    plt.show()


if __name__ == '__main__':
    main()
