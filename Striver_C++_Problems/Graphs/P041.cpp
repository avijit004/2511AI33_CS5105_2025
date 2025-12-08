// P041.cpp - Find all bridges (critical connections) in an undirected graph

#include <bits/stdc++.h>
using namespace std;

// ---------- Brute: remove each edge and test connectivity ----------
void dfs_brute(int node,
               const vector<vector<int>>& adj,
               vector<bool>& visited,
               int ban_u, int ban_v) {
    visited[node] = true;
    for (int nei : adj[node]) {
        // skip the banned edge in both directions
        if ((node == ban_u && nei == ban_v) ||
            (node == ban_v && nei == ban_u)) {
            continue;
        }
        if (!visited[nei]) {
            dfs_brute(nei, adj, visited, ban_u, ban_v);
        }
    }
}

vector<pair<int,int>> brute(int n, const vector<pair<int,int>>& connections) {
    vector<vector<int>> adj(n);
    for (auto &e : connections) {
        int u = e.first, v = e.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<pair<int,int>> bridges;

    for (auto &e : connections) {
        int u = e.first, v = e.second;
        vector<bool> visited(n, false);
        dfs_brute(0, adj, visited, u, v);
        int cnt = 0;
        for (bool b : visited) if (b) cnt++;
        if (cnt < n) {
            bridges.push_back({u, v});
        }
    }
    return bridges;
}

// ---------- Optimal: Tarjan's algorithm for bridges ----------
void dfs_tarjan(int node, int parent,
                const vector<vector<int>>& adj,
                vector<int>& tin,
                vector<int>& low,
                vector<bool>& visited,
                int& timer,
                vector<pair<int,int>>& res) {
    visited[node] = true;
    tin[node] = low[node] = timer++;
    for (int nei : adj[node]) {
        if (nei == parent) continue;
        if (!visited[nei]) {
            dfs_tarjan(nei, node, adj, tin, low, visited, timer, res);
            low[node] = min(low[node], low[nei]);
            if (low[nei] > tin[node]) {
                res.push_back({node, nei});
            }
        } else {
            low[node] = min(low[node], tin[nei]);
        }
    }
}

vector<pair<int,int>> optimal(int n, const vector<pair<int,int>>& connections) {
    vector<vector<int>> adj(n);
    for (auto &e : connections) {
        int u = e.first, v = e.second;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    vector<int> tin(n, -1), low(n, -1);
    vector<bool> visited(n, false);
    vector<pair<int,int>> res;
    int timer = 0;

    // Python called dfs(0,-1); we generalize to all components
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            dfs_tarjan(i, -1, adj, tin, low, visited, timer, res);
        }
    }
    return res;
}

int main() {
    int n = 4;
    vector<pair<int,int>> connections = {{0,1},{1,2},{2,0},{1,3}};

    auto b = brute(n, connections);
    auto o = optimal(n, connections);

    cout << "Brute: ";
    for (auto &e : b) cout << "[" << e.first << "," << e.second << "] ";
    cout << "\nOptimal: ";
    for (auto &e : o) cout << "[" << e.first << "," << e.second << "] ";
    cout << "\n";
    return 0;
}
