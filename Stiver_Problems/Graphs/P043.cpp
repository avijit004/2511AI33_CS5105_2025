// P043.cpp - Kosaraju's algorithm: count strongly connected components

#include <bits/stdc++.h>
using namespace std;

void dfs1(int node,
          const vector<vector<int>>& adj,
          vector<bool>& visited,
          vector<int>& stack_order) {
    visited[node] = true;
    for (int nei : adj[node]) {
        if (!visited[nei]) {
            dfs1(nei, adj, visited, stack_order);
        }
    }
    stack_order.push_back(node);
}

void dfs2(int node,
          const vector<vector<int>>& rev,
          vector<bool>& visited) {
    visited[node] = true;
    for (int nei : rev[node]) {
        if (!visited[nei]) {
            dfs2(nei, rev, visited);
        }
    }
}

int kosaraju(int V, const vector<vector<int>>& adj) {
    vector<bool> visited(V, false);
    vector<int> stack_order;

    // 1st pass: DFS on original graph to fill stack by finish time
    for (int i = 0; i < V; i++) {
        if (!visited[i]) {
            dfs1(i, adj, visited, stack_order);
        }
    }

    // Build reversed graph
    vector<vector<int>> rev(V);
    for (int u = 0; u < V; u++) {
        for (int v : adj[u]) {
            rev[v].push_back(u);
        }
    }

    // 2nd pass: DFS on reversed graph in stack order
    fill(visited.begin(), visited.end(), false);
    int SCC = 0;
    while (!stack_order.empty()) {
        int node = stack_order.back();
        stack_order.pop_back();
        if (!visited[node]) {
            dfs2(node, rev, visited);
            SCC++;
        }
    }
    return SCC;
}

int main() {
    int V = 5;
    vector<vector<int>> adj = {
        {2, 3},   // 0
        {0},      // 1
        {1},      // 2
        {4},      // 3
        {}        // 4
    };

    cout << "SCC Count: " << kosaraju(V, adj) << "\n";
    return 0;
}
