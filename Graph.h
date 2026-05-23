#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
#include <stack>
#include <limits>
#include <algorithm>
#include <functional>

// Weighted graph using an adjacency list.
// T must be hashable (std::hash<T>) and equality-comparable.
// Edge weights are int; unweighted edges default to weight 1.
//
// BFS and DFS are O(V + E).  Dijkstra is O((V + E) log V).
template <typename T = int>
class Graph {
private:
    using EdgeList = std::vector<std::pair<T, int>>;
    std::unordered_map<T, EdgeList> adj;
    bool directed;

public:
    explicit Graph(bool directed = false) : directed(directed) {}

    // Adds an isolated vertex (no-op if already present).
    void addVertex(const T& v) {
        if (!adj.count(v)) adj[v] = {};
    }

    // Adds a weighted edge from → to (and to → from if undirected).
    void addEdge(const T& from, const T& to, int weight = 1) {
        addVertex(from);
        addVertex(to);
        adj[from].emplace_back(to, weight);
        if (!directed) adj[to].emplace_back(from, weight);
    }

    // Removes an edge. For undirected graphs, removes both directions.
    void removeEdge(const T& from, const T& to) {
        auto erase = [&](EdgeList& edges, const T& target) {
            edges.erase(
                std::remove_if(edges.begin(), edges.end(),
                    [&target](const std::pair<T, int>& e) { return e.first == target; }),
                edges.end());
        };
        if (adj.count(from)) erase(adj[from], to);
        if (!directed && adj.count(to)) erase(adj[to], from);
    }

    // Removes a vertex and all edges connected to it.
    void removeVertex(const T& v) {
        adj.erase(v);
        for (auto& [u, edges] : adj)
            edges.erase(
                std::remove_if(edges.begin(), edges.end(),
                    [&v](const std::pair<T, int>& e) { return e.first == v; }),
                edges.end());
    }

    bool hasVertex(const T& v)                const { return adj.count(v) > 0; }

    bool hasEdge(const T& from, const T& to) const {
        if (!adj.count(from)) return false;
        for (auto& [nb, w] : adj.at(from))
            if (nb == to) return true;
        return false;
    }

    // Returns vertices reachable from start in breadth-first order.
    std::vector<T> bfs(const T& start) const {
        std::vector<T> result;
        if (!hasVertex(start)) return result;

        std::unordered_set<T> visited;
        std::queue<T> q;
        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            T v = q.front(); q.pop();
            result.push_back(v);
            for (auto& [nb, w] : adj.at(v)) {
                if (!visited.count(nb)) {
                    visited.insert(nb);
                    q.push(nb);
                }
            }
        }
        return result;
    }

    // Returns vertices reachable from start in depth-first order (iterative).
    std::vector<T> dfs(const T& start) const {
        std::vector<T> result;
        if (!hasVertex(start)) return result;

        std::unordered_set<T> visited;
        std::stack<T> s;
        s.push(start);

        while (!s.empty()) {
            T v = s.top(); s.pop();
            if (visited.count(v)) continue;
            visited.insert(v);
            result.push_back(v);
            // Push in reverse so we visit in natural adjacency order.
            auto& neighbors = adj.at(v);
            for (auto it = neighbors.rbegin(); it != neighbors.rend(); ++it)
                if (!visited.count(it->first)) s.push(it->first);
        }
        return result;
    }

    // Dijkstra's shortest-path distances from start.
    // Unreachable vertices map to std::numeric_limits<int>::max().
    std::unordered_map<T, int> dijkstra(const T& start) const {
        std::unordered_map<T, int> dist;
        for (auto& [v, edges] : adj) dist[v] = std::numeric_limits<int>::max();
        dist[start] = 0;

        using PQ = std::priority_queue<
            std::pair<int, T>,
            std::vector<std::pair<int, T>>,
            std::greater<std::pair<int, T>>>;
        PQ pq;
        pq.push({0, start});

        while (!pq.empty()) {
            int  d = pq.top().first;
            T    v = pq.top().second;
            pq.pop();
            if (d > dist[v]) continue;  // stale entry
            for (auto& [nb, weight] : adj.at(v)) {
                int newDist = dist[v] + weight;
                if (newDist < dist[nb]) {
                    dist[nb] = newDist;
                    pq.push({newDist, nb});
                }
            }
        }
        return dist;
    }

    // Prints the adjacency list of every vertex.
    void print() const {
        std::cout << (directed ? "Directed" : "Undirected") << " graph:\n";
        for (auto& [v, edges] : adj) {
            std::cout << "  " << v << " -> ";
            for (auto& [nb, w] : edges) std::cout << nb << "(w=" << w << ") ";
            std::cout << "\n";
        }
    }
};
