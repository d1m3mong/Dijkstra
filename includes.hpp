#pragma once

#include <algorithm>
#include <climits>
#include <cstddef>
#include <functional>
#include <limits>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

struct Edge {
  size_t destination;
  int weight;
};

class Graph {
  std::vector<std::vector<Edge>> adjacencyList;

public:
  size_t addNode() {
    adjacencyList.emplace_back();
    return adjacencyList.size() - 1;
  }
  void addEdge(size_t from, size_t to, int weight) {
    adjacencyList[from].push_back({to, weight});
    adjacencyList[to].push_back({from, weight});
  }
  const std::vector<Edge> &getNeighbors(int node) const {
    return adjacencyList[node];
  }

  const std::vector<std::vector<Edge>> &getAdjacencyList() const {
    return adjacencyList;
  }
};

class Dijkstra {
  std::vector<int> distance;
  std::vector<int> previous;

  const Graph &graph;
  size_t startId;

  std::priority_queue<std::pair<int, std::size_t>,
                      std::vector<std::pair<int, std::size_t>>, std::greater<>>
      queue;

public:
  Dijkstra(const Graph &graph, size_t startId)
      : graph(graph), startId(startId) {
    distance.resize(graph.getAdjacencyList().size(),
                    std::numeric_limits<int>::max());
    previous.resize(graph.getAdjacencyList().size(), -1);

    distance[startId] = 0;
    queue.push({0, startId});

    while (!queue.empty()) {
      auto [currentDistance, currentId] = queue.top();
      queue.pop();

      if (currentDistance > distance[currentId]) {
        continue;
      }

      for (const auto &edge : graph.getAdjacencyList()[currentId]) {
        int newDistance = currentDistance + edge.weight;

        if (newDistance < distance[edge.destination]) {
          distance[edge.destination] = newDistance;
          previous[edge.destination] = (int)currentId;
          queue.push({newDistance, edge.destination});
        }
      }
    }
  }

  std::vector<size_t> getPath(size_t targetId) const {
    std::vector<size_t> path;

    if (targetId == startId) {
      return {startId};
    }

    if (previous[targetId] == -1)
      return path;

    int resultId = (int)targetId;

    do {
      path.push_back((size_t)resultId);

      resultId = previous[resultId];
    } while (resultId != -1);

    std::reverse(path.begin(), path.end());

    return path;
  }
};
