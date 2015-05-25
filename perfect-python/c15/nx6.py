import networkx as nx
import matplotlib.pyplot as plt


def main():
    g = nx.star_graph(5)
    g.add_path([5, 6, 7, 8, 9, 10])
    g.add_path([5, 20, 10])

    print(nx.shortest_path(g, 3, 10))

    nx.draw(g)
    plt.show()


if __name__ == '__main__':
    main()
