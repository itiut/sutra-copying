import networkx as nx

g = nx.Graph()
g.add_path([1, 2, 3, 4])
print(g.edges())

g = nx.Graph()
g.add_star([1, 2, 3, 4])
print(g.edges())
