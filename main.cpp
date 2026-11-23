#include <iostream>

#include "includes.hpp"

int main() {
  Graph g;
  g.addNode();
  g.addNode();
  g.addNode();
  g.addNode();

  g.addEdge(0, 1, 5);
  g.addEdge(0, 2, 3);
  g.addEdge(1, 3, 8);
  g.addEdge(2, 3, 3);

  Dijkstra dijkstra(g, 0);
  auto result = dijkstra.getPath(3);

  for (const auto &v : result) {
    std::cout << v << '\n';
  }

  return 0;
}
